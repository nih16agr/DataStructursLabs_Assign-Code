#include <stdio.h>
#include <stdlib.h>

struct dequeue
{
    int *queue_array;
    int MAX,front,rear;
};
struct dequeue create(int initialMAX);
struct dequeue insertLeft(struct dequeue one);
struct dequeue insertRight(struct dequeue one);
struct dequeue deleteLeft(struct dequeue one);
struct dequeue deleteRight(struct dequeue one);
void display(struct dequeue one);


struct dequeue create(int initialMAX)
{
	struct dequeue one;
    one.MAX = initialMAX;
	one.queue_array = (int*)malloc(one.MAX*sizeof(int));
	one.front = -1;
	one.rear = -1;
	return one;
}
struct dequeue insertRight(struct dequeue one)
{
    printf("Enter the integer value to be stored : ");
    int data;
    scanf("%d",&data);
    if (one.rear == one.MAX - 1)
    {
    	one.MAX = 2*one.MAX;
    	one.queue_array = realloc(one.queue_array,one.MAX*sizeof(int));
    	one.rear = one.rear + 1;
        one.queue_array[one.rear] = data;
    }
    else
    {
        if (one.front == - 1)
        /*If queue is initially empty */
        one.front = 0;
        one.rear = one.rear + 1;
        one.queue_array[one.rear] = data;
    }
    return one;
}
struct dequeue insertLeft(struct dequeue one)
{
    printf("Enter the integer value to be stored : ");
    int data;
    scanf("%d",&data);
    if (one.rear == one.MAX - 1)
    {
    	one.MAX = 2*one.MAX;
    	one.queue_array = realloc(one.queue_array,one.MAX*sizeof(int));
    	one.rear = one.rear + 1;
    	for(int i = one.rear;i>0;i--)
        	one.queue_array[i] = one.queue_array[i-1];
        one.queue_array[one.front] = data;
    }
    else
    {
        if (one.front == - 1)
        /*If queue is initially empty */
        one.front = 0;
        one.rear = one.rear + 1;
        for(int i = one.rear;i>0;i--)
        	one.queue_array[i] = one.queue_array[i-1];
        one.queue_array[one.front] = data;
    }
    return one;
}
struct dequeue deleteLeft(struct dequeue one)
{
    if (one.front == - 1)
    	printf("Queue Underflow \n");
    else
    {
        printf("%d",one.queue_array[one.front]);
        for(int i = 0;i<one.rear;i++)
        	one.queue_array[i] = one.queue_array[i+1];
        one.rear = one.rear-1;
        if(one.rear == (one.MAX/2-1))
        {
        	one.MAX = one.MAX/2;
        	one.queue_array = realloc(one.queue_array,one.MAX*sizeof(int));
        }
    }
    return one;
}
struct dequeue deleteRight(struct dequeue one)
{
    if (one.front == - 1)
        printf("Queue Underflow \n");
    else
    {
        printf("%d",one.queue_array[one.rear]);
        one.rear = one.rear-1;
        if(one.rear == (one.MAX/2-1))
        {
        	one.MAX = one.MAX/2;
        	one.queue_array = realloc(one.queue_array,one.MAX*sizeof(int));
        }
    }
    return one;
}
void display(struct dequeue one)
{
	if (one.front == - 1)
    	printf("Queue Underflow \n");
    else
    	for(int i = 0;i<= one.rear ; i++)
    		printf("%d ",one.queue_array[i]);
        printf("\n%d",one.MAX*4);
}

void main()
{
    struct dequeue myqueue = create(4);
    int ch;
 
    printf("\n 1 - Insert in left");
    printf("\n 2 - Insert in right");
    printf("\n 3 - delete in left");
    printf("\n 4 - delete in right");
    printf("\n 5 - display");
    printf("\n 6 - exit");
 
    while (1)
    {
        printf("\n Enter choice : ");
        scanf("%d", &ch);
        switch(ch)
        {
        case 1:
            myqueue = insertLeft(myqueue);
            break;
        case 2:
            myqueue = insertRight(myqueue);
            break;
        case 3:
            myqueue = deleteLeft(myqueue);
            break;
        case 4:
            myqueue = deleteRight(myqueue);
            break;
        case 5:
            display(myqueue);
            break;            
        case 6:
            exit(0);
        default:
            printf("\n Wrong choice menu");
        }
    }
}