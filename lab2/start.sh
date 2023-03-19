#!/bin/zsh -x

## uncomment for the first 3 tasks
#python3 task2_init_val.py


## uncomment for the first task without locking
#python3 task2_a_put_1000.py &
#python3 task2_a_put_1000.py &
#python3 task2_a_put_1000.py &


## uncomment for the second task pessimistic locking
#python3 task2_b_put_1000_pessimistic.py &
#python3 task2_b_put_1000_pessimistic.py &
#python3 task2_b_put_1000_pessimistic.py &


## uncomment for the third task optimistic locking
#python3 task2_c_put_1000_optimistic.py &
#python3 task2_c_put_1000_optimistic.py &
#python3 task2_c_put_1000_optimistic.py &


## uncomment for the fourth task, bounded queue
#python3 task3_write.py &
#python3 task3_read.py 1 &
#python3 task3_read.py 2 &