import asyncio
from fastapi import FastAPI
from contextlib import asynccontextmanager
from MessagesMemRepository import MessagesMemRepository
import hazelcast


class MessagesService:
    def __init__(self):
        self.repository = MessagesMemRepository()
        self.client = hazelcast.HazelcastClient(cluster_members=["hazelcast1"])
        self.mq_queue = self.client.get_queue("messages_queue")
        self.loop = asyncio.get_running_loop()

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