#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int miroir(int longueur, char* str)
{
  int i = 0;
  char reverse =0;
  int milieu = longueur/2;

  while (i<milieu)
      {
	reverse = str[i];
	str[i]= str[longueur -i -1];
	str [longueur -i -1] = reverse;
	i=i+1;
      }
  return 0;

   }


void itoa(int longueur, int number, char* str_new) // Problème, marche pas avec un 0 => Mettre un do while pour faire un tour de boucle avant
{                                                 // En exo, traiter les nbres négatifs
  int i = 0;

  while (number>0)
    {
      str_new[i] = (number % 10) + '0';
      number = number / 10;
      i = i + 1;
    } 
  str_new[i]=0; 
}


int main(int argc, char* argv[])
{
  int i =1, longueur = 0;
  while (i<argc)
    {
      longueur = strlen(argv[i]);
      itoa(longueur, atoi(argv[i]), argv[i]);
      miroir(longueur, argv[i]);
      printf("\n%s\n", argv[i]);
      i=i+1;
    }
  return 0;
}
