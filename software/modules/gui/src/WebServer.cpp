
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

void WebServer::setPosition(const PositionOrientation &position_orientation) {
    web_position_service_.setPosition(position_orientation);
}

void WebServer::setBattery(const float &battery_v) {
    web_position_service_.setBattery(battery_v);
}

void WebServer::setGrabberState(const bool &is_grabber_open) {
    web_position_service_.setGrabberState(is_grabber_open);
}

void WebServer::setMissionStartedAt(const long &mission_started_at) {
    web_position_service_.setMissionStartedAt(mission_started_at);
}

void WebServer::setMissionEndedAt(const long &mission_ended_at) {
    web_position_service_.setMissionEndedAt(mission_ended_at);
}

void WebServer::stop() {
    server_->Shutdown();
}
