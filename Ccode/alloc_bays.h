

void alloc_bays(bay_layout ** bays){
	int size = num_bays(dock_info.doors);
	*bays = calloc(sizeof(bay_layout), size);

	remove_occupied_bays(*bays);

	//truck_info * alloc_list;
	//int max = init_alloc_list(&alloc_list);

	truck_info * truck = trucks;
	int i = 0;
	for(; i < num_trucks; i++){
		int check = find_avail_bay(truck + i, *bays, 6);
		if(i % 50 == 0){
			printf("round %i\n", i);
			print_bays(*bays);
		}
		if(check == -1)
			printf("failed to allocate a bay for the %s truck in door %i\n", (truck + i)->dest, (truck + i)->doors->door);
		else{
			printf("check: %i\n", check);
			set_bay(*bays, choice((truck + i)->doors->door, check), truck + i);
		  //print_bays(&bays);
		}
	}
}





void print_bays(bay_layout * bays){
	int i = 0;
	int limit = num_bays(dock_info.doors);
	for(; i < limit; i++)
		//printf("bay: %i id is: %s\n", i + 1, (bays + i)->id); 
		printf("'%.2s'   ", (bays+i)->id);
	printf("\n");
}


void set_bay(bay_layout * bays, int bay_num, truck_info * truck){
	(bays + bay_num)->occupier = truck;
	char door[16];
	sprintf(door, "%i", truck->doors->door);
	strcpy((bays + bay_num)->id, door);
}


int find_avail_bay(truck_info * truck, bay_layout * bays, int max){
	int i = truck->bay_choice;
	int bay_num;
	int bay_max = num_bays(dock_info.doors);
	for(; i < max; i++){
		truck->bay_choice = i;
		bay_num = choice(truck->doors->door, i);
		if(check_availability((bays) + bay_num, bay_num)){
			return i;
		}
		else if(((bays) + bay_num)->occupier != NULL){
			truck_info * cur = ((bays) + bay_num)->occupier;
			int ch= cur->bay_choice;
			cur->bay_choice++;
			//int max = bay_num - 1 > 4? 4 : bay_num;
			int assigned = find_avail_bay(cur, bays, 6);
			if(assigned != -1 && assigned < 3 && assigned < i + 1){
				strcpy((bays + choice(truck->doors->door, i))->id, " ");
				(bays + choice(truck->doors->door, i))->occupier = NULL;
				set_bay(bays, choice(cur->doors->door, assigned), cur);
				cur->bay_choice = assigned;
				
				return i;
			}
			else
				cur->bay_choice = ch;
		}
	}
	return -1;
}

int check_availability(bay_layout * bay, int bay_num){
	int min = 0;
	int max = num_bays(dock_info.doors) - 1;
	if(bay_num < min || bay_num > max)
		return 0;
	if(bay->occupier == NULL && strcmp(bay->id, "O"))
		return 1;
	return 0;
}

void remove_occupied_bays(bay_layout * bays){
	scale * scales = dock_info.scales;
	island * islands = dock_info.islands;
	while(scales != NULL){
		if(!strcmp(scales->location, "Top")){
			int bay = scales->bay*2 - 1;
			strcpy((bays + bay)->id, "O");
			//print("Bay");
		}
		if(!strcmp(scales->location, "Bottom")){
			int bay = scales->bay*2 - 2;
			strcpy((bays + bay)->id, "O");
		}
		scales = scales->next;
	}
	while(islands != NULL){
		if(!strcmp(islands->location, "Top")){
			int bay = islands->bay*2 - 1;
			strcpy((bays)->id, "O");
		}
		if(!strcmp(islands->location, "Bottom")){
			int bay = islands->bay*2 - 2;
			strcpy((bays)->id, "O");
		}
		islands = islands->next;
	}
}


void empty_bays(int num_bays, char *** bays){
	int i;
	*bays = (char**)calloc(1, (sizeof(char*) + 16)*num_bays);
	for(i = 0; i < num_bays; i++){
		char ** cur = *bays + i; 
		*cur = (char*)(*bays + num_bays + i*2);
		char * temp = "";
		strcpy(*cur, temp);
	}		
}

int choice(int door, int num){
	int ret = 0;
	switch(num + 1){
		case 1:
			ret = choice_1(door);
			break;
		case 2:
			ret = choice_2(door);
			break;
		case 3:
			ret = choice_3(door);
			break;
		case 4:
			ret = choice_4(door);
			break;
		case 5:
			ret = choice_5(door);
			break;
		case 6:
			ret = choice_6(door);
			break;
	}
		if(ret < 0 || ret > num_bays(dock_info.doors))
			return 0;
			
		return ret-1;
}


int choice_1(int door){
	int ret = door/2;
	if(door % 2 == 0){
		if(ret % 2 == 1)
			ret -= 1;
	}
	else{
		if(ret % 2 == 0)
			ret -=1;
	}
	return ret;
}


int choice_3(int door){
	int ret = door/2;
	if(door %2 == 0){
		if(ret %2 == 1)
			return choice_1(door) - 2;
		else
			return choice_1(door) + 2;
	}
	else{
		if(ret % 2 == 0)
			return choice_1(door) - 2;
		else
			return choice_1(door) + 2;
	}		
}


int choice_2(int door){
	int ret = door/2;
	if(door %2 == 0){
		if(ret %2 == 0)
			return choice_1(door) - 2;
		else
			return choice_1(door) + 2;
	}
	else{
		if(ret % 2 == 1)
			return choice_1(door) - 2;
		else
			return choice_1(door) + 2;
	}		
}


int choice_4(int door){
	if(door % 2 == 0)
		return choice_1(door - 1);
	else
		return choice_1(door + 1);
}


int choice_5(int door){
	if(door % 2 == 0)
		return choice_2(door - 1);
	else
		return choice_2(door + 1);
}


int choice_6(int door){
	if(door % 2 == 0)
		return choice_3(door - 1);
	else
		return choice_3(door + 1);
}

void print_choices(){
	int j = 1;
	for(; j < 33; j++){
		int i = 0;
		printf("Door: %i", j);
		for(; i < 6; i ++){
			printf("c%i: %i\t", i+1, choice(j, i));
		}
		printf("\n");
	}
}


	

