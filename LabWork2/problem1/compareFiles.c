#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void main()
{
  /* reading input file*/
  FILE *fp = fopen("./2019_CSN261_L2_Q1_SampleTestcaseFile/Sample_testcase_2.txt","r");
  //FILE *fp = fopen("./2019_CSN261_L2_Q1_SampleTestcaseFile/Sample_testcase_1.txt","r");
  //FILE *fp = fopen("./inputfile.txt","r"); 
  FILE *f2 = fopen("./decryptedOutputfile.txt","r"); 
  if(fp == NULL ||f2 == NULL)
  {
    printf("file opening failed\n ");
    exit(0) ;
  }

  char *inputtext = (char *)malloc(sizeof(char));
  char line[1024];
  while(fgets(line,1024,fp) != NULL)
    strcat(inputtext,(char *)line);
  int size = strlen(inputtext);

  char *decrypted = (char *)malloc(sizeof(char));
  char line2[1024];
  while(fgets(line2,1024,f2) != NULL)
    strcat(decrypted,(char *)line2);
  int size2 = strlen(inputtext);


  int i = 0;
  while(i<size)
  {
    if(inputtext[i] != decrypted[i])
    {
      printf("The value is not same, algo not working properly\n");
      exit(0);
    }
    i++;
  }
  printf("Algo working properly\n");

  // fclose(fp); double free or corruption (out) Aborted (core dumped)
  // fclose(f2);
}