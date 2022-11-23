#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Définis tailles Max noms pour tableaux names
#define NB_PLAYERS 2
#define MAX_LENGHT_NAME 10
#define LONGEST_SHIP    5

// Déclaration des types structs

struct position {int x;int y;}; 
struct dimension {int width;int height;};
enum orientation { HORIZONTAL, VERTICAL };
enum ship_kind {DESTROYER, SUBMARINE, CRUISER, BATTLESHIP, CARRIER, LAST_SHIP};
static const char* const ship_labels[] = {"Destroyer", "Submarine", "Cruiser", "Battleship", "Carrier"};
struct rules {const int ships_count[LAST_SHIP];const int ships_size[LAST_SHIP];};
struct ship { enum ship_kind kind; struct position position; enum orientation orientation;int state[LONGEST_SHIP];};
enum couleur {ROUGE,VERT,JAUNE, BLEUE};
static struct rules basic_rules = { { 2, 2, 1, 1, 1 }, { 2, 1, 3, 4, 5 },};

// Fonction pour écriture du texte en couleur

void print_Color(int color, const char *msg)
{
 
  if(color == 0)
    {
      printf("\033[91;01m%s\033[00m", msg); //ROUGE
    }
  else if(color == 1)
    {
      printf("\033[92;01m%s\033[00m", msg); // VERT
    } 
  else if(color == 2)
    {
      printf("\033[93;01m%s\033[00m", msg); // JAUNE
    }
  else if(color == 3)
    {
      printf("\033[94;01m%s\033[00m", msg); // BLEUE
    }
 
}

// Fonction générant un "générique" de fin

void print_END()
{
  print_Color(ROUGE, "\t--------------------------------------------------------------------------------------------------\n");   
  print_Color(JAUNE, "\t\t\tA bientôt pour de nouvelles aventures!\n\n\n\n");
  print_Color(JAUNE, "\t\t\t\tRéalisateurs:\n\n\t\t\t\tJean-Baptiste DIRIS\n\t\t\t\tJustine GAIRAUD\n\t\t\t\tMathieu SANCHEZ\n\n\n\t\t\tEn parteneriat avec Bordeaux INP\n");
  print_Color(JAUNE,"\t\t\t\t ___   __    _  _______ \n");
  print_Color(JAUNE,"\t\t\t\t|   | |  |  | ||       |\n");
  print_Color(JAUNE,"\t\t\t\t|   | |   |_| ||    _  |\n");
  print_Color(JAUNE,"\t\t\t\t|   | |       ||   |_| |\n");
  print_Color(JAUNE,"\t\t\t\t|   | |  _    ||    ___|\n");
  print_Color(JAUNE,"\t\t\t\t|   | | | |   ||   |    \n");
  print_Color(JAUNE,"\t\t\t\t|___| |_|  |__||___|    \n");
  print_Color(ROUGE, "\t--------------------------------------------------------------------------------------------------\n");    
}

// Permet de cibler la bonne case de la grille à mettre à jour

int index_grid (int largeur, struct position coord)
{ 
  return coord.y*largeur+coord.x;
}

// Affiche la grille

void print_grid (int largeur, int hauteur, int state_grid[])
{
  int b = 0;
  int m = 0;
  struct position coord;

  printf("\n  +");
  for (int j = 0; j<hauteur; ++j)
    {

      for (int i = 0; i<largeur; ++i)
	{
	  printf("---+");    
	}
      int result = 'A'+ m;
      printf("\n%c", result);
      m = m +1;
    
      for (int k= 0; k<largeur; k++)
	{
	  coord.x = k;
	  coord.y = j;
	  
	  if(state_grid[index_grid(largeur,coord)] == -2) // Init
	    {
	      printf(" | .");
	    }
	  else if (state_grid[index_grid(largeur,coord)]==-1) // Eau
	    {
	      printf(" | "); print_Color(BLEUE, "o");
	    }
	  else if (state_grid[index_grid(largeur,coord)]>=0) // touche
	    {
	      printf(" | "); print_Color(ROUGE, "x");
	    }
	  
	}
      printf(" |");
      printf("\n  +");

    }
  for (int n = 0; n<largeur; ++n)
    {
      printf("---+");    
    }
  printf("\n    ");
 
  for (int o = 0; o < largeur; o++)
    {
      printf("%d",b);
      b=b+1;
      printf("   ");
    }
  printf("\n");
  m=0;b=0;
}

// Fonctions systèmes
int sum(int n, const int array[])
    
{
  {     
    int i = 0;
    int sum = 0;
    
    for (i=0; i<n; i++)
      {
	sum = sum + array[i];
      }
    return sum;
  }
}
 
int inside(struct position pos,
	   struct position origin, struct dimension dim)
{
  if (pos.x >= origin.x && pos.x < origin.x + dim.width) 
    if (pos.y >= origin.y && pos.y < origin.y + dim.height) 
      return 1; 
       
  return 0; 
}
 

void constrain(struct position *pos, struct dimension dim)
{
  if(pos->x > dim.width-1)
    { 
      pos->x = dim.width-1;
    }
     
  if (pos ->y > dim.height-1)
    {
      pos->y = dim.height-1;
    }
          
}


int offset(struct position pos, struct position origin)
{   
  int offset = (pos.x-origin.x)+(pos.y-origin.y);
  return offset;
}

int ship_size(struct rules rules, struct ship ship)
{
  int ship_size = rules.ships_size[ship.kind];
  return  ship_size;
}


struct dimension ship_dimension(struct rules rules, struct ship ship)
{
        
  struct dimension dim;
  if (ship.orientation == VERTICAL)
    {
      dim.height = ship_size(rules,ship);
      dim.width = 1;
    }
  else
    {
      dim.height = 1;
      dim.width = ship_size(rules,ship);
    }
        
  return dim;
}


int remaining_life(struct rules rules, struct ship ship)
{
  int remaining_life = rules.ships_size[ship.kind] - sum(rules.ships_size[ship.kind], ship.state);
  return remaining_life;
}


void print_position(struct position pos)
{
  char ordonnee [27] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
  printf("%c%d", ordonnee[pos.y], pos.x);
}


void print_ship(struct rules rules, struct ship ship)
{
  char ordonnee [27] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
  printf("%s (%d/%d) %c%d-", ship_labels[ship.kind], remaining_life(rules, ship), ship_size(rules, ship), ordonnee[ship.position.y], ship.position.x);
  if (ship.orientation == HORIZONTAL )
    {
      ship.position.x = ship.position.x + ship_size(rules, ship)-1;
    }
  else
    {
      ship.position.y = ship.position.y + ship_size(rules, ship)-1;
    }
  printf("%c%d\n",  ordonnee[ship.position.y], ship.position.x); 
}


struct position parse_position(const char *str)
{
  struct position parse_position;
  int len = strlen(str);
  int x = -1;                             // Valeur pour tester si x vide
  int y = -1;                             // Valeur pour tester si y vide

  for (int i = len - 1; i >= 0; i--) 
    {

      if (str[i] >= '0' && str[i] <= '9') { // CHIFFRE
        if (x == -1) {
	  x = str[i] - '0';               // Si mem vide je stocke, 
        }                               // Sinon je fais rien
        
      } 


      else if (str[i] >= 'A' && str[i] <= 'Z') { // MAJUSCULE
        if (y == -1)                    
	  {
	    y = str[i] - 'A';                   // Si mem vide je stocke, 
	  }                                   // Sinon je fais rien


      } 
      else if (str[i] >= 'a' && str[i] <= 'z') {   // MINUSCULE 

        if (y == -1) 
	  {
	    y = str[i] - 'a';                   // Si mem vide je stocke,
	  }                                   // Sinon je fais rien
      }
    }                                           // Fermeture du For

  parse_position.x=x;
  parse_position.y=y;

  return parse_position;
    
}

struct ship *find_target(struct rules rules, struct position pos, int fleet_size, struct ship fleet[])
{   
         
  for (int i=0;i<fleet_size; i++) 
    {   
      if ( inside(pos, fleet[i].position, ship_dimension(rules,fleet[i])))
	return &fleet[i];                         
    }
        
  return NULL;
}


int hit(struct rules rules, struct position pos, int fleet_size, struct ship fleet[])
{
  struct ship *target = find_target(rules,pos, fleet_size, fleet);
  struct position pos_temp;

  if (target == NULL)
    {
      return -1;
    } 
  else 
    {
      pos_temp = target->position;

      for (int i=0; target->state[i] != '\0' ;i++)
	{
	  if (target->orientation == HORIZONTAL)
	    {
	      if (pos_temp.x == pos.x)
		{
		  if (target->state[i] == 0)
		    {
		      return 0;
		    }
		  else
		    {
		      return 1;
		    }
		}   
	      pos_temp.x +=1;
	    }
	  else 
	    { 
                                        
	      if (pos_temp.y == pos.y)
		{
		  if (target->state[i] == 0)
		    {
		      return 0;
		    }
		  else 
		    {
		      return 1;
		    }
		}
	      pos_temp.y +=1;  
	    }
	}
    } 
  return 0;
}


int fire(struct rules rules, struct position pos,
	 int fleet_size, struct ship fleet[])
{
  struct ship *target = find_target(rules, pos, fleet_size, fleet);
  int touche= hit(rules, pos, fleet_size,fleet);
  int coule;
  static const char* const ship_labels[] = {"Destroyer", "Submarine", "Cruiser", "Battleship", "Carrier"};


  if (touche == -1)
    {
      print_Color(BLEUE, "\t\tPlouf");
      return -1;
    }     
  if (touche == 0)
    {
      print_Color(ROUGE,"\t\tEn plein dans le mille!\n");
      target->state[offset(pos, target->position)] = 1;
    }
    
  if (remaining_life(rules, *target) == 0)
    {
      coule = (target->kind);
      printf("\t\tBravo, tu as coulé son %s\n\n",ship_labels[coule]);
      return (target->kind)+1;      
    }
  else 
    {
      return 0;
    }

  return 0;

}

int ships_remaining(struct rules rules, int fleet_size,
		    const struct ship fleet[], int remains[])
{

  for (int i = 0; i < LAST_SHIP; i++)
    remains[i] = rules.ships_count[i];
        
  for (int y = 0; y < fleet_size; y++)
    remains[fleet[y].kind]--;                
    
  int trop_bateaux = 0;
  int pas_assez_bateaux = 0;

  for (int j = 0; j < LAST_SHIP; j++)
    {
      if (remains[j] < 0){
	trop_bateaux=1;
      }
      else if (remains[j] > 0){
	pas_assez_bateaux = 1;
      }    
            
    }
        
  if (trop_bateaux == 1) 
    return -1;
  else if (pas_assez_bateaux == 1) 
    return 1;
  else 
    return 0;
}


int ship_overlap(struct rules rules, struct ship ship,
		 int fleet_size,  struct ship fleet[])
{
   
  for (int i = 0; i < rules.ships_size[ship.kind]; i++)
    {
      struct ship * found = find_target(rules, ship.position,   fleet_size, fleet);
      if (found)
	{
	  return found - &fleet[0];
	}
            
      if(ship.orientation == HORIZONTAL)
	ship.position.x = ship.position.x + 1;
      else
	ship.position.y = ship.position.y + 1;
    }
      
  return -1;
}

// Fonction pour initialiser le placement des bateaux en mode 2 joueurs

int init_ships (struct ship fleet_1[], struct ship fleet_2[], char name1[], char name2[], char saisie_bateaux[], int fleet_size_1, int fleet_size_2)
{

  for (int i =0;i<fleet_size_2;i++)
    {
      for(int j=0; j<LONGEST_SHIP;j++)
	{
	  fleet_1[i].state[j]=0;
	  fleet_2[i].state[j]=0;
	}
    }
  
  
  printf("\n%s, tu vas maintenant devoir placer tes 6 Bateaux\n", name1);

  //Placement des bateaux de Joueur 1
  for (int i=0;i<fleet_size_1-1;i++)
    {
      printf("\n\nDonne une coordonnee pour placer ton %s 1 chiffre pour les abcisses, 1 lettre pour les ordonnées\n", ship_labels[fleet_1[i].kind]);
      printf("\nPour info un %s fait %d cases de long/large\n",ship_labels[fleet_1[i].kind],ship_size(basic_rules, fleet_1[i]));
      fgets(saisie_bateaux,10,stdin);
      fleet_1[i].position =parse_position(saisie_bateaux);     
      printf("Dans quel sens veux tu le placer? 0 Horizontal, 1 Vertical\n");
      fgets(saisie_bateaux,10,stdin);
      if (strcmp(saisie_bateaux, "0") == 10)	    
	{
	  fleet_1[i].orientation = HORIZONTAL;
	}
      else if (strcmp(saisie_bateaux, "1") == 10)
	{
	  fleet_1[i].orientation = VERTICAL;
	}
        
      else if (strcmp(saisie_bateaux, "0") !=10 && (strcmp(saisie_bateaux, "0")))
	{
	  printf("Saisie invalide, recommence\n");
	  fgets(saisie_bateaux,10,stdin);
	}
      
   
      if (strcmp(saisie_bateaux, "0") == 10)
	{
	  fleet_1[i].orientation = HORIZONTAL;
	}
      else if (strcmp(saisie_bateaux, "1") == 10)
	{
	  fleet_1[i].orientation = VERTICAL;
	}
      print_ship(basic_rules, fleet_1[i]);
    }
  
  printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
  print_Color(ROUGE, "!!!!!!!!!!!!!!!!!!!!!!!!WARNING!!!!!!!!!!!!!!!!!!!!!!!!");
  printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");



  //Placement des bateaux de Joueur 2

  printf("\n%s, tu vas maintenant devoir placer tes 6 Bateaux\n", name2);
 
  for (int i=0;i<fleet_size_2-1;i++)
    {
      
      printf("\n\nDonne une coordonnee pour placer ton %s 1 chiffre pour les abcisses, 1 lettre pour les ordonnées\n", ship_labels[fleet_2[i].kind]);
      printf("\nPour info un %s fait %d cases de long/large\n",ship_labels[fleet_2[i].kind],ship_size(basic_rules, fleet_2[i]));
      fgets(saisie_bateaux,10,stdin);
      fleet_2[i].position =parse_position(saisie_bateaux);  
      printf("Dans quel sens veux tu le placer? 0 Horizontal, 1 Vertical\n");
      fgets(saisie_bateaux,10,stdin);
        
      if (strcmp(saisie_bateaux, "0") == 10)
	    
	{
	  fleet_2[i].orientation = HORIZONTAL;
	}
      else if (strcmp(saisie_bateaux, "1") == 10)
	{
	  fleet_2[i].orientation = VERTICAL;
	}
      else if (strcmp(saisie_bateaux, "0") !=10 && (strcmp(saisie_bateaux, "0")))
	{
	  printf("Saisie invalide, recommence\n");
	  fgets(saisie_bateaux,10,stdin);
	}
      if (strcmp(saisie_bateaux, "0") == 10)
	{
	  fleet_2[i].orientation = HORIZONTAL;
	}
      else if (strcmp(saisie_bateaux, "1") == 10)
	{
	  fleet_2[i].orientation = VERTICAL;
	}
      print_ship(basic_rules, fleet_2[i]);
    }
  
  return 0;
}

