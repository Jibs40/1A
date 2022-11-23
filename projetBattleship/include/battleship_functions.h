#ifndef BATTLESHIP_FUNCTIONS_h
#define BATTLESHIP_FUNCTIONS_h


#define NB_PLAYERS 2
#define MAX_LENGHT_NAME 10
#define LONGEST_SHIP    5

// Déclaration des structs

struct position {int x;int y;}; 
struct dimension {int width;int height;};
enum orientation { HORIZONTAL, VERTICAL };
enum ship_kind {DESTROYER, SUBMARINE, CRUISER, BATTLESHIP, CARRIER, LAST_SHIP};
static const char* const ship_labels[] = {"Destroyer", "Submarine", "Cruiser", "Battleship", "Carrier"};
struct rules {const int ships_count[LAST_SHIP];const int ships_size[LAST_SHIP];};
struct ship { enum ship_kind kind; struct position position; enum orientation orientation;int state[LONGEST_SHIP];};
enum couleur {ROUGE,VERT,JAUNE, BLEUE};
static struct rules basic_rules = { { 2, 2, 1, 1, 1 }, { 2, 1, 3, 4, 5 },};

// Déclaration des fonctions affichage

int index_grid (int largeur, struct position coord);
void print_grid (int largeur, int hauteur, int state_grid[]);
void print_Color(int color, const char *msg);
void print_END();


//Déclaration des fonctions système

int sum(int n, const int array[]);
int inside(struct position pos, struct position origin, struct dimension dim);
void constrain(struct position *pos, struct dimension dim);
int offset(struct position pos, struct position origin);
int ship_size(struct rules rules, struct ship ship);
struct dimension ship_dimension(struct rules rules, struct ship ship);
int remaining_life(struct rules rules, struct ship ship);
void print_position(struct position pos);
void print_ship(struct rules rules, struct ship ship);
struct position parse_position(const char *str);
struct ship *find_target(struct rules rules, struct position pos, int fleet_size, struct ship fleet[]);
int hit(struct rules rules, struct position pos, int fleet_size, struct ship fleet[]);
int fire(struct rules rules, struct position pos,int fleet_size, struct ship fleet[]);
int ships_remaining(struct rules rules, int fleet_size, const struct ship fleet[], int remains[]);
int ship_overlap(struct rules rules, struct ship ship, int fleet_size, struct ship fleet[]);
int init_ships (struct ship fleet_1[], struct ship fleet_2[], char name1[], char name2[], char saisie_bateaux[], int fleet_size_1, int fleet_size_2);

#endif
