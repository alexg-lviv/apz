#include <httpserver.hpp>

namespace hs = httpserver;

class messages_service_responce : public hs::http_resource {
public:
    const std::shared_ptr<hs::http_response> render_GET(const hs::http_request& req) override{
        return std::shared_ptr<hs::http_response>(new hs::string_response("not implemented yet"));
    }
};

int main(int argc, char** argv) {

            .start_method(hs::http::http_utils::THREAD_PER_CONNECTION);

    messages_service_responce msr;
    msr.disallow_all();
    msr.set_allowing("GET", true);
    ws.register_resource("/messages_service", &msr);
    ws.start(true);

    return 0;
}




class my_class{
private:
    hs::webserver ws;
public:
    my_class(){
        ws{};
    }
};