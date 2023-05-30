from Message import Message
import hazelcast


class LoggingHazelRepository:
    def __init__(self):
        self.distributed_map = None
        self.client = hazelcast.HazelcastClient(cluster_members=["hazelcast1"])

    def add_map_name(self, map_name: str):
        self.distributed_map = self.client.get_map(map_name)

    def add_msg(self, msg: Message):
        self.distributed_map.lock(msg.msg_uuid)
        self.distributed_map.put(msg.msg_uuid, msg.msg).result()
        self.distributed_map.unlock(msg.msg_uuid)

    def get_messages(self):
        return list(self.distributed_map.values().result())
