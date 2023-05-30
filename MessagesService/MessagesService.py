import asyncio
from fastapi import FastAPI
from contextlib import asynccontextmanager
from MessagesMemRepository import MessagesMemRepository
import hazelcast
import consul
import os
import socket


class MessagesService:
    def __init__(self):
        self.repository = MessagesMemRepository()
        self.client = hazelcast.HazelcastClient(cluster_members=["hazelcast1"])
        self.loop = asyncio.get_running_loop()
        self.id = os.environ["SERVICE_ID"]
        self.name = "messages"
        self.consul_service = consul.Consul(host="consul")
        hostname = socket.gethostname()
        check = consul.Check.http(f"http://{hostname}:8080/health", "10s", "2s", "20s")
        self.consul_service.agent.service.register(self.name, service_id=self.name+self.id, address=hostname, port=8080, check=check)
        self.mq_queue = self.client.get_queue(self.consul_service.kv.get('queue-name')[1]["Value"].decode('utf-8'))


    @asynccontextmanager
    async def lifespan(self, app: FastAPI):
        self.create_receive_messages_task()
        yield

    async def messages_reader(self):
        while True:
            if self.mq_queue.is_empty().result():
                await asyncio.sleep(0.1)
            else:
                msg = self.mq_queue.take().result()
                print(msg)
                self.repository.add_msg(msg)

    def create_receive_messages_task(self):
        self.loop.create_task(self.messages_reader())

    def get_messages(self):
        return self.repository.get_messages()