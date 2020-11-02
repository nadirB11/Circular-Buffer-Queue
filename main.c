#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

//////////
#define BUFFER_MAX_SIZE 8
#define QUEUE_IS_FULL 1
#define QUEUE_IS_EMPTY 2

///////Prototypes
typedef struct queue queue_t;

void init (queue_t* q);

int enqueue (queue_t* q, int val);

int dequeue (queue_t* q, int* val);

int menu();

bool is_empty(queue_t* q);

bool is_full(queue_t* q);

///////Structure and Function definitions
typedef struct queue{
    uint8_t* buffer;            //to store array address
    int head;           //follows write operation
    int tail;           //follows read operation
    int len;
    int maxlen;         //maximum length of the buffer
}queue_t;

void init (queue_t* q){         //initialization function
    q->head = 0;
    q->tail = 0;
    q->len = 0;
    q->maxlen = BUFFER_MAX_SIZE;    //assuming buffer max size to be 8
}

int enqueue (queue_t* q, int val){  //function to add element to queue
    int next;
    next = q->head+1;           //points to next write operation location

    if (next>=q->maxlen){       //reset head pointer if it reaches max length of queue
        next=0;
    }

    if (next==q->tail){         //if head pointer equates tail pointer, it means the queue became full
        return QUEUE_IS_FULL;
    }

    q->buffer[q->head] = val;       // write input in queue
    q->len++;
    printf("\n%d added to queue", val); //success message
    q->head = next;     //point to next write
    return 0;
}

int dequeue (queue_t* q, int* val){     //function to remove element from queue
    int next;

    if (q->tail==q->head)               //inverse to previous case, if head and tail equate, that means queue is empty
        return QUEUE_IS_EMPTY;

    next = q->tail+1;               //increment next tail pointer
    if (next>=q->maxlen)        //reset tail pointer if it reaches max value
        next=0;

    *val = q->buffer[q->tail];      //read from buffer
    q->len--;
    printf("\n%d removed from queue\n", *val);  //success message
    q->tail=next;           //point to next read

    return 0;
}

int menu (){                    //simple menu to choose operation and request input
    printf("\n---------------------------------------------------");
    printf("\n\nPlease choose one of the following:\n");
    printf("1-Enqueue element \n");
    printf("2-Dequeue element \n");
    printf("3-Check queue status\n");
    printf("Your selection: ");
    int selection;
    scanf("%d", &selection);
    return selection;
}

bool is_empty(queue_t* q){          //function to check if queue is empty
    if (q->len==0)
    {
        printf("Queue is empty\n");
        return 1;
    }
    else
        return 0;

}

bool is_full(queue_t* q){           //function to check if queue is full
    if (q->len==q->maxlen-1)
    {
        printf("Queue is full\n");
        return 1;
    }
    else
        return 0;

}
////////////////Main function

int main()
{

    queue_t q;
    uint8_t buffer_array [BUFFER_MAX_SIZE];
    init(&q);
    q.buffer=buffer_array;      //equating buffer pointer and created array

    bool loop_state=1;
    int selection;

    while (loop_state==1)
    {
        selection = menu();

        if (selection==1)
        {
            int data_in;        //variable to send data to the queue
            printf("\nEnter data element:");
            scanf("%d", &data_in);

            if(QUEUE_IS_FULL==enqueue(&q, data_in))
            {
                                                    //Error message if queue is full
                assert(false == is_full(&q));
            }
        }

        else if (selection==2)
        {
            int data_out;           //Variable to retrieve data from buffer
            if(QUEUE_IS_EMPTY==dequeue(&q, &data_out))
            {
                                                    //Error message if queue is empty
                assert(false == is_empty(&q));
            }
        }

        else if (selection==3)
        {
            if (is_empty(&q)==0)
            {
                if (is_full(&q)==0)
                    printf ("Space is available in queue");
            }
        }

        else
        {
            loop_state=0;               //to break the loop
            printf("\nUndefined choice, please re-run the program.\n");
        }

    }

    return 0;
}
