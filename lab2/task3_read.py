import hazelcast
import sys

num = sys.argv[1]

if __name__ == "__main__":
    client = hazelcast.HazelcastClient()

    my_queue = client.get_queue("queue")

    msgs_num = 0

    while True:
        val = my_queue.take().result()
        msgs_num += 1
        if val == -1:
            break
        print(f"reader {num} got {msgs_num} messages")