#include <stdio.h>
#include "genlib.h"
#include "simpio.h"
#include <string.h>

#define RENTS 20

typedef struct{

    int number;
    char type[20];
    int cc;
    char name[20];
    int days;
    float daily_rate;
    float total_charge;
} car_rentalT;

typedef struct {

    char type[20];
    int cc;
    float amount;
} best_carT;


int getData(car_rentalT rentals[]);
float calculateTotals(int numRentals, car_rentalT rentals[]);
best_carT findBest(int numRentals, car_rentalT rentals[]);
void printData(int numRentals, car_rentalT rentals[], float total, best_carT best);

int main(){

    car_rentalT rentals[RENTS];
    best_carT bestCar;
    int numRentals;
    float total;

    //We call the functions we created

    numRentals = getData(rentals);
    total = calculateTotals(numRentals, rentals);
    bestCar = findBest(numRentals, rentals);
    printData(numRentals, rentals, total, bestCar);

    return 0;
}

int getData(car_rentalT rentals[]){

    int i, numRentals;
    // User input for total number of rentals
    printf("Give the total number of rentals: \n");
    numRentals = GetInteger();

    for(i=0; i<numRentals;i++){

        // User input about details regarding the rentals
        printf("Give the rental data %d\n", i);
        rentals[i].number = i;

        printf("Brand: ");
        gets(rentals[i].type);

        printf("CC: ");
        rentals[i].cc = GetInteger();

        printf("Customer name: ");
        gets(rentals[i].name);

        printf("Number of days: ");
        rentals[i].days = GetInteger();

        printf("Price per day: ");
        rentals[i].daily_rate = GetReal();
    }

    return numRentals;
}

float calculateTotals(int numRentals, car_rentalT rentals[]){

    int i;
    float total = 0;

    // Total price calculator based on the user input
    for(i=0;i<numRentals;i++){

        rentals[i].total_charge = rentals[i].days * rentals[i].daily_rate;
        total += rentals[i].total_charge;
    }
    return total;
}

best_carT findBest(int numRentals, car_rentalT rentals[]){

    int i;
    best_carT best;

    strcpy(best.type, rentals[0].type);
    best.cc = rentals[0].cc;
    best.amount = rentals[0].total_charge;


    // We calculate what the best car is based on total price and the user input
    for(i=0;i<numRentals;i++){
        if(best.amount < rentals[i].total_charge){
            strcpy(best.type, rentals[i].type);
            best.cc = rentals[i].cc;
            best.amount = rentals[i].total_charge;
        }
    }

    return best;
}

void printData(int numRentals, car_rentalT rentals[], float total, best_carT best){

    int i;
    // Print the data we have
    printf("\n\n");
    printf(" %-7s %-20s %-10S %-5s %-5s %-6s %-8s\n", "Number", "Name", "Type", "CC", "Days", "Price", "Total");

    for(i=0;i<73;i++){
        printf("-");
    }
    printf("\n");

    for(i=0;i<numRentals;i++){
        printf(" %-7d %-20s %-10s %-5d %-5d %-6.2f %-8.2f\n",
               rentals[i].number,
               rentals[i].name,
               rentals[i].type,
               rentals[i].cc,
               rentals[i].days,
               rentals[i].daily_rate,
               rentals[i].total_charge );
    }
    for(i=0;i<73;i++){
        printf("-");
    }
    printf("\n");

    printf("%58s %-8.2f\n", "Total", total);
    printf("Best car: %s %d rented for %.2f Euros. \n", best.type, best.cc, best.amount );

}
