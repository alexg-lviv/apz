from Message import Message
import requests
import random
import hazelcast
import consul
import os
import socket
import json

class FacadeService:
    def __init__(self):
        self.client = hazelcast.HazelcastClient(cluster_members=["hazelcast1"])
        self.mq_queue = self.client.get_queue("messages_queue")
        self.id = os.environ["SERVICE_ID"]
        self.name = "facade"
        self.consul_service = consul.Consul(host="consul")
        hostname = socket.gethostname()
        check = consul.Check.http(f"http://{hostname}:8080/health", "10s", "2s", "20s")
        self.consul_service.agent.service.register(self.name, service_id=self.name+self.id, address=hostname, port=8080, check=check)

        self.endpoints = {
            "logging": "/log",
            "messages": "/messages"
        }
        self.ports = {
            "logging": 8080,
            "messages": 8080
        }

    def get_messages(self) -> str:
        service = self.get_service_addr_from_consul("logging")
        r_logging = requests.get(service)
        while r_logging.status_code != 200:
            print(r_logging.status_code)
            service = self.get_service_addr_from_consul("logging")
            r_logging = requests.get(service)
        messages = r_logging.json()

        service = self.get_service_addr_from_consul("messages")
        r_messages = requests.get(service)
        while r_messages.status_code != 200:
            print(r_messages.status_code)
            service = self.get_service_addr_from_consul("messages")
            r_messages = requests.get(service)

        print(r_messages.text)
        print(str(messages), r_messages.text)
        return (str(messages).replace("[", "").replace("]", '').replace("\'", "")) + "\n" + (str(r_messages.text).replace("[", "").replace("]", '').replace("\'", ""))

    def log_message(self, msg: Message):
        service_chosen = self.get_service_addr_from_consul("logging")
        r_logging = requests.post(service_chosen, data=msg.json())
        print(r_logging.status_code)

        while r_logging.status_code != 200:
            service_chosen = self.get_service_addr_from_consul("logging")
            print(service_chosen)
            r_logging = requests.post(service_chosen, data=msg.json())
            print(r_logging.status_code)

        while True:
            if self.mq_queue.offer(msg.msg).result():
                break
        return

    def get_service_addr_from_consul(self, name):
        AAAA = self.consul_service.health.service(name)[1]
        AAAA = random.choice(AAAA)["Service"]
        addr = AAAA["Address"]
        port = AAAA["Port"]
        return f"http://{addr}:{port}{self.endpoints[name]}"

