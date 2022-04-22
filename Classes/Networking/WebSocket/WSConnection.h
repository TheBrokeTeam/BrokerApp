//
// Created by Maykon Meneghel on 03/02/22.
//

#ifndef BROKERAPP_WSCONNECTION_H
#define BROKERAPP_WSCONNECTION_H

#include "WSCommon.h"
#include "WSMessage.h"
#include "WSQueue.h"
#include <fmt/format.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

enum class CustomMsgTypes : uint32_t {
    ServerAccept,
    ServerDeny,
    ServerPing,
    MessageAll,
    ServerMessage,
    Hi
};

namespace olc::net {

    template<typename T>
    class server_interface;

    template<typename T>
    class connection: public std::enable_shared_from_this<connection<T>>{

    public:
        connection(boost::asio::io_context& asioContext, boost::asio::ip::tcp::socket socket, WSQueue<owned_message<T>>& qIn)
            : m_asioContext(asioContext), m_socket(std::move(socket)), m_qMessagesIn(qIn) {

            m_handShakeOut = uint64_t(std::chrono::system_clock::now().time_since_epoch().count());
            m_handShakeCheck = scramble(m_handShakeOut);

        }

        virtual ~connection() {};

        uint32_t GetID() const {
            return id;
        }

    public:

        void ConnectToServer(const boost::asio::ip::tcp::resolver::results_type& endpoints)
        {
            boost::asio::async_connect(m_socket, endpoints, [this](boost::system::error_code ec, const boost::asio::ip::tcp::endpoint& endpoint)
            {
                if (!ec) {
                    std::cout << "Connected in Server on " << endpoint.port() << std::endl;
                    WriteValidation();
                }
            });
        }

        void Disconnect() {
            if (IsConnected()) {
                boost::system::error_code ec;
                m_socket.close(ec);
                if(!ec)
                {
                    std::cout << "Closed WebSocket" << std::endl;
                } else
                {
                    std::cout << "Error: " << ec.message() << std::endl;
                }
            }

        }

        bool IsConnected() const {
            return m_socket.is_open();
        }

        // Prime the connection to wait for incoming messages
        void StartListening() {

        }

    public:
        void Send(const message<T>& msg) {
            boost::asio::post(m_asioContext, [this, msg]() {
                // If the queue has a message in it, then we must
                // assume that it is in the process of asynchronously being written.
                // Either way add the message to the queue to be output. If no messages
                // were available to be written, then start the process of writing the
                // message at the front of the queue.
                bool bWritingMessage = !m_qMessagesOut.empty();
                m_qMessagesOut.push_back(msg);
                if (!bWritingMessage) {
                    WriteHeader();
                }
            });
        }

    private:
        void WriteHeader() {
            // If this function is called, we know the outgoing message queue must have
            // at least one message to send. So allocate a transmission buffer to hold
            // the message, and issue the work - asio, send these bytes
            boost::asio::async_write(m_socket, boost::asio::buffer(&m_qMessagesOut.front().header, sizeof(message_header<T>)),
                              [this](boost::system::error_code ec, std::size_t length) {
                // asio has now sent the bytes - if there was a problem
                // an error would be available...
                if (!ec) {
                    // ... no error, so check if the message header just sent also
                    // has a message body...
                    if (m_qMessagesOut.front().body.size() > 0) {
                        // ...it does, so issue the task to write the body bytes
                        WriteBody();
                    }
                    else {
                        // ...it didnt, so we are done with this message. Remove it from
                        // the outgoing message queue
                        m_qMessagesOut.pop_front();

                        // If the queue is not empty, there are more messages to send, so
                        // make this happen by issuing the task to send the next header.
                        if (!m_qMessagesOut.empty()) {
                            WriteHeader();
                        }
                    }
                } else {
                    // ...asio failed to write the message, we could analyse why but
                    // for now simply assume the connection has died by closing the
                    // socket. When a future attempt to write to this client fails due
                    // to the closed socket, it will be tidied up.
                    std::cout << "[" << id << "] Write Header Fail.\n";
                    m_socket.close();
                }
            });
        }

        // ASYNC - Prime context to write a message body
        void WriteBody()
        {
            // If this function is called, a header has just been sent, and that header
            // indicated a body existed for this message. Fill a transmission buffer
            // with the body data, and send it!
            boost::asio::async_write(m_socket, boost::asio::buffer(m_qMessagesOut.front().body.data(), m_qMessagesOut.front().body.size()),
                              [this](boost::system::error_code ec, std::size_t length) {
                if (!ec) {
                    // Sending was successful, so we are done with the message
                    // and remove it from the queue
                    m_qMessagesOut.pop_front();

                    // If the queue still has messages in it, then issue the task to
                    // send the next messages' header.
                    if (!m_qMessagesOut.empty()) {
                        WriteHeader();
                    }
                } else {
                    // Sending failed, see WriteHeader() equivalent for description :P
                    std::cout << "[" << id << "] Write Body Fail.\n";
                    m_socket.close();
                }
            });
        }

        // ASYNC - Prime context ready to read a message header
        void ReadHeader()
        {
            // If this function is called, we are expecting asio to wait until it receives
            // enough bytes to form a header of a message. We know the headers are a fixed
            // size, so allocate a transmission buffer large enough to store it. In fact,
            // we will construct the message in a "temporary" message object as it's
            // convenient to work with.
            boost::asio::async_read(m_socket, boost::asio::buffer(&m_msgTemporaryIn.header, sizeof(message_header<T>)),
                             [this](boost::system::error_code ec, std::size_t length) {
                if (!ec) {
                    // A complete message header has been read, check if this message
                    // has a body to follow...
                    if (m_msgTemporaryIn.header.size > 0) {
                        std::cout << "Reading the header message" << std::endl;

                        // ...it does, so allocate enough space in the messages' body
                        // vector, and issue asio with the task to read the body.
                        m_msgTemporaryIn.body.resize(m_msgTemporaryIn.header.size);
                        ReadBody();
                    } else {
                        // it doesn't, so add this bodyless message to the connections
                        // incoming message queue
                        AddToIncomingMessageQueue();
                    }
                } else {
                    // Reading form the client went wrong, most likely a disconnect
                    // has occurred. Close the socket and let the system tidy it up later.
                    std::cout << "[" << id << "] Read Header Fail.\n";
                    m_socket.close();
                }
            });
        }

        // ASYNC - Prime context ready to read a message body
        void ReadBody()
        {
            // If this function is called, a header has already been read, and that header
            // request we read a body, The space for that body has already been allocated
            // in the temporary message object, so just wait for the bytes to arrive...
            boost::asio::async_read(m_socket, boost::asio::buffer(m_msgTemporaryIn.body.data(), m_msgTemporaryIn.body.size()),
                             [this](boost::system::error_code ec, std::size_t length) {
                if (!ec) {
                    std::cout << "Reading the body message" << std::endl;
                    // ...and they have! The message is now complete, so add
                    // the whole message to incoming queue
                    AddToIncomingMessageQueue();
                } else {
                    // As above!
                    std::cout << "[" << id << "] Read Body Fail.\n";
                    m_socket.close();
                }
            });
        }

        // Once a full message is received, add it to the incoming queue
        void AddToIncomingMessageQueue()
        {
            // Shove it in queue, converting it to an "owned message", by initialising
            // with the a shared pointer from this connection object

            m_qMessagesIn.push_back({ this->shared_from_this(), m_msgTemporaryIn });
//            m_qMessagesIn.push_back({ nullptr, m_msgTemporaryIn });

            // We must now prime the asio context to receive the next message. It
            // wil just sit and wait for bytes to arrive, and the message construction
            // process repeats itself. Clever huh?

            ReadHeader();
        }

        uint64_t scramble(uint64_t nInput)
        {
            uint64_t value;
//            std::istringstream iss("dGhlIHNhbXBsZSBub25jZQ==");
            std::istringstream iss("258EAFA5-E914–47DA-95CA-C5AB0DC85B11");
            iss >> value;
            uint64_t out = nInput - value;
            return out;
//            uint64_t out = nInput ^ 0xDEADBEEFC0DECAFE;
//            out = (out & 0xF0F0F0F0F0F0F0F0) >> 4 | (out & 0xF0F0F0F0F0F0F0F0) << 4;
//            return out ^ 0xC0DEFACE12345678;
        }

//        static std::string uint64_to_string(uint64_t value ) {
//            std::ostringstream os;
//            os << value;
//            return os.str();
//        }

        void WriteValidation()
        {
            std::string sRequest =
                    "GET /chat HTTP/1.1\r\n"
                    "Upgrade: websocket\r\n"
                    "Connection: Upgrade\r\n"
                    "Sec-WebSocket-Key:" + m_secKey + "\r\n"
                    "Sec-WebSocket-Version: 13\r\n\r\n";

            boost::asio::async_write(m_socket, boost::asio::buffer(sRequest.data(), sRequest.size()),
                [this](boost::system::error_code ec, std::size_t length)
                {
                    if(!ec)
                    {
                        m_socket.wait(m_socket.wait_read);
//                        m_socket.async_read_some(asio::buffer(vBuffer.data(), vBuffer.size()), [&](std::error_code ec, std::size_t length)
//                        {
//                            if(!ec)
//                            {
//                                std::cout << "Read" << length << "bytes" << std::endl;
//                                for(int i=0; i< length; i++){
//                                    std::cout << vBuffer[i];
//                                }
//
//                            }
//                        });
                        ReadValidation();
                    }
                    else
                    {
                        boost::asio::post(m_asioContext, [this]() { m_socket.close(); });
                    }
                });
        }

        void ReadValidation(olc::net::server_interface<T>* server = nullptr)
        {
            boost::asio::async_read(m_socket, boost::asio::buffer(&m_handShakeIn, sizeof(uint64_t)),
                [this, server](boost::system::error_code ec, std::size_t length)
                {
                    if(!ec)
                    {
                        m_handShakeOut = scramble(m_handShakeIn);
                        std::cout << "Client wait something." << std::endl;
                        ReadHeader();
                    } else
                    {
                        std::cout << "Client Disconnected." << std::endl;
                        m_socket.close();
                    }
                });
        }



    protected:
        boost::asio::ip::tcp::socket m_socket;
        boost::asio::io_context& m_asioContext;
        WSQueue<message<T>> m_qMessagesOut;
        WSQueue<owned_message<T>> m_qMessagesIn;
        message<T> m_msgTemporaryIn;
        uint32_t id = 0;

        uint64_t m_handShakeOut = 0;
        uint64_t m_handShakeIn = 0;
        uint64_t m_handShakeCheck = 0;
        std::string m_secKey = "dGhlIHNhbXBsZSBub25jZQ==";

        std::vector<char> vBuffer = std::vector<char>(20*1024);
    };


}

#endif //BROKERAPP_WSCONNECTION_H
