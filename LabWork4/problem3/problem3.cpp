#include <iostream> 
#include <map> 
  
using namespace std; 

int main()
{
	while(1)
	{
		label1:
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
			cout<<"\nWrong choice menu";
			goto label1;
		}
		cout<<"Enter N"<<endl;
		int arr_len;
		cin>>arr_len;

		int in_arr[arr_len];
		for (int i = 0; i < arr_len; ++i)
			cin>>in_arr[i];

		cout<<"Enter n"<<endl;
		int n;
		cin>>n;

		int sum = 0, max_len = 0;
		map<int,int> hashmap;
		//hashmap[0] = -1
		int end_index = -1;

		for (int i = 0; i < arr_len; ++i)
		{
			
			sum += in_arr[i];  

			if(sum == n)
				max_len = i+1;

			if(hashmap.find(sum) == hashmap.end())
				hashmap[sum] = i;

			if(hashmap.find(sum - n) != hashmap.end())
			{ 
				if (max_len < (i - hashmap[sum - n])) 
				{
	                max_len = i - hashmap[sum - n]; 
					end_index = i+1;
					//cout<<end_index<<endl;
				}
	        } 
		}
		if(end_index == -1 && max_len == 0)
		{
			cout<<"SORRY sum doesnt exist"<<endl;
		}
		else
		{
			end_index = arr_len;
			cout<<"the max length of sub-array forming given sum is "<<max_len<<endl;
			cout<<"from "<<end_index-max_len+1<<" to "<<end_index<<endl;	
		}
	}
}