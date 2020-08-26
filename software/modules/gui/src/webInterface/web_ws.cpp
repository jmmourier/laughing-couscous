#include "server_ws.hpp"
#include "web_ws.hpp"
#include "messages_handler.h"
using namespace std;
messages_handler mh;
using WsServer = SimpleWeb::SocketServer<SimpleWeb::WS>;

int start_server() {

    // WebSocket (WS)-server at port 8080 using 1 thread
    WsServer server;
    server.config.port = 1234;
    auto &echo = server.endpoint["^/echo/?$"];
    cout << "server started @"<<server.config.port <<endl;
    echo.on_message = [](shared_ptr<WsServer::Connection> connection, shared_ptr<WsServer::Message> message) {
        auto message_str = message->string();
        cout << "Server: Message received: \"" << message_str << "\" from " << connection.get() << endl;
        std::string ret;
        //evt(message_str, ret );
        mh.handle_message(message_str, ret);


        auto send_stream = make_shared<WsServer::SendStream>();
        *send_stream << ret;
        // connection->send is an asynchronous function
        connection->send(send_stream, [](const SimpleWeb::error_code &ec) {
            if(ec) {
                cout << "Server: Error sending message. " <<
                     // See http://www.boost.org/doc/libs/1_55_0/doc/html/boost_asio/reference.html, Error Codes for error code meanings
                     "Error: " << ec << ", error message: " << ec.message() << endl;
            }
        });
        cout << "Server: Sending message \"" << ret << "\" to " << connection.get() << endl;
    };

    echo.on_open = [](shared_ptr<WsServer::Connection> connection) {
        cout << "Server: Opened connection " << connection.get() << endl;
    };

    // See RFC 6455 7.4.1. for status codes
    echo.on_close = [](shared_ptr<WsServer::Connection> connection, int status, const string & /*reason*/) {
        cout << "Server: Closed connection " << connection.get() << " with status code " << status << endl;
    };

    // See http://www.boost.org/doc/libs/1_55_0/doc/html/boost_asio/reference.html, Error Codes for error code meanings
    echo.on_error = [](shared_ptr<WsServer::Connection> connection, const SimpleWeb::error_code &ec) {
        cout << "Server: Error in connection " << connection.get() << ". "
             << "Error: " << ec << ", error message: " << ec.message() << endl;
    };


    thread server_thread([&server]() {
        // Start WS-server
        server.start();
    });

    server_thread.join();
    return 0;
}

