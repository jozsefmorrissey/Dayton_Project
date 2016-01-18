#define _GNU_SOURCE 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <fcntl.h>  
#include <sys/types.h>
#include <sys/wait.h>


//STRUCTURES
typedef struct island{
	int bay;
	char location[7]; 
	char orientation[5];
	struct island * next;
}island;

typedef struct scale{
	int bay;
	char location[7]; 
	struct scale * next;
}scale;

typedef struct destination{
	char dest[4];
	struct destination * next;
}destination;

typedef struct door_number{
	int door;
	struct door_number * next;
}door_number;

typedef struct truck_info{
	door_number * doors;   //variables neccesary for drawing
	char dest[4];
	int handling_units;
	long weight;
	char head;
	char tail;
	destination * destinations;

	char docked;	
	char bay_choice;
}truck_info;

typedef struct bay_layout{
	truck_info * occupier;
	char id[16];
}bay_layout;

typedef struct{//All variables neccisary for drawing
	char terminal [4];
	int doors;
	island * islands;
	scale * scales;
	bay_layout * bays;
}dock_information;

typedef struct freight{
	char dest[4];
	int handling_units;
	long weight;
}freight;

//CONSTANTS
#define EVEN (0)
#define ODD (1)
#define MIDDLE (2)

#define READ			(0)
#define WRITE			(1)

#define DOOR_LENGTH (15)
#define INFO_LENGTH (1000)

char * pos[3] = {"Top", "Bottom", "Middle"};
char * orient[2] = {"Down", "Up"};


//GLOBAL VARIABLES
dock_information dock_info;
truck_info * trucks;
int num_trucks;

//FUNCTIONS
//Main functions
void ex_py();
void print_data(FILE * out);
void print_dock_info(FILE * out);
void print_trucks_info(FILE * out);

//Input fundtions;
void prompt();
int get_doors();
int get_islands(island ** islands, int doors, char * type);
void clear_buffer();
int getint(int ** array, int max, int min);
int get_std_input(char * responses[], int len);
int exicute(int * doors, int num_doors, char ** bays[], int num_bays);
int num_bays(int doors);
void create_file();
char * find_terminal(FILE * file);
void change_default(char* location);
char * num_blanks(int num);
void file_start_location(FILE * layout, char * term);


//Bay Alloc funtions
void empty_bays(int num_bays, char *** bays);
int choice(int door, int num);
int choice_1(int door);
int choice_2(int door);
int choice_3(int door);
int choice_4(int door);
int choice_5(int door);
int choice_6(int door);
void remove_occupied_bays(bay_layout * bays);
void alloc_bays(bay_layout ** bays);
int find_avail_bay(truck_info * truck, bay_layout * bays, int max);
int check_availability(bay_layout * bay, int bay_num);
void set_bay(bay_layout * bays, int bay_num, truck_info * truck);
void print_bays(bay_layout * bays);
void print_choices();



//dock info functions
void calc_bays(FILE * file);
void dock_failed(char * cond, int line);
void get_door(char * string);
void init_scales(char * file);
void init_islands(char * string);
void locate_terminal_info(FILE * file);
int init_dock_info();
void print_info();
void destroy_dock();
void destroy_island_list(island * head);
void destroy_scales_list(scale * head);


//truck info functions
destination * save_dest(truck_info * truck, destination ** head, destination ** cur, char dest[4]);
void init_trucks();
void print_truck_info();
int get_lines(FILE * file);
void print_dest_list(destination * d);
void destroy_dest_list(destination * cur);
void destroy_truck_list();
void init_freight_data();
char * door_string(truck_info * truck);
void add_door(truck_info * truck, int door_num);
void destroy_door_list(door_number * doors);
void destroy_truck(truck_info * cur_truck);

//Process info funtions
int truck_cmp(truck_info * t1, truck_info * t2);
void check_identical_trucks();
int num_destinations(truck_info * truck);
int destinations_cmp(const void * t1, const void * t2);
void len_sort();
void sort(int (*cmp)(const void*, const void *));





