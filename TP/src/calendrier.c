#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int bissextile (int annee)
{
  if ((annee %4 == 0 && annee %100 !=0) || (annee % 400 == 0))
    {
      return 1;
    }
  return 0;
}


int jour_par_mois (int mois, int annee)
{
switch (mois) {

case 1 :
return 31;
 break;

case 2 :
  if (bissextile(annee) == 0)
    {
      return 28;
    }
  else
    {
      return 29;
    }
 break;

 case 3 :
return 31;
 break;

 case 4 :
return 30;
 break;

 case 5:
return 31;
 break;

 case 6 :
return 30;
 break;

 case 7 :
return 31;
 break;

 case 8 :
return 31;
 break;

 case 9 :
return 30;
 break;

 case 10 :
return 31;
 break;

 case 11 :
return 30;
 break;

 case 12 :
return 31;
 break;
 
 default :
   printf ("Incorrect");
   break;
}
 
  return 0;
}



int main (int argc, char* argv[])

{
  int mois = atoi(argv[2]);
  char valeur_mois [13] [9] = {"0","janvier", "fevrier", "mars", "avril", "mai", "juin", "juillet", "aout", "septembre", "octobre", "novembre", "decembre"};
  int annee = atoi(argv[1]);
  printf("%d  %s bissextile\n", annee,bissextile(annee) ? "est" : "n'est pas");
  printf("Le mois de %s a %d jours\n", valeur_mois[mois], jour_par_mois(mois,annee));

  
return 0;
}


