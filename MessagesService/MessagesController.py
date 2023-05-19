from fastapi import FastAPI
from MessagesService import MessagesService
import asyncio
from fastapi.responses import PlainTextResponse


class MessagesController:
    def __init__(self):
        self.service = MessagesService()

        self.app = FastAPI(lifespan=self.service.lifespan)

        @self.app.get("/messages", response_class=PlainTextResponse)
        def get_messages() -> str:
            print("got request")
            return str(self.service.get_messages())


controller = MessagesController()
# controller.read_msg()