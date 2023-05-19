

class MessagesMemRepository:
    def __init__(self):
        self.messages = []
    def add_msg(self, msg):
        self.messages.append(msg)

    def get_messages(self):
        return self.messages