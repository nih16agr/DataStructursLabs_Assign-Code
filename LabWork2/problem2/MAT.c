#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int compare(int **array , int s);

int num;
int numQuad;
int count ;
int level;

struct node
{
	int nodeValue;
	int bitValue;
	struct node *topLeft;
	struct node *topRight;
	struct node *bottomLeft;
	struct node *bottomRight;
};


void printQuadTree(struct node *quad)
{
	if(quad)
	{
		level++;
		printQuadTree(quad->topLeft);
		printQuadTree(quad->topRight);
		printQuadTree(quad->bottomLeft);
		printQuadTree(quad->bottomRight);
		if(!quad->topLeft && !quad->topRight && !quad->bottomLeft && !quad->bottomRight )
			printf("%d %d %d\n",quad->nodeValue , quad->bitValue ,level-1);
		level--;
	}
}


struct node *quadTree(int s, int** array)
{
	if(s < 1)
	{
		return NULL;
	}
	else if(s == 1)
	{
		struct node *leaf = (struct node*)malloc(sizeof(struct node));
		count++;
		leaf->bitValue = array[0][0];
		leaf->nodeValue = numQuad;
		numQuad++;
		return leaf;		
	}
	else
	{
		if(compare(array,s) == 1)
		{
			struct node *leaf = (struct node*)malloc(sizeof(struct node));
			count++;
			leaf->bitValue = array[0][0];
			leaf->nodeValue = numQuad;
			numQuad++;
			return leaf;				
		}
		else
		{
			struct node *parent = (struct node*)malloc(sizeof(struct node));
			int **dummy1 =(int**)malloc(sizeof(int*)*s/2);
			for(int m = 0;m < s;m++)
				dummy1[m]=(int*)malloc(sizeof(int)*s/2);
			
			for(int i = 0; i < s/2; i++)
			{
				for(int j = 0;j<s/2;j++)
				{
					dummy1[i][j] = array[i][j];
				}
			}
			parent->topLeft = quadTree(s/2,dummy1);


			
			for(int i = 0; i < s/2; i++)
			{
				for(int j = s/2;j<s;j++)
				{
					dummy1[i][j-s/2] = array[i][j];
				}
			}
			parent->topRight = quadTree(s/2,dummy1);



			for(int i = s/2; i < s; i++)
			{
				for(int j = 0;j<s/2;j++)
				{
					dummy1[i-s/2][j] = array[i][j];
				}
			}
			parent->bottomLeft = quadTree(s/2,dummy1);
			


			for(int i = s/2; i < s; i++)
			{
				for(int j = s/2;j<s;j++)
				{
					dummy1[i-s/2][j-s/2] = array[i][j];
				}
			}
			parent->bottomRight = quadTree(s/2,dummy1);

			
			return parent;

		}		
	}
}

int compare(int **array , int s)
{
	int c = array[0][0];
	for(int i = 0;i<s;i++)
	{
		for(int j = 0;j<s;j++)
			if(array[i][j] != c )
				return 0;				
	}
	return 1;
}


int **maxArray(int s, int** array)
{
	
		
	if(s < 1)
	{
		return NULL;
	}
	else if(s == 1)
	{
		array[0][0] = num;
		num++;
		return array;
	}
	else
	{
		if(compare(array,s) == 1)
		{
			for(int i = 0;i<s;i++)
			{
				for(int j = 0;j<s;j++)
					array[i][j] = num;
			}
			num++;
			return array;
		}
		else
		{
			int **dummy1 =(int**)malloc(sizeof(int*)*s/2);
			for(int m = 0;m < s;m++)
				dummy1[m]=(int*)malloc(sizeof(int)*s/2);
			
			for(int i = 0; i < s/2; i++)
			{
				for(int j = 0;j<s/2;j++)
				{
					dummy1[i][j] = array[i][j];
				}
			}
			dummy1 = maxArray(s/2,dummy1);
			for(int i = 0; i < s/2; i++)
			{
				for(int j = 0;j<s/2;j++)
				{
					array[i][j] = dummy1[i][j];
				}
			}

/*---------------------------------------------------------*/

			
			for(int i = 0; i < s/2; i++)
			{
				for(int j = s/2;j<s;j++)
				{
					dummy1[i][j-s/2] = array[i][j];
				}
			}
			dummy1 = maxArray(s/2,dummy1);
			for(int i = 0; i < s/2; i++)
			{
				for(int j = s/2;j<s;j++)
				{
					array[i][j] = dummy1[i][j-s/2];
				}
			}

/*---------------------------------------------------------*/

			for(int i = s/2; i < s; i++)
			{
				for(int j = 0;j<s/2;j++)
				{
					dummy1[i-s/2][j] = array[i][j];
				}
			}
			dummy1 = maxArray(s/2,dummy1);
			for(int i = s/2; i < s; i++)
			{
				for(int j = 0;j<s/2;j++)
				{
					array[i][j] = dummy1[i-s/2][j];
				}
			}

/*---------------------------------------------------------*/

			for(int i = s/2; i < s; i++)
			{
				for(int j = s/2;j<s;j++)
				{
					dummy1[i-s/2][j-s/2] = array[i][j];
				}
			}
			dummy1 = maxArray(s/2,dummy1);
			for(int i = s/2; i < s; i++)
			{
				for(int j = s/2;j<s;j++)
				{
					array[i][j] = dummy1[i-s/2][j-s/2] ;
				}
			}

			return array;

		}		
	}
}


void printQuadTree(struct node *quad);
struct node *quadTree(int s, int** array);
int **maxArray( int s, int** array);

void main()
{
	FILE *fp = fopen("./imagearray.txt","r");
	if(fp == NULL)
	{
		printf("\n file opening failed ");      
	    exit(0) ;   
	}

	int **image = (int**)malloc(sizeof(int*));   
	char line[1024];
	int i = 0;
	int j;
	while(fgets(line,1024,fp) != NULL)
	{
	 	image[i]=(int*)malloc(sizeof(int));
	    char* token = strtok (line, " ");
	    j = 0;      
	    while (token != NULL)
	    {
	    	int value = atoi(token);
	        image[i][j]= value;
	        token = strtok (NULL, " "); 
	        j++;
	    }
	    i++;
	}

	printf("The size of the array is %dx%d .\n\n",i,j);
	
	int size;
	if(i>=j)
		size = (int)pow(2, ceil(log(i)/log(2)));
	else
		size = (int)pow(2, ceil(log(j)/log(2)));

    
	printf("The new size of the array is %d.\n\n",size);
		
    int increRow = size-i ;
    int increCol = size-j ;

    printf("The image array with extra needed columns and rows is \n\n");

	int **usefulArray =(int**)malloc(sizeof(int*)*size);
	for(int m = 0;m < size;m++)
	{
		usefulArray[m]=(int*)malloc(sizeof(int)*size);
		for(int n = 0 ; n < size ; n++)
		{
			if(m < increRow || n < increCol)
				usefulArray[m][n] = 0;
			else
				usefulArray[m][n] = image[m-increRow][n-increCol];
			printf("%d ",usefulArray[m][n]);
		}
		printf("\n");
	}
		printf("\n\n");


	int **usefulArrayCopy =(int**)malloc(sizeof(int*)*size);
	for(int m = 0;m < size;m++)
	{
		usefulArrayCopy[m]=(int*)malloc(sizeof(int)*size);
		for(int n = 0 ; n < size ; n++)
			usefulArrayCopy[m][n] = usefulArray[m][n];
	}


	num = 1;
	numQuad = 1;
	count = 0;
	level = 0;

	int **maximalSquareArray =(int**)malloc(sizeof(int*)*size);
	for(int m = 0;m < size;m++)
		maximalSquareArray[m]=(int*)malloc(sizeof(int)*size);


	maximalSquareArray = maxArray(size,usefulArray);
	printf("The maximal square array is \n\n");

	for(int m = 0;m < size;m++)
	{
		for(int n = 0 ; n < size ; n++)
			{
				if(maximalSquareArray[m][n]/10 == 0)
					printf(" ");
				printf("%d ",maximalSquareArray[m][n]);
			}
		printf("\n");
	}
	printf("\n\n");

	
	struct node *finalQuadTree = (struct node*)malloc(sizeof(struct node));

	finalQuadTree = quadTree(size,usefulArrayCopy);
	printf("The information in leaf nodes of quad tree formed(in post order) are \n\n");

	printQuadTree(finalQuadTree);
	printf("\n\n");
	printf("The count of the quad tree is %d\n",count);	
	
}
