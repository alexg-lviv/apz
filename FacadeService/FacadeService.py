from Message import Message
import requests
import random
import hazelcast


class FacadeService:
    def __init__(self):
        self.logging_services = ["http://logging-service1:8080/log",
                                 "http://logging-service2:8080/log",
                                 "http://logging-service3:8080/log"]

        self.messages_services = ["http://messages-service1:8080/messages",
                                "http://messages-service2:8080/messages"]
        self.client = hazelcast.HazelcastClient(cluster_members=["hazelcast1"])
        self.mq_queue = self.client.get_queue("messages_queue")


    def get_messages(self) -> str:
        service = self.choose_random_service(self.logging_services)
        r_logging = requests.get(service)
        used = [service]
        while r_logging.status_code != 200:
            print(r_logging.status_code)
            service = self.choose_random_service(self.logging_services, used)
            r_logging = requests.get(service)
            used.append(service)
        messages = r_logging.json()

        service = self.choose_random_service(self.messages_services)
        used = [service]
        r_messages = requests.get(service)
        while r_messages.status_code != 200:
            print(r_messages.status_code)
            service = self.choose_random_service(self.messages_services, used)
            r_messages = requests.get(service)
            used.append(service)

        print(r_messages.text)
        print(str(messages), r_messages.text)
        return (str(messages).replace("[", "").replace("]", '').replace("\'", "")) + "\n" + (str(r_messages.text).replace("[", "").replace("]", '').replace("\'", ""))

    def log_message(self, msg: Message):
        service_chosen = self.choose_random_service(self.logging_services)
        used = [service_chosen]
        print("service_chosen: ", service_chosen)
        r_logging = requests.post(service_chosen, data=msg.json())
        print(r_logging.status_code)

        while r_logging.status_code != 200:
            service_chosen = self.choose_random_service(self.logging_services, used)
            print(service_chosen)
            r_logging = requests.post(service_chosen, data=msg.json())
            print(r_logging.status_code)
            used.append(service_chosen)

        while True:
            if self.mq_queue.offer(msg.msg).result():
                break
        return

    def choose_random_service(self, services_list: list, already_used=None):
        if already_used is None:
            already_used = []
        service = services_list[random.randint(0, len(services_list) - 1)]
        while service in already_used:
            service = services_list[random.randint(0, len(services_list) - 1)]
        return service
