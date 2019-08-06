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
	FILE *fp = fopen("./outputfile.txt","r"); 
  if(fp == NULL)
  {
    printf("file opening failed\n ");
    exit(0) ;
  }
  
  char *encrypted = (char *)malloc(sizeof(char));
  char line[1024];
  while(fgets(line,1024,fp) != NULL)
    strcat(encrypted, (char *)line);
  

  /*provide the encryption parameters*/
  int n,a,b;
  printf("Please provide SAME n (a natural number) and a & b (integers) to carryout the decryption\n");
  scanf("%d %d %d",&n,&a,&b);
  printf("\n");
  // if(gcd(n,a)!=1)
  // {
  //   printf("Badly formatted arguments\n");
  //   exit(0);
  // } 
  // else if(a == 0)
  // {
  //   printf("Badly formatted arguments\n");
  //   exit(0);
  // }
  // else 
  if(n<1)
  {
    printf("Badly formatted arguments\n");
    exit(0);
  }


 
  /*decryption parameters*/
  int ad,bd;
  int q = 0;
  while((1+q*n)%a != 0)
    q++;
  ad = (1+q*n)/a;
  bd = -1*((ad*b)%n);



  /* decryption process*/
  int size = strlen(encrypted); 
  char *decrypted = (char *)malloc(size*sizeof(char));
  int i;
  for(int m = 0; m < (double)size/(double)n ; m++)
  {
    for(int j = 0 ; j < n ; j++)
    {
      if(ad*j+bd >= 0) i = (ad*j + bd)%n ;
      else i =  n-( (-1*(ad*j+bd)) %n);
      decrypted[m*n + j] = encrypted[m*n+i];
    }  
  }



  /* writing decrypted output*/
  
  FILE *f1 = fopen("./decryptedOutputfile.txt","w");
  if(f1 == NULL)
  {
    printf("file opening failed\n ");
    exit(0) ;
  }
  fprintf(f1,"%s",decrypted);
  printf("contents to file written successfully !\n"); 

}

