from Message import Message
from LoggingMemRepository import LoggingMemRepository
from LoggingHazelRepository import LoggingHazelRepository
import consul
import os
import socket


class LoggingService:
    def __init__(self):
        self.logging_repository = LoggingHazelRepository()
        self.id = os.environ["SERVICE_ID"]
        self.name = "logging"
        self.consul_service = consul.Consul(host="consul")
        hostname = socket.gethostname()
        check = consul.Check.http(f"http://{hostname}:8080/health", "10s", "2s", "20s")
        self.consul_service.agent.service.register(self.name, service_id=self.name + self.id, address=hostname,
                                                   port=8080, check=check)
        self.logging_repository.add_map_name(self.consul_service.kv.get('map-name')[1]["Value"].decode('utf-8'))

    def log_new_message(self, msg: Message):
        self.logging_repository.add_msg(msg)

    def get_all_messages(self):
        return self.logging_repository.get_messages()
