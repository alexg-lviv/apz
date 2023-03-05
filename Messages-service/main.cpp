#include <httpserver.hpp>
#include "spdlog/spdlog.h"

namespace hs = httpserver;

class messages_service_response : public hs::http_resource {
public:
#ifdef IN_DOCKER
    std::shared_ptr<httpserver::http_response> render_GET(const hs::http_request &req) override {
#else
    const std::shared_ptr<httpserver::http_response> render_GET(const hs::http_request &req) override {
#endif
        spdlog::info("------------------------------------------------");
        spdlog::info("received GET request from the facade service");
        spdlog::info("sending response");
        return std::shared_ptr<hs::http_response>(new hs::string_response("not implemented yet"));
    }
};

int main(int argc, char** argv) {
    int port = 8082;
    spdlog::info("creating service on port " + std::to_string(port));
    hs::webserver ws = hs::create_webserver(port)
            .start_method(hs::http::http_utils::THREAD_PER_CONNECTION);

    spdlog::info("configuring and registering resource /messages_service");
    messages_service_response msr;
    msr.disallow_all();
    msr.set_allowing("GET", true);
    ws.register_resource("/messages_service", &msr);

    spdlog::info("starting service");
    ws.start(true);

    return 0;
}