
//Returns true if the truck destination, all freight destinations and the head and tail loads are the same.
int truck_cmp(truck_info * t1, truck_info * t2){
	if(strcmp(t1->dest, t2->dest))
		return 0;
	destination * d1 = t1->destinations;
	destination * d2 = t2->destinations;
	while(d1 != NULL && d2 != NULL){
		if(strcmp(d1->dest, d2->dest))
			return 0;
		d1 = d1->next;
		d2 = d2->next;
	}
	if(d1 != NULL || d2 != NULL)
		return 0;
	if(t1->head != t2->head || t1->tail != t2->tail)
		return 0;

	return 1;
}


//Combines dock numbers of compared trucks that are the same, onto a single truck object to eliminate duplacate information
void check_identical_trucks(){
	int i = 0;
	for(; i < num_trucks; i++){
		int j = i + 1;
		for(; j < num_trucks; j++){	
			if(truck_cmp(trucks + i, trucks + j)){
				add_door(trucks + i, (trucks + j)->doors->door);
				destroy_truck(trucks + j);
				num_trucks--;
				memcpy(trucks + j, trucks + num_trucks, sizeof(truck_info));
				j--;
}	}	}	}
		
		
int num_destinations(truck_info * truck){
	destination * dest = truck->destinations;
	int count = 0;
	while(dest != NULL){
		dest = dest->next;
		count++;	
	}	
	return count;
}	

int destinations_cmp(const void * t1, const void * t2){
	truck_info * truck1 = (truck_info *)t1;
	truck_info * truck2 = (truck_info *)t2;
	int count1 = num_destinations(truck1);
	int count2 = num_destinations(truck2);
	if(count1 == 1 && !strcmp(truck1->dest, truck1->destinations->dest))
		count1 = 0;
	if(count2 == 1 && !strcmp(truck2->dest, truck2->destinations->dest))
		count2 = 0;
	if(count1 == count2){
		int alph = strcmp(((truck_info*)t1)->dest, ((truck_info*)t2)->dest);
		if(alph > 0) 
			return 1;
		return 0;
	}
	return count1 < count2;
}


int handling_units_cmp(const void * truck1, const void * truck2){
	truck_info * t1 = (truck_info *)truck1;
	truck_info * t2 = (truck_info *)truck2;
	int count1 = t1->handling_units;
	int count2 = t2->handling_units;
	if(t1->docked) 
		count1 -= 24;
	if(t2->docked)
		count2 -= 24;
	return count1 < count2;	
}
		
		
void len_sort(){
	sort(&destinations_cmp);
}
		
		
void handling_units_sort(){
	sort(&handling_units_cmp);
}
		
		
void sort(int (*cmp)(const void*, const void *)){
	qsort(trucks, num_trucks, sizeof(truck_info), cmp);
}
		
		
		
		
		
		
		
