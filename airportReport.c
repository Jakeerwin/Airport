#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "airport.h"

int main(int argc, char **argv) {

    int r = 5;
    Airport arr[5];
    arr[0] = *createAirport("SfO", "International", "San Francisco International Airport", 37.6213, 122.3790, 13, "San Francisco", "USA");
    arr[1] = *createAirport("JFK", "International", "John F. Kennedy International Airport", 40.6413, 73.7781, 13, "New York", "USA");
    arr[2] = *createAirport("KEV", "large_airport", "Halli Airport", 61.8588, 24.8192, 481, "Kuorevesi", "FIN");
    arr[3] = *createAirport("LNK", "Public", "Lincoln Airport", 40.8507, -96.7581, 1219, "Lincoln", "USA");
    arr[4] = *createAirport("YOR", "Public", "York Airport", 38.93243, -94.27463, 12, "York", "USA");

    generateReports(arr, r);

    return 0;
}