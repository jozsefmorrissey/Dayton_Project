
void file_start_location(FILE * layout, char * term){
	char cmp[5] = "";
	strcpy(cmp, term);
	strcat(cmp, ":\n");
	char * line = "";
	size_t size = 0;
	fseek(layout, 0, SEEK_SET);
	while(getline(&line, &size, layout) != EOF){
		if(!strcmp(line, cmp))
			return;
	}
	fprintf(layout, "\n\n%s", cmp); 
}


char* find_terminal(FILE * file){
	fseek(file, 0, SEEK_SET);
	int length = 1;
	char * list = malloc(length * 4 + 1);
	char * line = "";
	size_t size = 0;
	int count = 0;
	while(getline(&line, &size, file) != EOF){
		if((int)(strstr(line, ":") - (int)line) == 3){
			if(count == length){
				length *= 2;
				list = realloc(list, length * 4 + 12);
			}
			line[3] = '\0';
			strcpy((list + count *4), line);
			count++;
		}
	}	
	sprintf((list +4*count), "NOT LISTED\n");
		
	printf("Enter the number that corresponds to your terminal:\n");
	int i = 0;
	for(; i < count+1; i++)
		printf("%i: %s%c", i+1, (list + 4*i), ((i+1)%3 == 0 ? '\n' : '\t')); 
		
	int *index; 
	while(getint(&index, count + 1, 1) != 1)
		if(*index > 1)
			printf("Please enter a single valid number\n");
	char loc[4];
	strcpy(loc,  (list + (*index - 1) * 4));
	strcpy(list, loc);
	if(*index <= count){
		free(line);
		return list;
	}
	printf("Please enter the three digit abrivation for your terminal: ");
	while((length = getline(&line, &size, stdin)) != -1){
		if(length == 4){
			i = 0;
			line[3] = '\0';
			for(; i < 4; i++)
				list[i] = (char)(toupper((int)(line[i])));
			while(length == 4){
				printf("Is %s your terminal? ", list);
				getline(&line, &size, stdin);
				if(line[0] == 'y' || line[0] == 'Y'){
					free(line);
					return list;
				}
				else if(line[0] == 'n' || line[0] == 'N'){
					break;
				}
				else
					printf("Please enter Y or n\n");
			}
		}
		else
			printf("Please enter the 3 digit abriviation for your terminal.\n");
	}
	strcpy(list, "FAILED");
	free(line);
	return list;
}


void change_default(char* location){
	FILE * file = fopen("../Info/dock_layout.txt", "r+");
	char * line = "";
	size_t size = 0;
	size_t len = 0;
	len = getline(&line, &size, file);
	while(line != strstr(line, "Default:"))
		len = getline(&line, &size, file);
	fseek(file, -(long)len, SEEK_CUR);
	fprintf(file, "Default: %s", location);
	
}


char * num_blanks(int num){
	char * ret = calloc(1, num);
	int i = 0;
	for(; i<num-1; i++)
		ret[i] = ' ';
	ret[i] = '\0';
	return ret;
}


void create_file(){
	FILE * file = fopen("../Info/dock_layout.txt", "w");
	fprintf(file, "//First Line: Terminal Location\n\n//Second Line: Number trailer doors on the dock\n\n//Location within bay: T or Top, M or Middle, B or Bottom\n//Orientation: U or Up, D or Down\n\n//Third Line: Island locations within dock and bay aswell as its orientation\n//Format (baynumber)/(location within bay)/(orientation of island intrance),\n\n//Fourth Line: Scale location within dock and bay\n//Format (baynumber)/(location within bay),\nDefault: NOT"); 
	fflush(NULL);
}


void prompt(){
	int doors = get_doors();
	island * islands;
	int num_islands = get_islands(&islands, doors, "island");
	island * scales;
	int num_scales = get_islands(&scales, doors, "scale");
	int i = 0;
	FILE * layout = fopen("../Info/dock_layout.txt", "r");
	if(layout == NULL)
		create_file();
	else
		fclose(layout);
	layout = fopen("../Info/dock_layout.txt", "r+");
	
	char * terminal = find_terminal(layout);
	change_default(terminal);
	file_start_location(layout, terminal);
	
	char first[DOOR_LENGTH] = "";
	sprintf(first, "Doors: %i", doors);
	fprintf(layout, "%s%s\nIslands: ", first, num_blanks(DOOR_LENGTH - strlen(first)));
	char second[INFO_LENGTH] = "";
	for(; i< num_islands; i++){
		char constructor[25] = "";
		sprintf(constructor, "%i/%s/%s, ", (islands + i)->bay, (islands + i)->location, (islands + i)->orientation);
		strcat(second, constructor);
	}
	fprintf(layout, "%s%s\nScales: ", second, num_blanks(INFO_LENGTH - strlen(second)));
	strcpy(second, "\0");
	for(i = 0; i < num_scales; i++){
		char constructor[25] = "";	
		sprintf(constructor,"%i/%s, ", scales[i].bay, scales[i].location);
		strcat(second, constructor);
	}
	fprintf(layout, "%s%s\n", second, num_blanks(INFO_LENGTH - strlen(second)));
	char ** bays;
	//int d[2] = {1, 2};
	empty_bays(num_bays(doors), &bays);
	exicute(NULL, 0, &bays, num_bays(doors));
	free(bays);
}


int exicute(int * doors, int num_doors, char ** bays[], int num_bays){
	int comm[2];
	pipe(comm);
	pid_t child = fork();
	if(child == 0){
		close(comm[WRITE]);
 		dup2(comm[READ], fileno(stdin));
		execl("py", "py", "NULL", "D", NULL); //helloworld.py DAN D", NULL);
		printf("Execute failed\n");
		exit(0); 
	}
	FILE * out = fdopen(comm[WRITE], "w");
	int i;
	for(i = 0; i < num_doors; i++){
		fprintf(out, "%i\n", *(i + doors));
	}
	fprintf(out, "END\n");
	for(i = 0; i < num_bays; i ++){
		fprintf(out, "%s\n", *(i + *bays));
	}
	fprintf(out, "END\n");
	int status = 0;
	waitpid(child, &status, WIFEXITED(status));
	return 0;
}


int num_bays(int doors){
	return (doors - 4)/2;
}





int get_islands(island ** islands, int doors, char * type){
	int * array;
	int number_of_bays = doors/4 - 1;
	int incorrect = 1;
	while(incorrect){
		printf("Enter the bay numbers that coorespond to %s locations seperated by a space: ", type);
		int read = getint(&array, number_of_bays, 1);
		int bays[read][3];
		while(incorrect && read != -1){
			if(read == 1)
				printf("Is bay %i the only bay with an %s in it?(yes/no)", array[0], type);
			else{
				printf("Are, ");
				int i = 0;
				for(; i < read; i++)
					printf("%i ", array[i]);
				printf(",all the bays at your terminal with %s %s(yes/no)?", (strcmp(type, "scale") ? "an": "a"), type);
			}
			char * response[4] = {"y", "yes", "no", "n"};
			int num = get_std_input(response, 4);
			if(num == 0 || num == 1){
				int i;
				for(i = 0; i < read; i++){
					bays[i][0] = array[i];
					printf("Enter the location of the %s within bay %i: \n", type, array[i]);
					printf("(even if its on the side with even door numbers, odd, or middle for in the middle)\n");
					char orien[10];
					char * options[6] = {"even", "e", "odd", "o", "middle", "m"};
					num = get_std_input(options, 6);
					if(num == 0 || num == 1)
						bays[i][1] = EVEN;
					else if(num == 2 ||num == 3)
						bays[i][1] = ODD;
					else if(num == 4 || num == 5)
						bays[i][1] = MIDDLE;
					else if(num == -1){
						printf("Error: your input could not be understood.\n");
						i --;
					}
					while(num > -1 && strcmp(type, "scale")){
						printf("Enter the orientation of the island within bay %i:\n", bays[i][0]);
						printf("(even for bays facing the even doors, or odd)\n");
						char * orientation[4] = {"even", "e", "odd", "o"};
						int orien = get_std_input(orientation, 4);
						if(orien == 0 || orien == 1){
							bays[i][2] = EVEN;
							break;
						}
						else if(orien == 2 || orien == 3){
							bays[i][2] = ODD;
							break;
						}
						else{
							printf("Error: your input could not be understood.\n");
						}
					}
					if(i == read - 1){
						incorrect = 0;
						*islands = malloc(sizeof(island)*read);
						int j = 0;
						for(; j < read; j++){
							(*islands + j)->bay =  bays[j][0];
							strcpy((*islands + j)->location,  pos[bays[j][1]]);
							if(strcmp(type, "scale"))
								strcpy((*islands + j)->orientation,  orient[bays[j][2]]);
						}
						return read;
					}
				}
			}
			else if(num == 2 || num == 3){
				printf("Error: try again, please follow input instructions.\n");
				break;
			}
			else{
				printf("Error: your response could not be understood.\n");
			}
		}		
	} 
	return 0;
}	




int get_doors(){
	int * doors;
	int error = 0;
	int max = 100;
	char returnChar;
	while(error != 1){
		printf("Enter number of trailer doors at your terminal: ");
		error = getint(&doors, max, 0);
		clear_buffer();
		if(error == -1)
			exit(0);
		if(error != 1)
			printf("Please enter one and only one number\nEnter '-1' to exit\n");	
	}
	int ret = *doors;
	free(doors);
	return ret;
}


void clear_buffer(){
	fseek(stdin, 0, SEEK_END);
}


int getint(int ** array, int max, int min){
	char * line = "";
	size_t size = 0;
	int read = getline(&line, &size, stdin);
	*array = malloc(sizeof(int)*read/2);
	int * assembler = *array;
	int i = 0;
	char * worker;
	worker = line;
	int counter = 0;
	for(; i<read + 1; i++){

		if(line[i] > '9' || line[i] < '0'){
			line[i] = 0;
			if(strlen(worker) > 0){
				*assembler = atoi(worker);
				if(*assembler > max || *assembler < min){
					printf("Error: one or more entries were out side of the bounds, entries should be in range %i to %i.\n", min, max);
					free(*array);
					return -1;
				}
				assembler++;
				counter++;
				worker = &line[i+1];
			}
		}
	}
	return counter;
}


int get_std_input(char * responses[], int len){
	char * line = "";
	size_t size = 0;
	int read = getline(&line, &size, stdin);
	if(read == -1)
		printf("Failed to read input at line %i\n", __LINE__);
	int j = 0;
	for(; j < len; j++){
		char * curr = responses[j];
		int i = 0;
		for(; i < strlen(curr) && i < strlen(line); i++){
			if(curr[i] != tolower(line[i]))
				break;
			if(i == strlen(line) - 2 && i == strlen(curr) - 1)
				return j;
		}
	}	
	return -1;
}
