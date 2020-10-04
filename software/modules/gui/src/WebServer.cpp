
#include "../include/WebServer.h"
#include "grpcpp/ext/proto_server_reflection_plugin.h"
#include "grpcpp/health_check_service_interface.h"
#include "grpcpp/security/server_credentials.h"
#include "grpcpp/server_builder.h"
#include <string>

void WebServer::start() {

  std::string server_address("0.0.0.0:9090");

  grpc::EnableDefaultHealthCheckService(true);
  grpc::reflection::InitProtoReflectionServerBuilderPlugin();

  grpc::ServerBuilder grpc_builder;

  grpc_builder.AddListeningPort(server_address,
                                grpc::InsecureServerCredentials());

  std::unique_ptr<grpc::Server> server(grpc_builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;
  server->Wait();
}
void WebServer::stop() {}