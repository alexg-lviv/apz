from Message import Message
import hazelcast


class LoggingHazelRepository:
    def __init__(self):
        client = hazelcast.HazelcastClient(cluster_members=["hazelcast1"])
        self.distributed_map = client.get_map("messages-map")

    def add_msg(self, msg: Message):
        self.distributed_map.lock(msg.msg_uuid)
        self.distributed_map.put(msg.msg_uuid, msg.msg).result()
        self.distributed_map.unlock(msg.msg_uuid)

    def get_messages(self):
        return list(self.distributed_map.values().result())
