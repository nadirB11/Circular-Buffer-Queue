# Circular-Buffer-Queue
Queue based on a circular buffer based on a fixed array in C
A circular buffer is based on an array of fixed size which is virtually connected end to end, i.e. when the end of the array is reached, writing is done at the start of the array. In our case as the buffer is used for a queue, when the maximum capacity is reached, an error code should be returned when trying to add more elements to the queue. Attempting to dequeue an element from an empty queue should also result in an error.
