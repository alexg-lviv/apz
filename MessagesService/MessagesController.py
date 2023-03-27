from fastapi import FastAPI


class MessagesController:
    def __init__(self):
        self.app = FastAPI()

        @self.app.get("/messages")
        def get_messages() -> str:
            print("got request")
            return "not yet implemented"


controller = MessagesController()
