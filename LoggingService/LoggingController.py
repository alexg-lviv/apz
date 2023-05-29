from fastapi import FastAPI
from LoggingService import LoggingService
from Message import Message


class LoggingController:
    def __init__(self):
        self.logging_service = LoggingService()

        self.app = FastAPI()

        @self.app.get("/log")
        def get_messages():
            print("getting all messages")
            return self.logging_service.get_all_messages()

        @self.app.post("/log")
        def post_message(msg: Message):
            print("message uuid: ", msg.msg_uuid, "\nmessage:   ", msg.msg)
            self.logging_service.log_new_message(msg)

        @self.app.get("/health")
        def healthcheck():
            return True


controller = LoggingController()
