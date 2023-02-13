#include <httpserver.hpp>
#include <iostream>
#include "spdlog/spdlog.h"
#include <unordered_map>


namespace hs = httpserver;

class logging_service_resource : public hs::http_resource {
public:
#ifdef IN_DOCKER
    std::shared_ptr<httpserver::http_response> render_GET(const hs::http_request &req) override {
#else
    const std::shared_ptr<httpserver::http_response> render_GET(const hs::http_request &req) override {
#endif
        spdlog::info("------------------------------------------------");
        spdlog::info("received GET request from the facade sevice");
        spdlog::info("creating result string");
        std::string result{};
        for(const auto& val: entries_map){
            result.append(std::string(val.second) + " ");
        }
        spdlog::info("sending responce: " + result);

        return std::shared_ptr<hs::http_response>(new hs::string_response(result));
    }

#ifdef IN_DOCKER
    std::shared_ptr<httpserver::http_response> render_POST(const hs::http_request &req) override {
#else
    const std::shared_ptr<httpserver::http_response> render_POST(const hs::http_request &req) override {
#endif
        spdlog::info("------------------------------------------------");
        spdlog::info("received POST request from the facade sevice");

        auto args = req.get_args();

        for(const auto& val: args){
            spdlog::info("UUOD: " + std::string(val.first) + "  value: " + std::string(val.second));
            entries_map[std::string(val.first)] = std::string(val.second);
        }
        spdlog::info("added value to local map");

        return std::shared_ptr<hs::http_response>(new hs::string_response(""));
    }
private:
    std::unordered_map<std::string, std::string> entries_map{};
};



int main(int argc, char** argv) {
    int port = 8081;
    spdlog::info("creating service on port " + std::to_string(port));

    hs::webserver ws = hs::create_webserver(port);

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