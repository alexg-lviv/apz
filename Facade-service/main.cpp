#include <httpserver.hpp>
#include <uuid/uuid.h>
#include "cpr/cpr.h"
#include "spdlog/spdlog.h"

namespace hs = httpserver;

//std::string ip_facade = "172.19.0.2";
std::string ip_logging = "172.19.0.3";
std::string ip_messages = "172.19.0.4";

//std::string ip_facade = "127.0.0.1";
//std::string ip_logging = "127.0.0.1";
//std::string ip_messages = "127.0.0.1";

class facade_service_resource : public hs::http_resource {
public:
#ifdef IN_DOCKER
    std::shared_ptr<httpserver::http_response> render_GET(const hs::http_request &req) override {
#else
    const std::shared_ptr<httpserver::http_response> render_GET(const hs::http_request &req) override {
#endif

        spdlog::info("------------------------------------------------");
        spdlog::info("received GET request from the client");
        spdlog::info("sending GET request to http://" + ip_logging + ":8081/logging_service");
        cpr::Response r_logging = cpr::Get(cpr::Url("http://" + ip_logging + ":8081/logging_service"));
        spdlog::info("received response with status code: " + std::to_string(r_logging.status_code));

        spdlog::info("sending GET request to http://" + ip_messages + ":8082/messages_service");
        cpr::Response r_messages = cpr::Get(cpr::Url("http://"  + ip_messages + ":8082/messages_service"));
        spdlog::info("received response with status code: " + std::to_string(r_messages.status_code));

        spdlog::info("sending response to client");

        return std::shared_ptr<hs::http_response>(new hs::string_response("response from Logging-service: " + r_logging.text +
                                                                        "\nresponse from Messages-service: " + r_messages.text));
    }
#ifdef IN_DOCKER
     std::shared_ptr<httpserver::http_response> render_POST(const hs::http_request &req) override {
#else
     const std::shared_ptr<httpserver::http_response> render_POST(const hs::http_request &req) override {
#endif
        auto a = req.get_arg("text");
        spdlog::info("------------------------------------------------");
        spdlog::info("received POST request from the client");
        spdlog::info("client message: " + std::string(req.get_content()));
        spdlog::info("generating UUID");

        uuid_t uuid;
        uuid_generate_random(uuid);
        char uuid_str[32];
        uuid_unparse_upper(uuid, uuid_str);


        spdlog::info("UUID generated: " + std::string(uuid_str));
        spdlog::info("sending POST request to http://" + ip_logging + ":8081/logging_service");

        cpr::Response r_logging = cpr::Post(cpr::Url("http://" + ip_logging + ":8081/logging_service"),
                                            cpr::Payload{{uuid_str, std::string(req.get_content())}});

        spdlog::info("received response with status code: " + std::to_string(r_logging.status_code));

        return std::shared_ptr<hs::http_response>(new hs::string_response(""));
    }
};

int main(int argc, char** argv) {
    int port = 8080;
    spdlog::info("creating service on port " + std::to_string(port));
    hs::webserver ws = hs::create_webserver(port)
            .start_method(hs::http::http_utils::THREAD_PER_CONNECTION);

    facade_service_resource fsr;

    spdlog::info("configuring and registering resource /facade_service");
    fsr.disallow_all();
    fsr.set_allowing("GET", true);
    fsr.set_allowing("POST", true);

    ws.register_resource("/facade_service", &fsr);
    spdlog::info("starting service");
    ws.start(true);

    return 0;
}

