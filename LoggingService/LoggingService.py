from Message import Message
from LoggingMemRepository import LoggingMemRepository
from LoggingHazelRepository import LoggingHazelRepository


class LoggingService:
    def __init__(self):
        self.logging_repository = LoggingHazelRepository()

    def log_new_message(self, msg: Message):
        self.logging_repository.add_msg(msg)

    def get_all_messages(self):
        return self.logging_repository.get_messages()
