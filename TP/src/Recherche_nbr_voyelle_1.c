#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int voyelle(char *argv)
{
  int i=0;
  int compteur= 0;
  char voyelle [] ="AaEeIiOoUuYy";

  printf("argv = %s (taille = %ld)\n", argv, strlen(argv));
  printf("argv = %s (taille = %ld)\n", voyelle, strlen(voyelle));

	 while (argv[i] !=0)
	   {
	     int j = 0;
	     while(voyelle[j] !=0)
	       {
		 if (argv[i] == voyelle[j])
		   {
		     compteur=compteur+1;
		     printf("%d\n",compteur);
		       }
		 j=j+1;
	       }
	     i=i+1;
	   }
	 return compteur;
	 }
    int main (int argc, char *argv[])
    {
      int compteur = 0;
      int i=1;
      while (i<argc)
	{
	  compteur = compteur+voyelle(argv[i]);
	  i=i+1;
	}
      printf("le nombre de voyelle total =%d \n", compteur);
      return 0;
    }
  
