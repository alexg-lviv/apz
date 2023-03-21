import uuid


class Message:
    def __init__(self, msg: str):
        self.msg = msg
        self.uuid = uuid.uuid4()
