#include "python2.7/Python.h"

int main(int argc, char * argv[])
{
	char * filename = malloc(500);
	//strcpy(filename, "/usr/bin/python /home/jozsef/UIUC/NotSvn/DaytonProject/PYcode/draw_dock.py");
		strcpy(filename, "/usr/bin/python /home/jozsef/UIUC/NotSvn/DaytonProject/PYcode/draw_load_plan.py");

	int i = 1;
	for(; i< argc; i++){
		strcat(filename, " ");
		strcat(filename, argv[i]);
	}

	FILE* in = popen(filename, "r");
   	 
    if(in == NULL)
    	printf("Failed\n");
    pclose(in);
    return 0;
 }
