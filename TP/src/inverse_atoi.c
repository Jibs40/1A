#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void chaine_miroir(char* str)
{
    char longueur = strlen(str);
    char memoire = 0;
    int i = 0;
    int milieu = longueur/2;


    while (i<milieu)
      {
	memoire = str[i];
	str[i]= str[longueur -i -1];
	str [longueur -i -1] = memoire;
	i=i+1;
      }
}

int main (int argc, char* argv[])


{
  int i=1;
  while (i<argc)
    {
      printf("avant %s\n", argv[i]);
      chaine_miroir(argv[i]);
      printf ("après %s\n", argv[i]);
      i=i+1;
    }
  return 0;
}
