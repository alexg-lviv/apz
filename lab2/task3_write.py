import hazelcast

if __name__ == "__main__":
    client = hazelcast.HazelcastClient()

    my_queue = client.get_queue("queue")

    for i in range(1, 1001):
        print(i)
        while True:
            if my_queue.offer(i).result():
                break
    for i in range(2):
        while True:
            if my_queue.offer(-1).result():
                break
