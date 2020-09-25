
#include "../include/WebServer.h"

#include "grpcpp/ext/proto_server_reflection_plugin.h"
#include "grpcpp/health_check_service_interface.h"
#include "grpcpp/impl/codegen/server_context.h"
#include "grpcpp/impl/codegen/status.h"
#include "grpcpp/server.h"
#include "grpcpp/server_builder.h"
#include "robot.grpc.pb.h"

/**
 * @brief Small example of requesting. The response will contain the speed
 * requested * 2
 */
class RobotService final : public web_service::MotionService::Service {
  ::grpc::Status startMove(::grpc::ServerContext *context,
                           const ::web_service::SpeedRequest *request,
                           ::web_service::SpeedResponse *response) {
    response->set_speed(request->speed() * 2);
    return grpc::Status::OK;
  }

  ::grpc::Status stopMove(::grpc::ServerContext *context,
                          const ::web_service::Empty *request,
                          ::web_service::SpeedResponse *response) {
    response->set_speed(0);
    return grpc::Status::OK;
  }
};

void WebServer::start() {
  RobotService robot_service;

  std::string server_address("0.0.0.0:9090");

  grpc::EnableDefaultHealthCheckService(true);
  grpc::reflection::InitProtoReflectionServerBuilderPlugin();

  grpc::ServerBuilder grpc_builder;

  grpc_builder.AddListeningPort(server_address,
                                grpc::InsecureServerCredentials());
  grpc_builder.RegisterService(&robot_service);

  std::unique_ptr<grpc::Server> server(grpc_builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;
  server->Wait();
}
void WebServer::stop() {}