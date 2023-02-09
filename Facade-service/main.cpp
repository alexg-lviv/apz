#include <httpserver.hpp>
#include <uuid/uuid.h>
#include <iostream>
#include "cpr/cpr.h"
#include "spdlog/spdlog.h"

namespace hs = httpserver;

class facade_service_resource : public hs::http_resource {
public:
    const std::shared_ptr<hs::http_response> render_GET(const hs::http_request &req) override {
        spdlog::info("------------------------------------------------");
        spdlog::info("received GET request from the client");

        spdlog::info("sending GET request to http://localhost:8081/logging_service");
        cpr::Response r_logging = cpr::Get(cpr::Url("http://localhost:8081/logging_service"));
        spdlog::info("received responce with status code: " + std::to_string(r_logging.status_code));

        spdlog::info("sending GET request to http://localhost:8082/messages_service");
        cpr::Response r_messages = cpr::Get(cpr::Url("http://localhost:8082/messages_service"));
        spdlog::info("received responce with status code: " + std::to_string(r_messages.status_code));

        spdlog::info("sending responce to client");

        return std::shared_ptr<hs::http_response>(new hs::string_response("responce from Logging-sercie: " + r_logging.text +
                                                                        "\nresponce from Messages-service: " + r_messages.text));
    }

    const std::shared_ptr<hs::http_response> render_POST(const hs::http_request &req) override {
        spdlog::info("------------------------------------------------");
        spdlog::info("received GET request from the client");
        spdlog::info("client message: " + req.get_content());
        spdlog::info("generating UUID");

        uuid_t uuid;
        uuid_generate_random(uuid);
        char uuid_str[32];
        uuid_unparse_upper(uuid, uuid_str);

        spdlog::info("UUID generated: " + std::string(uuid_str));
        spdlog::info("sending POST request to http://localhost:8081/logging_service");

        cpr::Response r_logging = cpr::Post(cpr::Url("http://localhost:8081/logging_service"),
                                            cpr::Payload{{uuid_str, req.get_content()}});

        spdlog::info("received responce with status code: " + std::to_string(r_logging.status_code));

        return std::shared_ptr<hs::http_response>(new hs::string_response(""));
    }
};

int main(int argc, char** argv) {
    int port = 8080;
    spdlog::info("creating service on port " + std::to_string(port));
    hs::webserver ws = hs::create_webserver(port)
            .start_method(hs::http::http_utils::THREAD_PER_CONNECTION);

    facade_service_resource fsr;

    spdlog::info("configuring and registering resource /facade_sevice");
    fsr.disallow_all();
    fsr.set_allowing("GET", true);
    fsr.set_allowing("POST", true);

    ws.register_resource("/facade_service", &fsr);
    spdlog::info("starting service");
    ws.start(true);

    return 0;
}

