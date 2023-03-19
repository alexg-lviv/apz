import hazelcast
from time import sleep

if __name__ == "__main__":
    client = hazelcast.HazelcastClient()

    my_map = client.get_map("my-distributed-map").blocking()
    key = 1
    for i in range(1, 1001):
        val = my_map.get(key)
        sleep(0.001)
        val += 1
        my_map.put(key, val)
