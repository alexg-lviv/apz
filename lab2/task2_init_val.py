import hazelcast

if __name__ == "__main__":
    client = hazelcast.HazelcastClient()

    my_map = client.get_map("my-distributed-map").blocking()
    key = 1
    my_map.put(key, 0)