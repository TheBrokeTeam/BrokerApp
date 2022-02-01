//
// Created by Maykon Meneghel on 28/01/22.
//

#include "ConnectView.h"
#include "../Editor.h"
#include "../Helpers/JsonUtils.h"

ConnectView::ConnectView(Context *context) : Widget(context) {
    _title                  = "Connect View";
    _is_window              = true;
}

std::vector<char> vBuffer(20 * 1024);

void ConnectView::grabSomeData(asio::ip::tcp::socket& socket) {
    socket.async_read_some(asio::buffer(vBuffer.data(), vBuffer.size()),
                           [&](std::error_code ec, size_t length){
        if(!ec) {
            std::cout << "Read" << length << "bytes" << std::endl;
            for (int i=0; i<length; i++){
                std::cout << vBuffer[i];
            }
            grabSomeData(socket);
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

    if(ImGui::Button("Connect", ImVec2(200,50))){
        asio::error_code ec;
        asio::io_context context;
        asio::io_context::work idleWork(context);
        std::thread thrContext = std::thread([&](){ context.run(); });

        asio::io_service io_service;
        std::string const address = "stream.binance.com";

        asio::ip::tcp::resolver resolver(io_service);
        asio::ip::tcp::resolver::query query(address, "9443", asio::ip::resolver_query_base::numeric_service);
        asio::ip::tcp::resolver::iterator iter = resolver.resolve(query, ec);

        asio::ip::tcp::endpoint endpoint = iter->endpoint();
//        asio::ip::tcp::endpoint endpoint(asio::ip::make_address("18.176.240.156", ec), 9443);

        asio::ip::tcp::socket socket(context);
        socket.connect(endpoint, ec);

        if(!ec) {
            std::cout << "Connected" << std::endl;
        } else {
            std::cout << "Failed to connect to address. " << ec.message() << "Error code: " << ec.value() << std::endl;
            context.stop();
            if (thrContext.joinable())
                thrContext.join();
        }

        if(socket.is_open()){
            grabSomeData(socket);

            rapidjson::Document doc;
            doc.SetObject();
            rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();
            doc.AddMember("method", "SUBSCRIBE", allocator);
            rapidjson::Value params;
            params.SetArray();
            params.PushBack("btcusdt@kline_1m", allocator);
            doc.AddMember("params", params, allocator);
            doc.AddMember("id", 1, allocator);

//            std::string sRequest =
//                    "GET /ws/btcusdt@kline_1m HTTP/1.1\r\n"
//                    "Host: " + address +"\r\n"
//                    "Accept: */*\r\n\n"
//                    + json::Stringfy(doc) + "\r\n\n"
//                    "Connection: close\r\n\r\n";

//                    "GET /index.html HTTP/1.1\r\n"
//                    "Host: stream.binance.com\r\n"
//                    "Connection: close\r\n\r\n";


            std::string sRequest = json::Stringfy(doc);
            socket.write_some(asio::buffer(sRequest.data(), sRequest.size()), ec);

            std::this_thread::sleep_for(std::chrono::milliseconds(20000));

            context.stop();
            if (thrContext.joinable())
                thrContext.join();
        }

    }
}

void ConnectView::onPushStyleVar() {
    PushStyleColor(ImGuiCol_WindowBg,Editor::broker_dark_grey);
}
