#include <stdio.h>
#include <string.h>
//#include <conio.h>

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

int searchCity(struct City cities[], char code[], int size) {
	int ctr;
	
	for(ctr = 0; ctr <= size; ctr++) {
		if(strcmp(cities[ctr].code,code) == 0)
			return ctr;
	}
	
	return 999;
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

int * searchFlightByCity(struct Flight flights[], char city[], int size) {
	int count, ctr, temp = 0;

	for(ctr = 0; ctr < size; ctr++) {
		if(strcmp(flights[ctr].source_city,city) == 0 || strcmp(flights[ctr].destination_city,city) == 0)
			count++;
	}
	int results[count];
	for(ctr = 0; ctr < size; ctr++) {
		if(strcmp(flights[ctr].source_city,city) == 0 || strcmp(flights[ctr].destination_city,city) == 0) {
			results[temp] = ctr;
			temp++;
		}
	}
	return results;
}

int * searchFlightByCode(struct Flight flights[], char code[], int size) {
	int count, ctr, temp = 0;

	for(ctr = 0; ctr < size; ctr++) {
		if(strcmp(flights[ctr].code,code) == 0)
			count++;
	}
	int results[count];
	for(ctr = 0; ctr < size; ctr++) {
		if(strcmp(flights[ctr].code,code) == 0) {
			results[temp] = ctr;
			temp++;
		}
	}
	printf("Actual size: %d\n",count);
	return results;
}

int * searchFlightByDeparture(struct Flight flights[], int departure, int size) {
	int count, ctr, temp = 0;

	for(ctr = 0; ctr < size; ctr++) {
		if(flights[ctr].departure_time == departure)
			count++;
	}
	int results[count];
	for(ctr = 0; ctr < size; ctr++) {
		if(flights[ctr].departure_time == departure) {
			results[temp] = ctr;
			temp++;
		}
	}
	return results;
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

void saveCities(struct City cities) {
	
}

void saveFlights(struct Flight flights) {
	
}

int loadCities(struct City * cities) {
	
	return TRUE;
}

int loadFlights(struct Flight * flights) {
	
	return TRUE;
}

void mainMenu() {
	printf("Press any key to continue... ");
}

int main() {
	struct City cities[NUM_CITY];
	struct Flight flights[NUM_FLIGHT];
	int index_city = 0;
	int index_flight = 0;
	int x, ctr;
	int *temp;
	addNewCity(cities,"MNL","Manila",&index_city);
	addNewCity(cities,"LPC","Las Piñas",&index_city);
	addNewCity(cities,"PNQ","Parañaque",&index_city);
	addNewFlight(flights,cities,"XX99","MNL","LPC",1200,50,&index_flight,&index_city);
	printf("%d\n", searchCity(cities,"MNL",index_city));
	for(ctr = 0; ctr < index_city; ctr++) {
		printf("%s\n", cities[ctr].code);
	}
	printf("%s\n", flights[0].code);
	printf("hello\n");
	temp = searchFlightByCode(flights,"XX99",index_flight);
	printf("%d\n",sizeof(temp)/sizeof(temp[0]));
	printf("%d\n",sizeof(temp)/sizeof(temp[0]));

	
	return 0;
}
















