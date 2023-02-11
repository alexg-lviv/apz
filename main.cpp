#include <iostream>
#include "hazelcast/client/hazelcast.h"

namespace hc = hazelcast::client;

int main(){
    hc::hazelcast_client hz = hazelcast::new_client().get();
    auto map = hz.get_map("my-distributed-map").get();


    for(int i = 0; i < 1000; ++i){
        map->put<int, int>(i, 2*i).get();
    }
    auto a = map->get<int, int>(1).get();
    std::cout<<a<<std::endl;


    std::cout<<"hi"<<std::endl;
}