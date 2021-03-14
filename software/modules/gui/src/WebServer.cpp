
#include "WebServer.h"

#include "WebPositionService.h"
#include "grpcpp/ext/proto_server_reflection_plugin.h"
#include "grpcpp/server_builder.h"

void WebServer::registerWebServerRequestListener(
    const std::weak_ptr<IWebServerRequestListener> &webserver_listener) {
    web_position_service_.registerWebServerRequestListener(webserver_listener);
}

void WebServer::start() {
    std::string server_address("0.0.0.0:9090");

    grpc::EnableDefaultHealthCheckService(true);
    grpc::reflection::InitProtoReflectionServerBuilderPlugin();

    grpc::ServerBuilder grpc_builder;

    grpc_builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    grpc_builder.RegisterService(&web_position_service_);

    server_ = grpc_builder.BuildAndStart();
    std::cout << "Server listening on " << server_address << std::endl;
    server_->Wait();
}

void WebServer::setPosition(
    const double &pos_x_m,
    const double &pos_y_m,
    const double &orientation_rad) {
    web_position_service_.setPosition(pos_x_m, pos_y_m, orientation_rad);
}

// void WebServer::setSpeed(const int &motor1, const int &motor2) {
//     web_position_service_.setSpeed(motor1, motor2);
// }

void WebServer::stop() {
    server_->Shutdown();
}
