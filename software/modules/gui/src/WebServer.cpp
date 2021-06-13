
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

void WebServer::setRobotState(const RobotState &robot_state) {
    web_position_service_.setRobotState(robot_state);
}

RobotState WebServer::getRobotState() {
    return web_position_service_.getRobotState();
};

void WebServer::stop() {
    server_->Shutdown();
}
