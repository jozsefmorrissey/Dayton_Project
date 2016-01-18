
int init_dock_info(){
	FILE * file = fopen("../Info/dock_layout.txt", "r");
	if(file == NULL){
		dock_failed("open dock_layout.txt", __LINE__);
		exit(1);
	}

	dock_info.islands = NULL;
	dock_info.scales = NULL;
	dock_info.bays = NULL;
	
	locate_terminal_info(file);

	//print_info();

	fclose(file);
	
	return 0;
}


//Retreave default terminal information from text file
void locate_terminal_info(FILE * file){
	char * line = "";
	size_t size = 0;
	char terminal[4] = "zzz";
	while(1){
		if(getline(&line, &size, file) == EOF){
			dock_failed("find terminal", __LINE__);
			free(line);
			exit(1);
		}
		if(strstr(line, "Default:") == line){
			char string[strlen(line)];
			strcpy(string, line);
			string[strlen(string) - 1] = '\0';
			strcpy(terminal, &string[9]);
		}
		if(strcmp(terminal, "zzz") && strstr(line, terminal) == line){
			strcpy(dock_info.terminal, terminal);
			getline(&line, &size, file);
			get_door(line);
			getline(&line, &size, file);
			init_islands(line);
			getline(&line, &size, file);
			init_scales(line);
			break;
		}

	}

	
	free(line);
}


//Get door #
void get_door(char * string){
	char * start = strstr(string, " ");
	dock_info.doors = atoi(start);
}


//Retrieve island information from text file.
void init_islands(char * string){

	island * cur_island;
	island * prev_island;
	
	while(strstr(string, "/") != NULL){
		cur_island = malloc(sizeof(island));
		cur_island->next = NULL;
		
		if(dock_info.islands == NULL)
			dock_info.islands = cur_island;
		else
			prev_island->next = cur_island;
			
		//Retrieve bay information
		char * start = strstr(string, " ");
		char * end = strstr(start, "/");
		string = &end[1];
		*end = '\0';
		cur_island->bay = atoi(start);
		
		//Retrieve location information
		start = string;
		end = strstr(start, "/");
		string = &end[1];
		*end = '\0';
		strcpy(cur_island->location, start);
		
		//Retrieve orientation information
		start = string;
		end = strstr(start, ",");
		string = &end[1];
		*end = '\0';
		strcpy(cur_island->orientation, start);
		
		prev_island = cur_island;
	}
}


void init_scales(char * string){
	
	scale * cur_scale, * prev_scale;
	
	while(strstr(string, "/") != NULL){
		
		cur_scale  = malloc(sizeof(scale));
		cur_scale->next = NULL;
		
		if(dock_info.scales == NULL)
			dock_info.scales = cur_scale;
		else
			prev_scale->next = cur_scale;
		
		char * start = strstr(string, " ");
		char * end = strstr(start, "/");
		string = &end[1];
		*end = '\0';
		cur_scale->bay = atoi(start);
		
		start = string;
		end = strstr(start, ",");
		string = &end[1];
		*end = '\0';
		strcpy(cur_scale->location, start);
		
		prev_scale = cur_scale;
	}
}


void calc_bays(FILE * file){

}

void dock_failed(char * cond, int line){
	fprintf(stderr, "Failed to %s in dock_info.h at line %i\n", cond, line);
}


//Print dock information
void print_info(){
	char * terminal = dock_info.terminal;
	int doors = dock_info.doors;
	island * islands = dock_info.islands;
	scale * scales = dock_info.scales;
	//bay_layout bays = dock_info.bays;
	
	printf("Terminal location: %s with %i doors\n", terminal, doors);
	
	//display island infromation
	printf("\nISLAND INFO:\n");
	while(islands != NULL){
		printf("Bay: %i \t Location: %s \t Orientation: %s\n", islands->bay, islands->location, islands->orientation);
		islands = islands->next;
	}
	
	//display scale information
	printf("\nSCALE INFO:\n");
	while(scales != NULL){
		printf("Bay: %i \t Location: %s\n", scales->bay, scales->location);
		scales = scales->next;
	}
}


void destroy_dock(){
	destroy_scales_list(dock_info.scales);
	destroy_island_list(dock_info.islands);
	if(dock_info.bays != NULL)
		free(dock_info.bays);
}


void destroy_scales_list(scale * head){
	if(head == NULL)
		return;
	if(head->next != NULL)
		destroy_scales_list(head->next);
	free(head);
}


void destroy_island_list(island * head){
	if(head == NULL)
		return;
	if(head->next != NULL)
		destroy_island_list(head->next);
	free(head);
}
	
	
	
	
	
	
	
	




