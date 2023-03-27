from Message import Message


class LoggingMemRepository:
    def __init__(self):
        self.messages_map = dict()

    def add_msg(self, msg: Message):
        self.messages_map[msg.msg_uuid] = msg.msg

    def get_messages(self):
        return list(self.messages_map.values())
