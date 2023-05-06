from Domain.Message import Message
import requests
import random


class FacadeService:
    def __init__(self):
        self.logging_services = ["http://logging-service1:8080/log/",
                                 "http://logging-service2:8080/log/",
                                 "http://logging-service3:8080/log/"]

        self.message_service = "http://messages-service:8080/messages/"

    def get_messages(self) -> str:
        service = self.choose_random_logging()
        r_logging = requests.get(service)
        used = [service]
        while r_logging.status_code != 200:
            print(r_logging.status_code)
            service = self.choose_random_logging(used)
            r_logging = requests.get(service)
            used.append(service)
        messages = r_logging.json()

        r_messages = requests.get(self.message_service)
        print(r_messages.text)
        print(str(messages), r_messages.text)
        return (str(messages).replace("[", "").replace("]", '').replace("\'", "")) + "\n" + r_messages.text

    def log_message(self, msg: Message):
        service_chosen = self.choose_random_logging()
        used = [service_chosen]
        print("service_chosen: ", service_chosen)
        r_logging = requests.post(service_chosen, data=msg.json())
        print(r_logging.status_code)

        while r_logging.status_code != 200:
            service_chosen = self.choose_random_logging(used)
            print(service_chosen)
            r_logging = requests.post(service_chosen, data=msg.json())
            print(r_logging.status_code)
            used.append(service_chosen)
        return

    def choose_random_logging(self, already_used=[]):
        sevice = self.logging_services[random.randint(0, len(self.logging_services) - 1)]
        while sevice in already_used:
            sevice = self.logging_services[random.randint(0, len(self.logging_services) - 1)]
        return sevice
