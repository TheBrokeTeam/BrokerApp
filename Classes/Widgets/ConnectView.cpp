//
// Created by Maykon Meneghel on 28/01/22.
//

#include "ConnectView.h"
#include "../Editor.h"
#include "../Helpers/JsonUtils.h"

ConnectView::ConnectView(Context *context)
        : Widget(context) {
    _title                  = "Connect View";
    _is_window              = true;
}

std::vector<char> vBuffer(20 * 1024);
void ConnectView::GrabSomeData(asio::ip::tcp::socket& socket) {
    socket.async_read_some(asio::buffer(vBuffer.data(), vBuffer.size()),
                           [&](std::error_code ec, size_t length){
        if(!ec) {
            std::cout << "Read" << length << "bytes" << std::endl;
            for (int i=0; i<length; i++){
                std::cout << vBuffer[i];
            }
            GrabSomeData(socket);
        }
    });
}

void ConnectView::updateVisible(float dt) {
    Widget::updateVisible(dt);
    //change color text
    PushStyleColor(ImGuiCol_Text,Editor::broker_black);

    //change background of frames
    PushStyleColor(ImGuiCol_FrameBg,Editor::broker_white);
    PushStyleColor(ImGuiCol_FrameBgActive,Editor::broker_white);
    PushStyleColor(ImGuiCol_FrameBgHovered,Editor::broker_white);

    //change background of items on combos
    PushStyleColor(ImGuiCol_PopupBg,Editor::broker_white);

    //change background from other buttons
    PushStyleColor(ImGuiCol_Button,Editor::broker_yellow);
    PushStyleColor(ImGuiCol_ButtonActive,Editor::broker_yellow_active);
    PushStyleColor(ImGuiCol_ButtonHovered,Editor::broker_yellow_hover);

    if(ImGui::Button(_is_connected ? "Disconnect" : "Connect", ImVec2(200,50))){
        _is_connected = !_is_connected;
        if(_is_connected) {
            client.Connect("localhost", 3200);
        } else {
            client.Disconnect();
        }
    }

    if(ImGui::Button("OneShot", ImVec2(200,50))){
        asio::error_code ec;

        asio::io_context asioContext;
        asio::ip::tcp::socket socket(asioContext);

        asio::io_context::work idleWork(asioContext);
        std::thread thrContext = std::thread([&](){ asioContext.run(); });

        asio::io_service io_service;
        std::string const address = "localhost";
        int const port = 3200;

        asio::ip::tcp::resolver resolver(io_service);
        asio::ip::tcp::resolver::query query(address, std::to_string(port), asio::ip::resolver_query_base::numeric_service);
        asio::ip::tcp::resolver::iterator iter = resolver.resolve(query, ec);

        asio::ip::tcp::endpoint endpoint = iter->endpoint();

        socket.connect(endpoint, ec);

        if(!ec) {
            std::cout << "Connected" << std::endl;
        } else {
            std::cout << "Failed to connect to address. " << ec.message() << "Error code: " << ec.value() << std::endl;
            asioContext.stop();
            socket.release();
            if (thrContext.joinable())
                thrContext.join();
        }

        if(socket.is_open()) {

            GrabSomeData(socket);

            std::string sRequest =
                    "GET /ws/btcbrl@kline_1m HTTPS/1.1\r\n"
                    "Host: " + address + ":" + std::to_string(port) + "\r\n"
                    "Origin: wss://" + address + ":" + std::to_string(port) + "\r\n"
                    "Upgrade: websocket\r\n"
                    "Connection: Upgrade\r\n"
                    "Sec-WebSocket-Key: dGhlIHNhbXBsZSBub25jZQ==\r\n"
                    "Sec-WebSocket-Version: 13\r\n\r\n";

            socket.write_some(asio::buffer(sRequest.data(), sRequest.size()), ec);

//            rapidjson::Document doc;
//            doc.SetObject();
//            rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();
//            doc.AddMember("method", "SUBSCRIBE", allocator);
//            rapidjson::Value params;
//            params.SetArray();
//            params.PushBack("btcusdt@kline_1m", allocator);
//            doc.AddMember("params", params, allocator);
//            doc.AddMember("id", 1, allocator);
//
//            using namespace std::chrono_literals;
//            std::this_thread::sleep_for(30000ms);

//            thrContext.stop();
            if (thrContext.joinable())
                thrContext.join();
        }
    }

    if(ImGui::Button("Ping", ImVec2(200,50))) {
        if (client.IsConnected()) {
            client.Hi();
        }
    }

}

void ConnectView::onPushStyleVar() {
    PushStyleColor(ImGuiCol_WindowBg,Editor::broker_dark_grey);
}
