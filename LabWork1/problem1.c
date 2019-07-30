#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node
{
    struct node *prev;
    int rollno;
    char name[50];
    char dob[50];
    char address[100];
    char phoneno[50];
    struct node *next;
}*first,*last;


int MAX = 100;
int *queue_array ;
int front = -1;
int rear = -1;
int checkQueue();
void pushInQueue(int unusedroll);
int popOutQueue();	 

void pushInQueue(int unusedroll)
{
    if (rear == MAX - 1)
    printf("Queue Overflow \n");
    else
    {
        if (front == - 1)
	        /*If queue is initially empty */
        front = 0;
        rear = rear + 1;
        queue_array[rear] = unusedroll;
    }
}

int popOutQueue()
{
    if(front == rear)
	{
		int d = queue_array[front];
	    front = rear =-1;
	    return d;
    }
	else
	{
	    int d = queue_array[front];
	    queue_array[front] = 0;
	    front = front+1;
	    return d;
	}
}

int checkQueue()
{
	if (front == -1 && rear ==-1)
		return 0;
	else
		return 1;
}

void insert(char name[],char dob[],char address[],char phoneno[]);
void delete();
void search();
void modify();
void sort();
void printlist();

int count = 0;

/* insertion */
void insert(char name[],char dob[],char address[],char phoneno[])
{
	int unusedroll = 0;
	if(checkQueue() == 1)
		 unusedroll = popOutQueue(); 

	struct node *temp =(struct node*)malloc(sizeof(struct node));
    int i ;
 	if(first == NULL)
 	{
    	first = temp ;
    	temp->next = first;
    	temp->prev = first;
    	last = first;
    	
    	if(unusedroll == 0)
    		first->rollno = 101;
    	else
    		first->rollno = unusedroll;
    	printf(" First node inserted with roll no:%d\n",first->rollno);
    	i = first->rollno%100;
 	}
    else
    {
    	if(unusedroll == 0)
    	{
    		last->next = temp;
    		temp->prev = last;
    		temp->next = first;
    		first->prev = temp;
			last = last->next;
            temp->rollno = (temp->prev->rollno)+1;
			i = temp->rollno;
    	}
    	else
    	{
    		
    		if(unusedroll==101)
    		{
    			temp->prev=last;
    			temp->next=first;
    			first->prev=temp;
    			last->next=temp;
    			first = temp;
    		}
    		else
    		{
    			struct node *temp1 = first;
    			while(!((temp1->rollno < unusedroll) && (temp1->next->rollno > unusedroll))) 
    			temp1 = temp1->next;
    			temp->prev = temp1;
	    		temp->next = temp1->next;
	    		temp1->next->prev = temp;
	    		temp1->next = temp;
	    		temp1 = NULL;
   				free(temp1);
    		}
    		i = unusedroll;
    		
    	}
    	
    }

    strcpy(temp->name,name);
    strcpy(temp->dob,dob);
    strcpy(temp->address,address);
    strcpy(temp->phoneno,phoneno); //phone no int krne se kyu ni ho rha, provided strcpy is not used and atoi() is used in main
    count++;
    temp = NULL;
    free(temp);
}
 
// /* To delete an element */
void delete()
{   
    int getroll;
    printf("Enter the roll no to be deleted :\n");
    scanf("%d",&getroll);
    if(getroll<100 || getroll>200)
    {
    	printf("invalid input");
    }
    else if (first == NULL && last == NULL)
    {
    	printf("list is empty");
    }
    else{
    	struct node *temp2 = first;
	    while(!((temp2->rollno == getroll) || (temp2->next == first)))
	        temp2 = temp2->next;
	    if(temp2==first && getroll != first->rollno) 
	    {
	    	printf("no such position detected");
	    }
	    else if(temp2==first && getroll == first->rollno )
	    {
	    	printf("Node deleted from list");
	    	first = first->next;
		   	free(temp2);
		   	pushInQueue(getroll);
		   	count--;
	    }
	    else
	    {
	    	temp2->prev->next = temp2->next;
		   	temp2->next->prev = temp2->prev;
		   	printf("Node deleted from list");
		   	free(temp2);
		   	pushInQueue(getroll);
		   	count--;
	    }    
    }
}
 
void printSome()
{
    struct node *temp7 = first;
 
    if (temp7 == NULL)
    {
        printf("List empty to display \n");
        return;
    }
    else
    {
    	for(int i =0;i<count;i++)
	    {
	        printf(" %d ", temp7->rollno);
	        printf("  %s " , temp7->name);
	        printf("  %s " , temp7->dob);
	        temp7 = (temp7->next);
	        printf("\n");
	    }
    }
}
void printFullList()
{
    struct node *temp2 = first;
 
    if (temp2 == NULL)
    {
        printf("List empty to display \n");
        return;
    }
    else
    {
    	for(int i =0;i<count;i++)
	    {
	        printf(" %d ", temp2->rollno);
	        printf("  %s " , temp2->name);
	        printf("  %s " , temp2->dob);
	        printf("  %s " , temp2->address);
	        printf("  %s ", temp2->phoneno);
	        temp2 = (temp2->next);
	        printf("\n");
	    }
    }
}
void search()
{
	int search;
	printf("\nenter search key\n");
	scanf("%d",&search);
  struct node *temp3;
  temp3=first;
  while((temp3->next!= first)&&(temp3->rollno!=search))
  {
     temp3=temp3->next;
  }
  if(temp3->rollno==search)
  {
    printf("Search Successfull!\n");
    printf("Roll No: %d\nName:%s\nDOB:%s\n",temp3->rollno,temp3->name,temp3->dob);
  }
  else
  {
    printf("Search unsuccessful,no such element exists\n");

  }
}

char nname[50];
char ndob[50];
char naddress[100];
char nphoneno[50];
 
void modify()
{
  
  int key;
	printf("\nenter the key\n");
	scanf("%d",&key);
	int choose;
  
  struct node *temp4;
  temp4=first;
  while((temp4->next!= first)&&(temp4->rollno!=key))
  {
     temp4=temp4->next;
  }
  if(temp4->rollno==key)
  {
    printf("Which field do you want to modify?\n");
    printf("1.Name\n");
    printf("2.Date of Birth\n");
    printf("3.Address\n");
    printf("4.Mobile Number\n");
    printf("5.Exit\n");
    printf("Enter your choice : ");
    scanf("%d",&choose);
    //printf("%d and %s\n",temp->rollNumber,temp->name);
    switch(choose)
    {
        case 1:
        printf("Enter new name : ");
        scanf("%s",nname);
        strcpy(temp4->name,nname);   
        break;
        case 2:
        printf("Enter new DOB : ");
        scanf("%s",ndob);
        strcpy(temp4->dob,ndob);   
        break;
        case 3:
        printf("Enter new address : ");
        scanf("%s",naddress);
        strcpy(temp4->address,naddress);   
        break;
        case 4:
        printf("Enter new number : ");
        scanf("%s",nphoneno);
        strcpy(temp4->phoneno,nphoneno);
        break;
        case 5:
        break;
        default:
        printf("Wrong choice\n");

    }
  }
  else
  {
    printf("Unable to find element with given roll number\n");

  }
}

void sort()
{

  int c=1;
  struct node *temp5;
  temp5 = first;

  while(temp5->next!=first)
  {
    temp5=temp5->next;
    c++;
  }
  printf("%d\n",c);
   char namessort[c][25];
   char temp6[25];
  
  int t;

  for(int t=0;t<c;t++)
  {
    strcpy(*(namessort+t),temp5->name);
    temp5=temp5->next;
  }

  
   for( t=0;t<=c;t++)
      for(int j=t+1;j<=c;j++)
      {
         if(strcmp(*(namessort+t),*(namessort+j))>0){
            strcpy(temp6,*(namessort+t));
            strcpy(*(namessort+t),*(namessort+j));
            strcpy(*(namessort+j),temp6);
         }
      }
   printf("Order of Sorted Names: ");
   for(t=0;t<c;t++)
      {
        printf("\n%s",*(namessort+t));
      }

}


void main()
{
    queue_array = (int*)malloc(MAX*sizeof(int));
    
    char buffer[1024] ;  
    FILE *fp = fopen("StudentData.csv","r"); 
     if(fp == NULL)
    {
        printf("\n file opening failed "); 
        exit(0); 
    }
    fgets(buffer,sizeof(buffer),fp);
    char name[50],dob[50],address[100], phoneno[50];
     

    int ch;
    //first = last = h = temp = temp1 = NULL;
    printf("\n 1 - Insert");
    printf("\n 2 - Delete");
    printf("\n 3 - Search");
    printf("\n 4 - modify");
    printf("\n 5 - Sort");
    printf("\n 6 - print");
    printf("\n 7 - print full list");
    printf("\n 8 - printcount");
    printf("\n 9 - printqueue");
    printf("\n 10 - Exit");

    while (1)
    {
        printf("\n Enter choice : ");
        scanf("%d", &ch);
        switch (ch)
        {
            case 1:
            fgets(buffer,sizeof(buffer),fp);
        	char *token = strtok(buffer,",");	
        	if(token!=NULL)
        	{
        		token = strtok(NULL,",");
        		strcpy(name,token);
        		token = strtok(NULL,",");
        		strcpy(dob,token);
        		token = strtok(NULL,",");
        		strcpy(address,token);
        		token = strtok(NULL,",");
        		strcpy(phoneno,token);
        	} 
            insert(name,dob,address,phoneno);
            break;
            case 2:
                delete();
                break;
            case 3:
                search();
                break;
            case 4:
                modify();
                break;
            case 5:
                sort();
                break;   
            case 6:
            	printSome();
            	break;   
            case 7:
            	printFullList();
            	break;         
            case 8:
                printf("%d",count);
                break;
            case 9:
            	for(int i = front;i<=rear;i++)
                printf("%d\n",queue_array[i]);
                break;
            case 10:
                exit(0);
            default:
                printf("\n Wrong choice menu");
        }
    }
}