import hazelcast
from time import sleep

if __name__ == "__main__":
    client = hazelcast.HazelcastClient()

    my_map = client.get_map("my-distributed-map").blocking()
    key = 1
    for i in range(1, 1001):
        while True:
            old_val = my_map.get(key)
            new_val = old_val + 1
            sleep(0.001)
            if my_map.replace_if_same(key, old_val, new_val):
                break
