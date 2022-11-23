#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int palindrome (const char *str)
{
  int i=0;
  int len = strlen(str);
  while (i<len/2){
    if ((str[i] != str[len -i -1])
	return 0;
	i=i+1;
	}
    return 1;
  
  }
  
  int main (argc char*argv)

  {
    int i =1
      const char *estpas[]={"n'est pas", "est"};
      while (i<argc){
		 
		     printf ("%d:%s (%zu)\n", i, argv[i], strlen (argv[i]));
		      printf"%s %s un palindrome?.\n", argv [i], palindrome (argv[i]);

		     }
    i=i+1;
  }
    return 0;
}
    
