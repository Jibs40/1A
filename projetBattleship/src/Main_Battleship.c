#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "battleship_functions.h"
                
int main(int argc, char* argv[])
{
  //argc et argv ne sont pas utilisés
  
  (void)argc;
  (void)argv;

  //Parcours menu entrée
  
  char choix[5]={};
  int jeu = 0;
  
  print_Color(ROUGE, "\t--------------------------------------------------------------------------------------------------\n");   
  printf("\t     _______  _______  _______  _______  ___      _______  _______  __   __  ___   _______ \n");
  printf("\t    |  _    ||   _   ||       ||       ||   |    |       ||       ||  | |  ||   | |       |\n");
  printf("\t    | |_|   ||  |_|  ||_     _||_     _||   |    |    ___||  _____||  |_|  ||   | |    _  |\n");
  printf("\t    |       ||       |  |   |    |   |  |   |    |   |___ | |_____ |       ||   | |   |_| |\n");
  printf("\t    |  _   | |       |  |   |    |   |  |   |___ |    ___||_____  ||       ||   | |    ___|\n");
  printf("\t    | |_|   ||   _   |  |   |    |   |  |       ||   |___  _____| ||   _   ||   | |   |    \n");
  printf("\t    |_______||__| |__|  |___|    |___|  |_______||_______||_______||__| |__||___| |___|    \n\n\n");
  print_Color(ROUGE, "\t--------------------------------------------------------------------------------------------------\n\n");  
		     

  print_Color(BLEUE, "\n\n\n\t\t\tBIENVENUE DANS BATTLESHIP 2020 4.0!!!!\n\n\n");
  print_Color(BLEUE, "\t1/Démarrer une partie en mode 1 joueur\n\t\n\t2/Démarrer une partie en mode 2 joueurs\n\t\n\t3/Quitter\n\n\n\tVeuillez taper, svp, le chiffre correspondant à votre choix suivi de la touche entrer\n");
 
  fgets(choix,10,stdin);
  if (strcmp(choix,"2")==10) // Lancement de partie

    {
      // Mode 2 joueurs
      // Declaration des bateaux Joueur 1

      struct ship bateau_1;
      struct ship bateau_2;
      struct ship bateau_3;
      struct ship bateau_4;
      struct ship bateau_5;
      struct ship bateau_6;

      // Constitution flotte Joueur 1
	  
      bateau_1.kind = DESTROYER; 
      bateau_2.kind = DESTROYER; 
      bateau_3.kind = SUBMARINE; 
      bateau_4.kind = CARRIER;   
      bateau_5.kind = CRUISER;    
      bateau_6.kind = BATTLESHIP;
  
      // Declaration des bateaux du joueur 2
	  
      struct ship bateau_12;
      struct ship bateau_22;
      struct ship bateau_32;
      struct ship bateau_42;
      struct ship bateau_52;
      struct ship bateau_62;

      // Constitution flotte Joueur 2

      bateau_12.kind = DESTROYER; 
      bateau_22.kind = DESTROYER; 
      bateau_32.kind = SUBMARINE; 
      bateau_42.kind = CARRIER;   
      bateau_52.kind = CRUISER; 
      bateau_62.kind = BATTLESHIP;
	  
      // Constitution des différents fleets
	  
      struct ship fleet_1[7] = {bateau_1,bateau_2,bateau_3,bateau_4,bateau_5,bateau_6};
      struct ship fleet_2[7] = {bateau_12,bateau_22,bateau_32,bateau_42,bateau_52,bateau_62}; 

      // Gestion de la grille
	  
      char width_grid = 10;
      char lenght_grid=10;
      int hauteur = lenght_grid;
      int largeur = width_grid;
      int lenght = hauteur*largeur;
      int state_grid_1[lenght];
      int state_grid_2[lenght];
	

      // Nécessaire pour tir
      char tir [5] = {0};
      struct position coordonnees;
      int state_fire_1 =5;
      int state_fire_2 = 5;

	  
      // Fonction Init_ships
	  			    
      char saisie_bateaux[20];
      char name1[MAX_LENGHT_NAME];
      char name2[MAX_LENGHT_NAME]; 
      int fleet_size_1 = 7;
      int fleet_size_2 = 7;
      int count_bateau_1 = fleet_size_1-1;
      int count_bateau_2 = fleet_size_2-1;

      //Création des joueurs

      printf("\n\n");
      print_Color(BLEUE,"Joueur 1 , entre ton nom stp\n");
      fgets(name1,10,stdin);
      print_Color(BLEUE,"Joueur 2 , entre ton nom stp\n");
      fgets(name2,10,stdin);

      //Provision pour changer la taille de la grille à insérer plus tard pour éventuelle évolution
	  
      // Init grid_parameters

      /*	  printf("Veuillez entrer une largeur de grille");
		  scanf("%d",width_grid);
		  printf("Veuillez entrer une hauteur de grille");
		  scanf("%d", lenght_grid);*/



	  
      // Init du tableau state_grid de chaque joueur
	  
      for (int i=0;i<lenght;i++)
	{
	  state_grid_1[i]=-2;
	  state_grid_2[i]=-2;
	}
  
      //Déclaration des bateaux
	  
      init_ships(fleet_1, fleet_2, name1, name2,saisie_bateaux, fleet_size_1, fleet_size_2);
	  
      while(jeu==0)
	{
	  //Au premier joueur de jouer
	      
	  printf("\n\nGrille de %s",name1);
	  print_grid (largeur,hauteur,state_grid_2);
	  printf("\nA toi de jouer %s Entre stp les coordonnées de ton tir ou Exit pour quitter\n", name1);
	  fgets(tir,10,stdin);

	  if (strcmp(tir,"Exit")==10 || strcmp(tir,"exit")==10)
	    {
	      print_END();
	      break;
	    }      
	  else
	    {
	      coordonnees=parse_position(tir);
	      state_fire_2 = fire(basic_rules,coordonnees,fleet_size_2,fleet_2);
	      if (state_fire_2==-1)
		{
		  state_grid_2[index_grid(largeur,coordonnees)]=-1;
		}
	      if (state_fire_2==0)
		{
		  state_grid_2[index_grid(largeur,coordonnees)]=0;
		}
	      if (state_fire_2>0)
		{
		  state_grid_2[index_grid(largeur,coordonnees)]=0;
		  count_bateau_2 --;
		}
	      if (count_bateau_2 == 0)
		{
		  print_Color(VERT, "YOU WIN!!!");
		  printf("\n");
		  print_END();
		  break;
		}

	    }
	  
	  // Au deuxieme joueur de jouer
	  
	  printf("\n\nGrille de %s",name2);
	  print_grid (largeur,hauteur,state_grid_1);
	  printf("\nA toi de jouer %s Entre stp les coordonnées de ton tir ou Exit pour quitter\n", name2);
	  fgets(tir,10,stdin);

	  if (strcmp(tir,"Exit")==10 || strcmp(tir,"exit")==10)
	    {
	      print_END();
	      break;
	    }
	  else
	    {
	      coordonnees=parse_position(tir);
	      state_fire_1 = fire(basic_rules,coordonnees,fleet_size_1,fleet_1);
	      if (state_fire_1==-1)
		{
		  state_grid_1[index_grid(largeur,coordonnees)]=-1;
		}
	      if (state_fire_1==0)
		{
		  state_grid_1[index_grid(largeur,coordonnees)]=0;
		}
	      if (state_fire_1>0)
		{
		  state_grid_1[index_grid(largeur,coordonnees)]=0;
		  count_bateau_1 --;
		}

	      if (count_bateau_1 == 0)
		{
		  print_Color(VERT, "YOU WIN!!!");
		  printf("\n");
		  print_END();
		  break;
		}

	    }
 
	}
    }    
 
  else if(strcmp(choix,"1")==10)
    {
      //Mode 1 joueur : Init des variables
      
      char tir [10];
      int jeu = 0;
      char width_grid = 10;
      char lenght_grid=10;
      int hauteur = lenght_grid;
      int largeur = width_grid;
      int lenght = hauteur*largeur;
      int state_grid_mono[lenght];
      int state_fire_mono =5;
      int fleet_size_mono = 7;
      int count_bateau_comp = fleet_size_mono;
      struct position coordonnees;

      //Déclaration des Bateaux
      struct ship bateau_1mono;
      struct ship bateau_2mono;
      struct ship bateau_3mono;
      struct ship bateau_4mono;
      struct ship bateau_5mono;
      struct ship bateau_6mono;
      
      //Init des tableaux states des bateaux correspondants
	  
      for (int i =0;i<LONGEST_SHIP;i++)
	{
	  bateau_1mono.state[i]=0;
	  bateau_2mono.state[i]=0;
	  bateau_3mono.state[i]=0;
	  bateau_4mono.state[i]=0;
	  bateau_5mono.state[i]=0;
	  bateau_6mono.state[i]=0;
	}
	  
 
      //Codage des positions en dur, pourra être remplacé dans de futures évolutions
      
      bateau_1mono.kind = DESTROYER; bateau_1mono.position.x=6; bateau_1mono.position.y=7; bateau_1mono.orientation = VERTICAL; 
      bateau_2mono.kind = DESTROYER; bateau_2mono.position.x=3; bateau_2mono.position.y=3; bateau_2mono.orientation = VERTICAL;
      bateau_3mono.kind = SUBMARINE; bateau_3mono.position.x=4; bateau_3mono.position.y=1; bateau_3mono.orientation = HORIZONTAL;
      bateau_4mono.kind = CARRIER; bateau_4mono.position.x=7; bateau_4mono.position.y=3; bateau_4mono.orientation = VERTICAL; 
      bateau_5mono.kind = CRUISER; bateau_5mono.position.x=0; bateau_5mono.position.y=8; bateau_5mono.orientation = HORIZONTAL; 
      bateau_6mono.kind = BATTLESHIP; bateau_6mono.position.x=0; bateau_6mono.position.y=2; bateau_6mono.orientation = HORIZONTAL;

      
      //Rassemblement dans le fleet mono
      
      struct ship fleet_mono[7] = {bateau_1mono,bateau_2mono,bateau_3mono,bateau_4mono,bateau_5mono,bateau_6mono};
      
      // Init de la grid joueur
      
      for (int i=0;i<lenght;i++)
	{
	  state_grid_mono[i]=-2;
	}

      // Boucle de jeu mode 1 joueur
      
      while(jeu==0)
	{
	  print_grid (largeur,hauteur,state_grid_mono);
	  printf("\nA toi de jouer! Entre stp les coordonnées de ton tir ou Exit pour quitter\n");
	  fgets(tir,10,stdin);

	  if (strcmp(tir,"Exit")==10 || strcmp(tir,"exit")==10)
	    {
	      print_END();
	      break;
	    }
	  
	  else
	    {
	      coordonnees=parse_position(tir);
	      state_fire_mono = fire(basic_rules,coordonnees,fleet_size_mono,fleet_mono);
	      if (state_fire_mono==-1)
		{
		  state_grid_mono[index_grid(largeur,coordonnees)]=-1;
		}
	      if (state_fire_mono==0)
		{
		  state_grid_mono[index_grid(largeur,coordonnees)]=0;
		}
	      if (state_fire_mono>0)
		{
		  state_grid_mono[index_grid(largeur,coordonnees)]=0;
		  count_bateau_comp --;
		}
	      if (count_bateau_comp == 0)
		{
		  print_Color(VERT, "\n\nYou win!\n\n");
		  break;
		}
	      
	    }
	}
      
      // Choix quitter, affiche les crédits
      
      if(strcmp(choix,"3")==10)
	{
	  print_END();	      
	}
      return 0;
    }

}








