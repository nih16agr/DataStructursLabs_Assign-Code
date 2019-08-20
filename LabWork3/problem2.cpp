#include <iostream>
using namespace std;

int count = 0;
struct nodeXOR
{
	int xorvalue;
	int firstIndex,lastIndex;
	struct nodeXOR *next;
}*head,*point;

// void printXOR()
// {
// 	nodeXOR *node = head;
// 	if(!node)
// 	{
// 		cout<<"The list is empty!"<<endl;
// 		return;
// 	} 
// 	while(node)
// 	{
// 		cout<<node->xorvalue<<endl;
// 		node = node->next;
// 	}
// 	delete node;
// }
int getxor(int a, int b)
{
	nodeXOR *traverse = new nodeXOR;
	traverse = head;
	while(!(traverse->firstIndex == a && traverse->lastIndex == b))
		traverse = traverse->next;
	// if(traverse->xorvalue)
	return traverse->xorvalue;
	//else return 0;
}
void xorit(int startIndex,int endIndex,int value)
{
	nodeXOR *temp = new nodeXOR;
	if(!head)
	{
		head = temp;
		point = temp;
		temp->xorvalue = value;
	}
	else if(startIndex == endIndex)
	{
		point->next = temp;
		point = temp;
		temp->xorvalue = value;
	}
	else 
	{
		point->next = temp;
		point = temp;
		temp->xorvalue = getxor(startIndex,endIndex-1)^value;
	}
	temp->firstIndex = startIndex;
	temp->lastIndex = endIndex;
	//cout<<"the inserted node is "<<temp->firstIndex<<" "<<temp->lastIndex<<" "<<temp->xorvalue<<endl;
	temp = NULL;
	delete temp;	
}
void formXOR(int *array,int size)
{
	for(int i= 0;i<size;i++)
	{
		for(int j = i;j<size;j++)
			xorit(i,j,array[j]);
	}
}
void getTriplets()
{
	nodeXOR *pt = new nodeXOR;
	pt = head;
	while(pt)
	{
		if(pt->xorvalue == 0)
		{
			int i = pt->firstIndex;
			int k = pt->lastIndex;
			for(int j = i+1;j<=k;j++)
			{
				cout<<"("<<i+1<<" , "<<j+1<<" , "<<k+1<<")"<<endl;
				count++;
			}
		}
		pt = pt->next;
	}
}
int main()
{
	while(1)
	{
		cout<<"\n1- Run the program"<<endl;
		cout<<"2- Exit"<<endl;
		cout<<"Enter choice"<<endl;
		int ch;
		cin>>ch;
		switch(ch)
		{
			case 1:
			break;
			case 2:
			exit(0);
			default:
			cout<<"\n Wrong choice menu";
		}
		cout<<"Enter the number of integers : "<<endl;
	    int n;
	    cin>>n;
	    cout<<"Enter "<<n<<" positive integers : "<<endl;
	    int *num = new int[n];
	    for(int j = 0;j<n;j++)
	      	cin>>num[j];
	    cout<<endl;
	    formXOR(num,n);
	    getTriplets();
	    cout<<"\nThe COUNT of triplets is "<<count<<endl;
		count = 0;
		//printXOR();
		head = NULL;
		point = NULL;
	}
	return 0;
}