#include <httpserver.hpp>
#include "oneapi/tbb/concurrent_hash_map.h"
#include <iostream>
#include "spdlog/spdlog.h"


namespace hs = httpserver;


class logging_service_resource : public hs::http_resource {
public:
    const std::shared_ptr<hs::http_response> render_GET(const hs::http_request& req) override{
        spdlog::info("------------------------------------------------");
        spdlog::info("received GET request from the facade sevice");
        spdlog::info("creating result string");
        std::string result{};
        for(const auto& val: entries_map){
            result.append(val.second + " ");
        }
        spdlog::info("sending responce: " + result);

        return std::shared_ptr<hs::http_response>(new hs::string_response(result));
    }

    const std::shared_ptr<hs::http_response> render_POST(const hs::http_request& req) override{
        spdlog::info("------------------------------------------------");
        spdlog::info("received POST request from the facade sevice");

        auto args = req.get_args();

        for(const auto& val: args){
            spdlog::info("UUOD: " + val.first + "  value: " + val.second);
            tbb::concurrent_hash_map<std::string, std::string>::accessor a;
            entries_map.insert(a, val.first);
            a->second = val.second;
            a.release();
        }
        spdlog::info("added value to local map");

        return std::shared_ptr<hs::http_response>(new hs::string_response(""));
    }
private:
    tbb::concurrent_hash_map<std::string, std::string> entries_map{};
};



int main(int argc, char** argv) {
    int port = 8081;
    spdlog::info("creating service on port " + std::to_string(port));

    hs::webserver ws = hs::create_webserver(port)
            .start_method(hs::http::http_utils::THREAD_PER_CONNECTION);

    logging_service_resource lsr;
    spdlog::info("configuring and registering resource /logging_service");

    lsr.disallow_all();
    lsr.set_allowing("GET", true);
    lsr.set_allowing("POST", true);

    ws.register_resource("/logging_service", &lsr);

    spdlog::info("starting service");
    ws.start(true);

    return 0;
}