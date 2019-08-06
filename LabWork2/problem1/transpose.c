#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int gcd(int a, int b) 
{ 
    if (b == 0) 
        return a; 
    return gcd(b, a % b);  
} 

void main()
{
  /* reading input file*/
  FILE *fp = fopen("./2019_CSN261_L2_Q1_SampleTestcaseFile/Sample_testcase_2.txt","r");
  //FILE *fp = fopen("./2019_CSN261_L2_Q1_SampleTestcaseFile/Sample_testcase_1.txt","r");
  //FILE *fp = fopen("./inputfile.txt","r"); 
  if(fp == NULL)
  {
    printf("file opening failed\n ");
    exit(0) ;
  }

  char *inputtext = (char *)malloc(sizeof(char));
  char line[1024];
  while(fgets(line,1024,fp) != NULL)
    strcat(inputtext,(char *)line);

   /*provide the encryption parameters*/
  int n,a,b;
  printf("Please provide n (a natural number) and a & b (integers) to carryout the encryption\n");
  scanf("%d %d %d",&n,&a,&b);
  printf("\n");
  // if(gcd(n,a)!=1)
  // {
  // 	printf("Badly formatted arguments\n");
  // 	exit(0);
  // } 
  // else if(a == 0)
  // {
  // 	printf("Badly formatted arguments\n");
  // 	exit(0);
  // }
  // else 
  if(n<1)
  {
  	printf("Badly formatted arguments\n");
  	exit(0);
  }


  /* adding extra \0 in inputtext*/
  int size = strlen(inputtext);
  int d = size%n ;
  if(d != 0)
  {
    for(int i = 0; i < (n-d) ; i++)
    strcat(inputtext," ");
  } 
  size = strlen(inputtext);

  /* encryption process*/
  char *encrypted = (char *)malloc(size*sizeof(char));
  int j;
  for(int m = 0; m < (double)size/(double)n ; m++)
  {
    for(int i = 0 ; i < n ; i++)
    {
      if(a*i+b >= 0) j = (a*i + b)%n ;
      else j =  n-((-1*(a*i+b))%n);
      encrypted[m*n + i] = inputtext[m*n+j];
    }
  }  /////yaar 4 ya 8 hone me n ,extra char aa ja rhe h and automaticall line kyo change ho rhi h

  
  /* writing ecrypted output*/
  FILE *f1 = fopen("./outputfile.txt","w");
  if(f1 == NULL)
  {
    printf("file opening failed\n ");
    exit(0);
  }

  // for(int i = 0; i < (size+(n-d)); i++)
  // {
  // 	if(encrypted[i])
  // 		fprintf(f1,"%c",encrypted[i]);
  // 	else
  // 		fprintf(f1,"\\0");
  // }
  fprintf(f1,"%s",encrypted);
  printf("contents to file written successfully !\n"); 
  // fclose(f1);

}


// in reference to line 18 -  not needed
// int s = strlen(line); //int s = sizeof(line); returns 1024 , not to be used
// inputtext = (char *)realloc(inputtext, sizeof(inputtext) + s*sizeof(char));

//in reference to line 24 - alternatie and one anomaly
// scanf("%d\n",&n);
// scanf("%d\n",&a);
// scanf("%d",&b); // here \n after %d is bringing descrapancy(it is asking for one more input to proceed )

// in reference to line 35 -  not needed
//inputtext = (char *)realloc(inputtext, sizeof(inputtext) + sizeof(char));