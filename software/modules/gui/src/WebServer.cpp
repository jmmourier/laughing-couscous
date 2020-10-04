
#include "WebServer.h"

#include "WebPositionService.h"
#include "grpcpp/ext/proto_server_reflection_plugin.h"
#include "grpcpp/server_builder.h"

WebServer::WebServer(
    std::function<void(double pos_x_m, double pos_y_m, double orientation_rad)>
        on_set_position_callback)
    : web_position_service_(std::move(on_set_position_callback)) {}

void WebServer::start() {
  std::string server_address("0.0.0.0:9090");

  grpc::EnableDefaultHealthCheckService(true);
  grpc::reflection::InitProtoReflectionServerBuilderPlugin();

  grpc::ServerBuilder grpc_builder;

  grpc_builder.AddListeningPort(server_address,
                                grpc::InsecureServerCredentials());
  grpc_builder.RegisterService(&web_position_service_);

  server_ = grpc_builder.BuildAndStart();
  std::cout << "Server listening on " << server_address << std::endl;
  server_->Wait();
}

void WebServer::updatePosition(double pos_x_m, double pos_y_m,
                               double orientation_rad) {
  web_position_service_.updatePosition(pos_x_m, pos_y_m, orientation_rad);
}

void WebServer::stop() { server_->Shutdown(); }
