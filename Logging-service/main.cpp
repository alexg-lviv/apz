#include <httpserver.hpp>
#include "oneapi/tbb/concurrent_hash_map.h"
#include <iostream>


namespace hs = httpserver;


class logging_service_resource : public hs::http_resource {
public:
    const std::shared_ptr<hs::http_response> render_GET(const hs::http_request& req) override{
        std::string result{};
        for(const auto& val: entries_map){
            result.append(val.second + " ");
        }
        return std::shared_ptr<hs::http_response>(new hs::string_response(result));
    }

    const std::shared_ptr<hs::http_response> render_POST(const hs::http_request& req) override{
        auto args = req.get_args();
        for(const auto& val: args){
            tbb::concurrent_hash_map<std::string, std::string>::accessor a;
            entries_map.insert(a, val.first);
            a->second = val.second;
            a.release();
        }
        return std::shared_ptr<hs::http_response>(new hs::string_response(""));
    }
private:
    tbb::concurrent_hash_map<std::string, std::string> entries_map{};
};



int main(int argc, char** argv) {

    hs::webserver ws = hs::create_webserver(8081)
            .start_method(hs::http::http_utils::THREAD_PER_CONNECTION);

    logging_service_resource lsr;

    lsr.disallow_all();
    lsr.set_allowing("GET", true);
    lsr.set_allowing("POST", true);

    ws.register_resource("/logging_service", &lsr);
    ws.start(true);

    return 0;
}