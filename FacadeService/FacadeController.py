import uuid
from fastapi import FastAPI
from fastapi.responses import PlainTextResponse
from FacadeService import FacadeService
from Message import Message
import uvicorn


class FacadeController:
    def __init__(self):
        self.app = FastAPI()

        self.facade_service = FacadeService()

        @self.app.get("/log", response_class=PlainTextResponse)
        def get_messages():
            return self.facade_service.get_messages()

        @self.app.post("/log")
        def post_msg(msg: Message):
            msg.msg_uuid = uuid.uuid1()
            return self.facade_service.log_message(msg)

        @self.app.get("/health")
        def healthcheck():
            return True


controller = FacadeController()

if __name__ == "__main__":
    uvicorn.run(controller.app)
