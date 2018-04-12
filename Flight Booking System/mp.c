#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define NUM_CITY 10
#define NUM_FLIGHT 50
#define TRUE 1
#define FALSE 0

struct Flight {
	char code[5];
	char source_city[4];
	char destination_city[4];
	int departure_time;
	int duration;
	int eta;
};

struct City{
	char code[4];
	char name[16];
};

struct Ticket {
	struct Ticket * pNext;
	struct Ticket * pPrev;
	struct Flight flight;
};

int addNewCity(struct City cities[], char code[], char name[], int * index) {
	int isUnique = TRUE;
	int ctr;
	if(strlen(code) <= 3 && strlen(name) <= 15) {
		for(ctr = 0; ctr <= *index; ctr++) {
			if(strcmp(cities[ctr].code,code) == 0)
				isUnique = FALSE;
		} 
		if(isUnique) {
			strcpy(cities[*index].code, code);
			strcpy(cities[*index].name, name);
			*index = *index + 1;	
			return TRUE;
		}
		else
			return FALSE;	
	}
	else
		return FALSE;
}

int deleteCity(struct City cities[], int index, int * size) {
	struct City temp;
	int ctr;
	
	for(ctr = index; ctr < *size; ctr++) {
		temp = cities[ctr+1];
		cities[ctr] = temp;
	}
	*size = *size - 1;
	
	return TRUE;
}

void searchCity(struct City cities[], char code[], int size) {
	int ctr, isFound = FALSE;
	struct City temp;
	
	for(ctr = 0; ctr <= size; ctr++) {
		if(strcmp(cities[ctr].code,code) == 0) {
			temp = cities[ctr];
			isFound = TRUE;
		}
	}
	if(isFound) {
		printf("%s\n",temp.code);
		printf("%s\n",temp.name);
		printf("Press any key to continue... ");
		getch();
	}
	else {
		printf("No results found!\n");
		printf("Press any key to continue... ");
		getch();
	}
}

int cityExist(struct City cities[], char code[], int size) {
	int ctr;
	int isExist = FALSE;
	
	for(ctr = 0; ctr <= size; ctr++) {
		if(strcmp(cities[ctr].code,code) == 0)
			isExist = TRUE;
	}
	return isExist;
}

int getETA(int departure, int duration) {
	int hours, minutes;
	
	hours = departure / 100;
	minutes = departure % 100;
	minutes += duration;
	while(minutes >= 60) {
		minutes -= 60;
		hours++;
	}
	if(hours >= 24)
		hours -= 24;
	hours *= 100;
	return hours + minutes;
}

int addNewFlight(struct Flight flights[], struct City cities[], char code[], char source_city[], char destination_city[], int departure_time, int duration, int * index_flight, int * index_city) {
	int isUnique = TRUE;
	int isCorrect = TRUE;
	int isExist = TRUE;
	int errorCodeNotUnique = 2;
	int errorCityNotExist = 3;
	int errorInvalidLength = 4;
	int errorInvalidCode = 5;
	int ctr;
	
	if(strlen(code) <= 4 && strlen(source_city) <= 3 && strlen(destination_city) <= 4) {
		for(ctr = 0; ctr < *index_flight; ctr++) {
			if(strcmp(flights[ctr].code,code) == 0)
				isUnique = FALSE;
		}
		if (isUnique) {
			if(cityExist(cities,source_city,*index_city) && cityExist(cities,destination_city,*index_city)) {
				if((code[0] >= 97 && code[0] <= 122 || code[0] >= 65 && code[0] <= 90) && (code[1] >= 97 && code[1] <= 122 || code[1] >= 65 && code[1] <= 90) && (code[2] >= 48 && code[2] <= 57) && (code[3] >= 48 && code[3] <= 57)) {
					strcpy(flights[*index_flight].code,code);
					strcpy(flights[*index_flight].source_city,source_city);
					strcpy(flights[*index_flight].destination_city,destination_city);
					flights[*index_flight].departure_time = departure_time;
					flights[*index_flight].duration = duration;
					flights[*index_flight].eta = getETA(departure_time, duration);
					*index_flight = *index_flight + 1;
					return TRUE;		   	
				}
				else
					return errorInvalidCode;
			}
			else
				return errorCityNotExist;	
		}
		else
			return errorCodeNotUnique;
	}
	else
		return errorInvalidLength;
	
}

void searchFlightByCity(struct Flight flights[], char city[], int size) {
	int count = 0, ctr, temp = 0, isFound = FALSE;

	for(ctr = 0; ctr < size; ctr++) {
		if(strcmp(flights[ctr].destination_city,city) == 0) {
			isFound = TRUE;
			printf("Code: %s\n", flights[ctr].code);
			printf("Source City: %s\n", flights[ctr].source_city);
			printf("Destination City: %s\n", flights[ctr].destination_city);
			printf("Departure Time: %d\n", flights[ctr].departure_time);
			printf("Duration: %d\n", flights[ctr].duration);
			printf("ETA: %d\n", flights[ctr].eta);
			printf("----------------------------------\n");
		}
	}
	if(!isFound) {
		printf("No results found!\n");
	}
	printf("Press any key to continue... ");
	getch();
}

void searchFlightByCode(struct Flight flights[], char code[], int size) {
	int count = 0, ctr, temp = 0, isFound = FALSE;

	for(ctr = 0; ctr < size; ctr++) {
		if(strcmp(flights[ctr].code,code) == 0) {
			isFound = TRUE;
			printf("Code: %s\n", flights[ctr].code);
			printf("Source City: %s\n", flights[ctr].source_city);
			printf("Destination City: %s\n", flights[ctr].destination_city);
			printf("Departure Time: %d\n", flights[ctr].departure_time);
			printf("Duration: %d\n", flights[ctr].duration);
			printf("ETA: %d\n", flights[ctr].eta);
			printf("----------------------------------\n");
		}
	}
	if(!isFound) {
		printf("No results found!\n");
	}
	printf("Press any key to continue... ");
	getch();
}

void searchFlightByDeparture(struct Flight flights[], int departure, int size) {
	int count = 0, ctr, temp = 0, isFound = FALSE;

	for(ctr = 0; ctr < size; ctr++) {
		if(flights[ctr].departure_time == departure) {
			isFound = TRUE;
			printf("Code: %s\n", flights[ctr].code);
			printf("Source City: %s\n", flights[ctr].source_city);
			printf("Destination City: %s\n", flights[ctr].destination_city);
			printf("Departure Time: %d\n", flights[ctr].departure_time);
			printf("Duration: %d\n", flights[ctr].duration);
			printf("ETA: %d\n", flights[ctr].eta);
			printf("----------------------------------\n");
		}
	}
	if(!isFound) {
		printf("No results found!\n");
	}
	printf("Press any key to continue... ");
	getch();
}

int deleteFlight(struct Flight flights[], int index, int * size) {
	struct Flight temp;
	int ctr;
	
	for(ctr = index; ctr < *size; ctr++) {
		temp = flights[ctr+1];
		flights[ctr] = temp;
	}
	*size = *size - 1;
	
	return TRUE;
}

void saveCities(struct City cities[], int size) {
	int ctr;
	FILE *fptr;
	fptr = fopen("cities.txt","w");
	
	system("cls");
	printf("Cities will be saved on cities.txt\n");
	for(ctr = 0; ctr < size; ctr++) {
		fprintf(fptr,"%s %s\n",cities[ctr].code,cities[ctr].name);
	}
	fclose(fptr);
	printf("Press any key to continue... ");
	getch();
}

void saveFlights(struct Flight flights[], int size) {
	int ctr;
	FILE *fptr;
	fptr = fopen("flights.txt","w");
	
	system("cls");
	printf("Flights will be saved on flights.txt\n");
	for(ctr = 0; ctr < size; ctr++) {
		fprintf(fptr,"FCODE=%s\n",flights[ctr].code);
		fprintf(fptr,"SRCCITY=%s\n",flights[ctr].source_city);
		fprintf(fptr,"DESTCITY=%s\n",flights[ctr].destination_city);
		fprintf(fptr,"DEPARTURE=%d\n",flights[ctr].departure_time);
		fprintf(fptr,"DURATION=%d\n",flights[ctr].duration);
	}
	fclose(fptr);
	printf("Press any key to continue... ");
	getch();
}

void loadCities(struct City cities[], int * size) {
	FILE *fptr;
	char filename[20];
	char code[4];
	char name[16];
	
	printf("Enter filename: ");
	scanf("%s",filename);

	if((fptr = fopen(filename,"r")) == NULL) {
		printf("Error in opening file!\n");
		printf("Press any key to continue... ");
		getch();
	}
	else {
		while(!feof(fptr)) {
			fscanf(fptr,"%s %[^\n]s",code,name);
			addNewCity(cities,code,name,size);
		}
		printf("Load success!\n");
		printf("Press any key to continue... ");
		getch();
	}
}

void loadFlights(struct Flight flights[], struct City cities[], int * size, int * cSize) {
	FILE *fptr;
	char filename[20];
	char tempCode[10], code[4];
	char tempSrc[12], src[4];
	char tempDest[13], dest[4];
	char tempDeparture[15];
	char tempDuration[18];
	int departure, duration;
	
	printf("Enter filename: ");
	scanf("%s",filename);

	if((fptr = fopen(filename,"r")) == NULL) {
		printf("Error in opening file!\n");
		printf("Press any key to continue... ");
		getch();
	}
	else {
		while(!feof(fptr)) {
			fscanf(fptr,"%s",tempCode);
			fscanf(fptr,"%s",tempSrc);
			fscanf(fptr,"%s",tempDest);
			fscanf(fptr,"%s",tempDeparture);
			fscanf(fptr,"%s",tempDuration);
			strcpy(code,(tempCode+6));
			strcpy(src,(tempSrc+8));
			strcpy(dest,(tempDest+9));
			departure = atoi(tempDeparture+10);
			duration = atoi(tempDuration+9);
			addNewFlight(flights,cities,code,src,dest,departure,duration,size,cSize);
		}
		printf("Load success!\n");
		printf("Press any key to continue... ");
		getch();
	}
}

void sortFlightAlphabetical(struct Flight flights[], int size) {
	struct Flight temp;
	int c, d;
	
	for (c = 0 ; c < size; c++) {
	    for (d = c+1; d < size; d++) {
	    	if (strcmp(flights[c].code,flights[d].code) > 0){
		        temp = flights[c];
		        flights[c] = flights[d];
		        flights[d] = temp;
	    	}
	    }
	}
}

void sortFlightETA(struct Flight flights[], int size) {
	struct Flight temp;
	int c, d;
	
	for (c = 0 ; c < size; c++) {
	    for (d = c+1; d < size; d++) {
	    	if (flights[c].eta > flights[d].eta){
		        temp = flights[c];
		        flights[c] = flights[d];
		        flights[d] = temp;
	    	}
	    }
	}
}

void sortFlightDeparture(struct Flight flights[], int size) {
	struct Flight temp;
	int c, d;
	
	for (c = 0 ; c < size; c++) {
	    for (d = c+1; d < size; d++) {
	    	if (flights[c].departure_time > flights[d].departure_time){
		        temp = flights[c];
		        flights[c] = flights[d];
		        flights[d] = temp;
	    	}
	    }
	}
}

void sortFlightDuration(struct Flight flights[], int size) {
	struct Flight temp;
	int c, d;
	
	for (c = 0 ; c < size; c++) {
	    for (d = c+1; d < size; d++) {
	    	if (flights[c].duration > flights[d].duration){
		        temp = flights[c];
		        flights[c] = flights[d];
		        flights[d] = temp;
	    	}
	    }
	}
}

void sortCityAlphabetical(struct City cities[], int size) {
	struct City temp;
	int c, d;
	
	for (c = 0 ; c < size; c++) {
	    for (d = c+1; d < size; d++) {
	    	if (strcmp(cities[c].code,cities[d].code) > 0){
		        temp = cities[c];
		        cities[c] = cities[d];
		        cities[d] = temp;
	    	}
	    }
	}
}

void viewCities(struct City cities[], int * size) {
	int ctr = 0;
	char option, nOption;
	char code[4];
	
	if(*size != 0) {

		while(option != 'q') {
			printf("[0]delete entry\n");
			printf("[1]sort alphabetical\n");
			printf("[2]search\n");
			printf("[a]Previous [d]Next [q]quit\n\n\n");
			printf("Code: %s\n", cities[ctr].code);
			printf("Name: %s\n", cities[ctr].name);
			printf("----------------------------\n");
			
			option = getch();
			if(option == 'a') {
				if(ctr > 0)
					ctr--;
			}
			else if(option == 'd') {
				if(ctr != *size-1)
					ctr++;
			}
			else if(option == '0') {
				printf("Are you sure you want to delete %s?\n", cities[ctr].code);
				printf("[y]es, [n]o\n");
				nOption = getch();
				if(nOption == 'y') {
					deleteCity(cities, ctr, size);
					ctr = 0;
				}
			}
			else if(option == '1') {
				sortCityAlphabetical(cities,*size);
				ctr = 0;
			}
			else if(option == '2') {
				system("cls");
				printf("Enter city code: ");
				scanf("%s",code);
				searchCity(cities,code,*size);
			}
			system("cls");
		}
	}
	else
		printf("No entries available!\n");
	printf("Press any key to continue... ");
	getch();
}

void viewFlights(struct Flight flights[], int * size) {
	int ctr = 0;
	char option, nOption;
	char code[4];
	char city[4];
	int departure;
	
	if(*size != 0) {
		while(option != 'q') {
			printf("[0]delete entry\n");
			printf("Sort: [1]alphabetical, [2]by duration, [3]by ETA, [4]departure time\n");
			printf("Search: [5]flight code, [6]departure city, [7]departure time\n");
			printf("[a]Previous [d]Next [q]quit\n\n\n");
			printf("Code: %s\n", flights[ctr].code);
			printf("Source City: %s\n", flights[ctr].source_city);
			printf("Destination City: %s\n", flights[ctr].destination_city);
			printf("Departure Time: %d\n", flights[ctr].departure_time);
			printf("Duration: %d\n", flights[ctr].duration);
			printf("ETA: %d\n", flights[ctr].eta);
			printf("----------------------------\n");	
			option = getch();
			if(option == 'a') {
				if(ctr > 0)
					ctr--;
			}
			else if(option == 'd') {
				if(ctr != *size-1)
					ctr++;
			}
			else if(option == '0') {
				printf("Are you sure you want to delete %s?\n", flights[ctr].code);
				printf("[y]es, [n]o\n");
				nOption = getch();
				if(nOption == 'y') {
					deleteFlight(flights, ctr, size);
					ctr = 0;
				}
			}
			else if(option == '1') {
				sortFlightAlphabetical(flights,*size);
				ctr = 0;
			}
			else if(option == '2') {
				sortFlightDuration(flights,*size);
				ctr = 0;
			}
			else if(option == '3') {
				sortFlightDeparture(flights,*size);
				ctr = 0;
			}
			else if(option == '4') {
				sortFlightETA(flights,*size);
				ctr = 0;
			}
			else if(option == '5') {
				system("cls");
				printf("Enter flight code: ");
				scanf("%s",code);
				searchFlightByCode(flights,code,*size);
			}
			else if(option == '6') {
				system("cls");
				printf("Enter departure city code: ");
				scanf("%s",city);
				searchFlightByCity(flights,city,*size);
			}
			else if(option == '7') {
				system("cls");
				printf("Enter departure time: ");
				scanf("%d", &departure);
				searchFlightByDeparture(flights,departure,*size);
			}
			system("cls");
		}
	}
	else
		printf("No entries available!\n");
	printf("Press any key to continue... ");
	getch();
}

void booking(struct City cities[], struct Flight flights[], int index_city, int index_flight) {
	FILE *fptr;
	struct Ticket temp;
	struct Ticket * current;
	struct Ticket * first;
	struct Ticket * last;
	struct Ticket * ftemp;
	struct Flight tFlight;
	char input[4];
	char option;
	int x, ctrFlight = 0, ctrTicket = 0;
	int tSize = 0;
	int is_add = FALSE;
	
	first = malloc(sizeof(struct Ticket));
	current = first;
	last = first;
	(*current).pNext = NULL;
	(*current).pPrev = NULL;
	
	while(option != 'x') {
		system("cls");
		current = first;
		//display tickets
		printf("[z]save to file, [x]exit\n");
		printf("[q]previous ticket, [w]next ticket, [e]delete ticket\n");
		if(tSize == 0)
			printf("No tickets yet \n");
		else {
			for(x = 0; x < tSize; x++) {
				current = (*current).pNext;
				if(x == ctrTicket)
					temp = *current;
			}
			printf("Code: %s\n", temp.flight.code);
			printf("Source City: %s\n", temp.flight.source_city);
			printf("Destination City: %s\n", temp.flight.destination_city);
			printf("Departure Time: %d\n", temp.flight.departure_time);
			printf("Duration: %d\n", temp.flight.duration);
			printf("ETA: %d\n", temp.flight.eta);
		}
		
		//display flights
		printf("\n[a]previous flight, [s]next flight, [b]book flight\n");
		if(index_flight != 0) {
			printf("Code: %s\n", flights[ctrFlight].code);
			printf("Source City: %s\n", flights[ctrFlight].source_city);
			printf("Destination City: %s\n", flights[ctrFlight].destination_city);
			printf("Departure Time: %d\n", flights[ctrFlight].departure_time);
			printf("Duration: %d\n", flights[ctrFlight].duration);
			printf("ETA: %d\n", flights[ctrFlight].eta);
		}
		else
			printf("No flights!\n");
		
		option = getch();
		
		if(option == 'q') { //previous ticket
			if(ctrTicket - 1 < 0)
				ctrTicket = 0;
			else
				ctrTicket--;
		}
		if(option == 'w') { //next ticket
			if(!(ctrTicket + 1 >= tSize))
				ctrTicket++;
		}
		if(option == 'e') { //delete ticket
			if(current != first) {
				(*(*current).pPrev).pNext = (*current).pNext;
				if((*current).pNext != NULL)
					(*(*current).pNext).pPrev = (*current).pPrev;
				if(current == last)
					last = (*current).pPrev;
				printf("passed");
				free(current);
				tSize--;
				ctrTicket = 0;
			}
		}
		if(option == 'a') { //previous flight
			if(ctrFlight - 1 < 0)
				ctrFlight = 0;
			else
				ctrFlight--;
		}
		if(option == 's') { //next flight
			if(!(ctrFlight + 1 >= index_flight))
				ctrFlight++;
		}
		if(option == 'b') { //book flight
			is_add = FALSE;
			if((*last).pPrev != NULL) {
				
				if(flights[ctrFlight].departure_time - (*last).flight.eta >= 15) {
					is_add = TRUE;
					if(strcmp(flights[ctrFlight].source_city,(*last).flight.destination_city) == 0)
						is_add = TRUE;
					else {
						is_add = FALSE;
						printf("Unsuccessfully booked %s\n", flights[ctrFlight].code);
						printf("Error: Invalid source city\n");
						printf("Press any key to continue... ");
						getch();
					}
				}
				else {
					printf("Unsuccessfully booked %s\n", flights[ctrFlight].code);
					printf("Error: Interval not equal or greater than 15mins\n");
					printf("Press any key to continue... ");
					getch();
				}
				
					
			}
			else
				is_add = TRUE;
			if(is_add) {
				tSize++;
				(*last).pNext = malloc(sizeof(struct Ticket));
				last = (*last).pNext;
				(*last).pPrev = current;
				current = last;
				(*current).pNext = NULL;
				strcpy((*current).flight.code,flights[ctrFlight].code);
				strcpy((*current).flight.destination_city,flights[ctrFlight].destination_city);
				strcpy((*current).flight.source_city,flights[ctrFlight].source_city);
				(*current).flight.departure_time = flights[ctrFlight].departure_time;
				(*current).flight.duration = flights[ctrFlight].duration;
				(*current).flight.eta = flights[ctrFlight].eta;
				printf("Successfully booked %s\n", flights[ctrFlight].code);
				printf("Press any key to continue... ");
				getch();
			}
		}
		if(option == 'z'){ //save to file
			fptr = fopen("tickets.txt","w");
			current = first;
			
			fprintf(fptr, "CODE ETDEPART SOURCE DESTIN ETARRIVAL DURATION flight\n");
			for(x = 0; x < tSize; x++) {
				current = (*current).pNext;
				fprintf(fptr, "%s %d %s %s %d %d\n", (*current).flight.code,(*current).flight.departure_time,(*current).flight.source_city,
													(*current).flight.destination_city,(*current).flight.eta,(*current).flight.duration);
			}
			
			fclose(fptr);
			printf("Tickets saved to tickets.txt\n");
			printf("Press any key to continue... ");
			getch();
		}
	}
	
	//free linked list
	current = last;
	while(current != NULL) {
		ftemp = current;
		current = (*current).pPrev;
		free(ftemp);
	}
}

void mainMenu() {
	struct City cities[NUM_CITY];
	struct Flight flights[NUM_FLIGHT];
	char code[4], name[16];
	char src[4], dest[4];
	int departure, duration;
	int index_city = 0;
	int index_flight = 0;
	int x, ctr, option;
	int *temp;
	
	while(TRUE) {
		option = 999;
		system("cls");
		while(option != 0 && option != 1) {
			printf("[0]Data Module\n");
			printf("[1]Booking Module\n");
			scanf("%d",&option);
			system("cls");
		}
		
		if(option == 0) {
			printf("Enter initial Cities? [0]No [1]Yes ");
			scanf("%d", &option);
			if(option == 1) {
				loadCities(cities,&index_city);
				system("cls");
			}
			printf("Enter initial Flights? [0]No [1]Yes ");
			scanf("%d", &option);
			if(option == 1) {
				loadFlights(flights,cities,&index_flight,&index_city);
				system("cls");
			}
			system("cls");
			while(option != 6) {
				printf("[0]Add New Flight\n");
				printf("[1]Add New City\n");
				printf("[2]View Flights\n");
				printf("[3]View Cities\n");
				printf("[4]Save Flights\n");
				printf("[5]Save Cities\n");
				printf("[6]Exit\n");
		
				fflush(stdin);
				scanf("%d", &option);
				fflush(stdin);
				system("cls");
				if(option >= 0 && option <= 6) {
					switch(option) {
						case 0 : printf("Enter code: ");
								 scanf("%s",code);
								 printf("Source city: ");
								 scanf("%s",src);
								 printf("Destination city: ");
								 scanf("%s",dest);
								 printf("Departure time: ");
								 scanf("%d",&departure);
								 printf("Duration: ");
								 scanf("%d",&duration);
								 switch(addNewFlight(flights,cities,code,src,dest,departure,duration,&index_flight,&index_city)) {
								 	case 0 : printf("Error!\n");
								 			 break;
									case 1 : printf("Success!\n");
											 break;
									case 2 : printf("Error! Code not unique!\n");
											 break;
									case 3 : printf("Error! City does not exist!\n");
											 break;
									case 4 : printf("Error! Invalid Length!\n");
											 break;
									case 5 : printf("Error! Invalid Code!\n");
											 break;
								 }
								 printf("Press any key to continue... ");
								 getch();
								 break;
						case 1 : printf("Enter code: ");
								 scanf("%s",code);
								 printf("Enter name: ");
								 scanf("%s",name);
								 if(addNewCity(cities,code,name,&index_city)) {
								 	printf("Success!\n");
								 	printf("Press any key to continue... ");
								 	getch();
								 }
								 else {
								 	printf("Error!\n");
								 	printf("Press any key to continue... ");
								 	getch();
								 }
								 break;
						case 2 : viewFlights(flights, &index_flight);
								 break;
						case 3 : viewCities(cities, &index_city);
								 break;
						case 4 : saveFlights(flights,index_flight);
								 break;
						case 5 : saveCities(cities,index_city);
								 break;
						case 6 : //exit(0);
								 break;
					}
				}
				else {
					printf("Invalid Input!\n");
					printf("Press any key to continue... ");
					getch();
				}
				system("cls");	
			}
		}
		else {
			booking(cities,flights,index_city,index_flight);
			printf("end of booking");
		}
	}
}

int main() {
	struct City cities[NUM_CITY];
	struct Flight flights[NUM_FLIGHT];
	int index_city = 0;
	int index_flight = 0;
	int x, ctr, option;
	int *temp;
	
	
	mainMenu();
	
	return 0;
}
















