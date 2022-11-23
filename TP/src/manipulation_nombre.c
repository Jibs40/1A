#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void table (void)
{
  
   printf ("Caractère\t Décimal\t Hexa.\t Octal\t\n"); 
  int i =32;
  while (i<127)
    {
      printf ("%c\t %d\t 0x%x\t %o\t\n",i,i,i,i);
      i=i+1;
    }
 }
      
int main(int argc, char* argv[])
{

  table();
  return 0;
}
