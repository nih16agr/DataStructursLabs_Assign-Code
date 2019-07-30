#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void removeRed(int **red,int **blue,int **green);
void removeBlue(int **red,int **blue,int **green);
void removeGreen(int **red,int **blue,int **green);
void preserveRed(int **red,int **blue,int **green);
void preserveBlue(int **red,int **blue,int **green);
void preserveGreen(int **red,int **blue,int **green);
void pixelvalue(int **red,int **blue,int **green);

void removeRed(int **red,int **blue,int **green)
{
  for(int i=0;i<953;i++)
    {
      for(int j=0;j<1268;j++)
        {
            if(red[i][j]>blue[i][j] && red[i][j]>green[i][j])
                red[i][j]=0;
        }
    }  
}
void removeBlue(int **red,int **blue,int **green)
{
  for(int i=0;i<953;i++)
    {
      for(int j=0;j<1268;j++)
        {
          if(red[i][j]<blue[i][j] && blue[i][j]>green[i][j])
            blue[i][j]=0;
        }
    }
}
void removeGreen(int **red,int **blue,int **green)
{
  for(int i=0;i<953;i++)
    {
      for(int j=0;j<1268;j++)
        {
            if(green[i][j]>blue[i][j] && red[i][j]<green[i][j])
                green[i][j]=0;
        }
    }
}

void preserveRed(int **red,int **blue,int **green)
{
  removeBlue(red,blue,green);
  removeGreen(red,blue,green);
}
void preserveBlue(int **red,int **blue,int **green)
{
  removeGreen(red,blue,green);
  removeRed(red,blue,green);
}
void preserveGreen(int **red,int **blue,int **green)
{
  removeRed(red,blue,green); 
  removeBlue(red,blue,green);
}
void pixelvalue(int **red,int **blue,int **green)
{
  int x,y;
  scanf("%d",&x);
  scanf("%d",&y);
  if(x<0 || y<0 || x>953 || y>1268)
    printf("wrong input\n");
  else
  {
    printf("\nthe rgb values are :\n");
    printf(" %d ",red[x][y]);
    printf(" %d ",green[x][y]);
    printf(" %d\n",blue[x][y]);
  }
}

void main()
{   
  int **red=(int**)malloc(sizeof(int*)*953);
  for(int i=0;i<953;i++)
    red[i]=(int*)malloc(sizeof(int)*1268);
  
  int **green=(int**)malloc(sizeof(int*)*953);
  for(int i=0;i<953;i++)
    green[i]=(int*)malloc(sizeof(int)*1268);
  
  int **blue=(int**)malloc(sizeof(int*)*953);
  for(int i=0;i<953;i++)
    blue[i]=(int*)malloc(sizeof(int)*1268);
  
  FILE *fp = fopen("./Q3_Input/Q3_ip_Blue.dat","r");   
  FILE *fp1 = fopen("./Q3_Input/Q3_ip_Red.dat","r");
  FILE *fp2 = fopen("./Q3_Input/Q3_ip_Green.dat","r");

  if(fp == NULL || fp1 == NULL || fp2 == NULL)
  { 
    printf("\n file opening failed ");      
    exit(0) ;   
  }   
  
  char line[5072];

  for(int i = 0 ; i<953 ;i++)
  {
    fgets(line, 5072, fp);  
    char* token = strtok (line, ",");
    int k = 0;      
    while (token != NULL)
    {
      int l = atoi(token);
      blue[i][k]=l;
      token = strtok (NULL, ","); 
      k++;
    }
  }


  for(int i = 0 ;i<953 ;i++)
  {
    fgets(line, 5072, fp1);  
    char* token = strtok (line, ",");
    int k = 0;      
    while (token != NULL)
    {
      int l = atoi(token); 
      red[i][k]=l;
      token = strtok (NULL, ","); 
      k++;
    }
  }


  for(int i = 0 ;i<953 ;i++)
  {
    fgets(line, 5072, fp2);  
    char* token = strtok (line, ",");
    int k = 0;      
    while (token != NULL)
    {
      int l = atoi(token); 
      green[i][k]=l;
      token = strtok (NULL, ","); 
      k++;
    }
  }

  fclose (fp);
  fclose (fp1);
  fclose (fp2);

  int ch;
    //first = last = h = temp = temp1 = NULL;
    printf("\n 1 - Remove Red");
    printf("\n 2 - Remove Green");
    printf("\n 3 - Remove Blue");
    printf("\n 4 - Preserve Red");
    printf("\n 5 - Preserve Green");
    printf("\n 6 - Preserve Blue");
    printf("\n 7 - None");


    printf("\n Enter choice : ");
    scanf("%d", &ch);
        switch (ch)
        {
            case 1:
                removeRed(red,blue,green);
                break;
            case 2:
                removeGreen(red,blue,green);
                break;
            case 3:
                removeBlue(red,blue,green);
                break;
            case 4:
                preserveRed(red,blue,green);
                break;
            case 5:
                preserveGreen(red,blue,green);
                break;   
            case 6:
                preserveBlue(red,blue,green);
                break; 
            case 7:
                break;    
            default:
                printf("\n Wrong choice menu");
          }


  printf("\nGet Pixel Value at given x and y coordinates provided the image pixels are 953 x 1268\n");
  pixelvalue(red,blue,green);
  // FILE *f1 = fopen("outputred.dat", "wb");
  // fwrite(red, sizeof(char), sizeof(red), f1);
  // fclose(f1);
  // FILE *f2 = fopen("outputblue.dat", "wb");
  // fwrite(blue, sizeof(char), sizeof(blue), f2);
  // fclose(f2);
  // FILE *f3 = fopen("outputgreen.dat", "wb");
  // fwrite(green, sizeof(char), sizeof(green), f3 );
  // fclose(f3);

   FILE *f1;
   char output1[]="./q3myoutput/outputred.txt";
   f1 = fopen(output1,"w");
   for(int n=0;n<953;n++)
    {
       for(int j =0;j<1268;j++)
       {
        fprintf(f1,"%d",red[n][j]);
        fprintf(f1,",");
       }
       fprintf(f1,"\n");
    }
   fclose(f1);
   FILE *f2;
   char output2[]="./q3myoutput/outputgreen.txt";
   f2 = fopen(output2,"w");
   for(int n=0;n<953;n++)
    {
       for(int j =0;j<1268;j++)
       {
        fprintf(f2,"%d",green[n][j]);
        fprintf(f2,",");
       }
       fprintf(f2,"\n");
    }
   fclose(f2);
  FILE *f3;
     char output3[]="./q3myoutput/outputblue.txt";
     f3 = fopen(output3,"w");
     for(int n=0;n<953;n++)
      {
         for(int j =0;j<1268;j++)
         {
          fprintf(f3,"%d",blue[n][j]);
          fprintf(f3,",");
         }
         fprintf(f3,"\n");
      }
     fclose(f3);

}