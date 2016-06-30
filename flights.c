/* 
 * CS61C Summer 2016
 * Name:
 * Login:
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "flights.h"
#include "timeHM.h"
typedef struct flight flight_t;
 struct flight{
  char * destination_name;
  timeHM_t departure;
  timeHM_t arrival;
  int cost_of_flight;
  flight_t * next_flight;
};
typedef struct airport airport_t;
  struct airport{
    char * airport_name;
    airport_t * next_airport;
    flight_t * start_flight;
   };

struct flightSys{
   airport_t *start_airport;
};
typedef struct flightSys flightSys_t;



/*
   This should be called if memory allocation failed.
 */
static void allocation_failed() {
    fprintf(stderr, "Out of memory.\n");
    exit(EXIT_FAILURE);
}


/*
   Creates and initializes a flight system, which stores the flight schedules of several airports.
   Returns a pointer to the system created.
 */
flightSys_t* createSystem() {
    // Replace this line with your code
  //printf("A\n");
    flightSys_t * new_flight_sys = (flightSys_t *) malloc(sizeof(flightSys_t ));
    if(new_flight_sys == NULL){
      allocation_failed();
    }
    new_flight_sys->start_airport = NULL;
  
    return new_flight_sys;
}


/*
   Frees all memory associated with this system; that's all memory you dynamically allocated in your code.
 */
void deleteSystem(flightSys_t* s) {
    // Replace this line with your code
 /* if(s != NULL){
    while(s->start_airport != NULL){
      airport_t * airport_pointer = s->start_airport;
      //free all the schedules of an airport
      while(airport_pointer->start_flight!= NULL){
        free(airport_pointer->start_flight->destination_name);
        airport_pointer->start_flight->destination_name = NULL;
        flight_t * flight_pointer = airport_pointer->start_flight;
        airport_pointer->start_flight = flight_pointer->next_flight;
        free(flight_pointer);
        flight_pointer = NULL;
      }
      free(airport_pointer->airport_name);
      airport_pointer->airport_name = NULL;
      s->start_airport = airport_pointer->next_airport;
      free(airport_pointer);
    }
    free(s);
    s = NULL;
  }*/

}


/*
   Adds a airport with the given name to the system. You must copy the string and store it.
   Do not store "name" (the pointer) as the contents it point to may change.
 */
void addAirport(flightSys_t* s, char* name) {
    // Replace this line with your code
  //printf("B\n");
if(s!= NULL && name != NULL){
    airport_t * new_airport = (airport_t *) malloc(sizeof(airport_t));
    if(new_airport == NULL){
        allocation_failed();
    }
    //possible segfault?
    new_airport->airport_name = malloc((strlen(name) + 1)* sizeof(char));
    new_airport->start_flight = NULL;
    if(new_airport->airport_name == NULL){
      free(new_airport);
      allocation_failed();
    }
    strcpy(new_airport->airport_name, name);
    airport_t * pointer = s->start_airport;
    new_airport->next_airport = NULL;
    if(pointer == NULL){
      s->start_airport = new_airport;
    }else{
        while(pointer->next_airport != NULL){
        pointer = pointer->next_airport;
      }
      pointer->next_airport = new_airport;

    }
  
  }
}


/*
   Returns a pointer to the airport with the given name.
   If the airport doesn't exist, return NULL.
 */

airport_t* getAirport(flightSys_t* s, char* name) {
    // Replace this line with your code
  //printf("c\n");
    if(s != NULL && name != NULL){
        airport_t * pointer = s->start_airport;
        while(pointer != NULL){
          if(strcmp(pointer->airport_name, name) == 0){
            return pointer;
          }
          pointer = pointer->next_airport;
        }
    }
       // printf("got here fine\n");
    return NULL;
}


/*
   Print each airport name in the order they were added through addAirport, one on each line.
   Make sure to end with a new line. You should compare your output with the correct output
   in flights.out to make sure your formatting is correct.
 */
void printAirports(flightSys_t* s) {
    // Replace this line with your code
  //printf("D\n");
  if(s != NULL){
    airport_t * pointer = s->start_airport;
    while(pointer != NULL){
      printf("%s",pointer->airport_name);
      printf("\n");
      pointer = pointer->next_airport;
    }
  }
  
}


/*
   Adds a flight to src's schedule, stating a flight will leave to dst at departure time and arrive at arrival time.
 */
void addFlight(airport_t* src, airport_t* dst, timeHM_t* departure, timeHM_t* arrival, int cost) {
    // Replace this line with your code

  if (src != NULL) {
      flight_t * new_flight = (flight_t *) malloc(sizeof(flight_t));
      if(new_flight == NULL){
        allocation_failed();
      }
      new_flight->destination_name = malloc(sizeof(dst->airport_name) + 1);
      //new_flight->departure = malloc(sizeof(departure));
      //new_flight->arrival = malloc(sizeof(arrival));
      //new_flight->cost_of_flight = malloc(sizeof(cost));
      strcpy(new_flight->destination_name, dst->airport_name);
      new_flight->departure = * departure;
      new_flight->arrival = * arrival;
      new_flight->cost_of_flight = cost;
      flight_t * pointer = src->start_flight;
      new_flight->next_flight = NULL;
      if (pointer == NULL) {
        src->start_flight = new_flight;
      } else {
        while (pointer->next_flight != NULL) {
          pointer = pointer->next_flight;
      }
      pointer->next_flight = new_flight;
      }
    }
}
/*
   Prints the schedule of flights of the given airport.
   Prints the airport name on the first line, then prints a schedule entry on each 
   line that follows, with the format: "destination_name departure_time arrival_time $cost_of_flight".
   You should use printTime (look in timeHM.h) to print times, and the order should be the same as 
   the order they were added in through addFlight. Make sure to end with a new line.
   You should compare your output with the correct output in flights.out to make sure your formatting is correct.
 */
void printSchedule(airport_t* s) {
    // Replace this line with your code
   if(s != NULL){
    flight_t * pointer = s->start_flight;
    printf("AIRPORT: %s \n",s->airport_name);
    while(pointer != NULL){
      printf("%s ",pointer->destination_name);
      printTime(&pointer->departure);
      printf(" ");
      printTime(&pointer->arrival);
      printf(" ");
      printf("$%d \n",pointer->cost_of_flight);
      pointer = pointer->next_flight;
    }
      
  }

}


/*
   Given a src and dst airport, and the time now, finds the next flight to take based on the following rules:
   1) Finds the cheapest flight from src to dst that departs after now.
   2) If there are multiple cheapest flights, take the one that arrives the earliest.
   If a flight is found, you should store the flight's departure time, arrival time, and cost in departure, arrival, 
   and cost params and return true. Otherwise, return false. 
   Please use the function isAfter() from time.h when comparing two timeHM_t objects.
 */
bool getNextFlight(airport_t* src, airport_t* dst, timeHM_t* now, timeHM_t* departure, timeHM_t* arrival, int* cost) {
    flight_t * pointer = src->start_flight;
    flight_t * best_flight = NULL;
    int result = 0;
    if (src != NULL && dst != NULL) {
      while (pointer != NULL) {
        if (strcmp(pointer->destination_name, dst->airport_name) == 0 && isAfter(&pointer->departure, now)) {
          result = 1;
          if (best_flight == NULL) {
            best_flight = pointer;
          } else if (best_flight->cost_of_flight > pointer->cost_of_flight) {
            best_flight = pointer;
          } else if (best_flight->cost_of_flight == pointer->cost_of_flight) {
            if (isAfter(&best_flight->arrival, &pointer->arrival)) {
             best_flight = pointer;
            }
          }
        }
        pointer = pointer->next_flight;
      }
      if (best_flight != NULL) {
      * departure = (best_flight->departure);
      * arrival = (best_flight->arrival);
      * cost = (best_flight->cost_of_flight);
      }
    }
    return (result == 1);
  }