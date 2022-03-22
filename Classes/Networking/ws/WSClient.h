//
// Created by Maykon Meneghel on 03/02/22.
//

#ifndef BROKERAPP_WSCLIENT_H
#define BROKERAPP_WSCLIENT_H

#include "WSCommon.h"

namespace olc::net {
    template<typename T>
    struct client_interface {
    public:
        client_interface() {}

        virtual ~client_interface() {
            Disconnect();
        }

    public:
        void Connect(const std::string& host, const uint16_t port) {
            try {
                asio::ip::tcp::resolver resolver(m_context);
                asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(host, std::to_string(port));

                // Create connection
                m_connection = std::make_unique<connection<T>>(
                        m_context,
                        asio::ip::tcp::socket(m_context), m_qMessagesIn);

                // Tell the connection object to connect to server
                m_connection->ConnectToServer(endpoints);

                // Start Context Thread
                thrContext = std::thread([this]() { m_context.run(); });

            } catch(std::exception& e)
            {
                std::cerr << "Client Exception: " << e.what() << "\n";
            }
        }

        void Disconnect(){
            if(IsConnected())
                m_connection->Disconnect();

            m_context.stop();

            if(thrContext.joinable())
                thrContext.join();

            m_connection.reset();
        }

        bool IsConnected() {
            if(m_connection)
                return m_connection->IsConnected();
            else
                return false;
        }

        void Send(const message<T>& msg)
        {
            if (IsConnected())
                m_connection->Send(msg);
        }

        WSQueue<owned_message<T>>& Incoming(){
            return m_qMessagesIn;
        };

    protected:
        asio::error_code ec;
        asio::io_context m_context;
        std::thread thrContext;
        std::unique_ptr<connection<T>> m_connection;
    private:
        WSQueue<owned_message<T>> m_qMessagesIn;
    };
}


#endif //BROKERAPP_WSCLIENT_H
