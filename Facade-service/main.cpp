#include <httpserver.hpp>
#include <uuid/uuid.h>
#include <iostream>
#include "cpr/cpr.h"

namespace hs = httpserver;

class facade_service_resource : public hs::http_resource {
public:
    const std::shared_ptr<hs::http_response> render_GET(const hs::http_request &req) override {

        cpr::Response r_logging = cpr::Get(cpr::Url("http://localhost:8081/logging_service"));
        cpr::Response r_messages = cpr::Get(cpr::Url("http://localhost:8082/messages_service"));
        return std::shared_ptr<hs::http_response>(new hs::string_response("responce from Logging-sercie: " + r_logging.text +
                                                                        "\nresponce from Messages-service: " + r_messages.text));
    }

    const std::shared_ptr<hs::http_response> render_POST(const hs::http_request &req) override {
        uuid_t uuid;
        uuid_generate_random(uuid);
        char uuid_str[32];
        uuid_unparse_upper(uuid, uuid_str);

        cpr::Response r_logging = cpr::Post(cpr::Url("http://localhost:8081/logging_service"),
                                            cpr::Payload{{uuid_str, req.get_content()}});



        return std::shared_ptr<hs::http_response>(new hs::string_response(""));
    }
};

int main(int argc, char** argv) {
    hs::webserver ws = hs::create_webserver(8080)
            .start_method(hs::http::http_utils::THREAD_PER_CONNECTION);

    facade_service_resource fsr;

    fsr.disallow_all();
    fsr.set_allowing("GET", true);
    fsr.set_allowing("POST", true);

    ws.register_resource("/facade_service", &fsr);
    ws.start(true);

    return 0;
}

