#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "airport.h"

Airport* createAirport(const char* gpsId,
                       const char* type,
                       const char* name,
                       double latitude,
                       double longitude,
                       int elevationFeet,
                       const char* city,
                       const char* countryAbbrv) {
           if(gpsId == NULL || type == NULL || name == NULL || city == NULL || countryAbbrv == NULL) {
            return NULL;
           }

        Airport *a = (Airport *) malloc(sizeof(Airport) * 1);
        initAirport(a, gpsId, type, name, latitude, longitude, elevationFeet, city, countryAbbrv);
        return a;
                       }

void initAirport(Airport* airport,
                 const char* gpsId,
                 const char* type,
                 const char* name,
                 double latitude,
                 double longitude,
                 int elevationFeet,
                 const char* city,
                 const char* countryAbbrv) {


        airport->gpsId = (char *) malloc(sizeof(char) * strlen(gpsId) + 1);
        strcpy(airport->gpsId, gpsId);
        airport->type = (char *) malloc(sizeof(char) * strlen(type) + 1);
        strcpy(airport->type, type);
        airport->name = (char *) malloc(sizeof(char) * strlen(name) + 1);
        strcpy(airport->name, name);
        airport->latitude = latitude;
        airport->longitude = longitude;
        airport->elevationFeet = elevationFeet;
        airport->city = (char *) malloc(sizeof(char) * strlen(city) + 1);
        strcpy(airport->city, city);
        airport->countryAbbrv = (char *) malloc(sizeof(char) * strlen(countryAbbrv) + 1);
        strcpy(airport->countryAbbrv, countryAbbrv);
        if(longitude > 180 || longitude < 180 || latitude > 90 || latitude < -90) {
            return;
        }
        return;
                 }
char* airportToString(const Airport* a) {

    if( a == NULL) {
        char *result = (char *) malloc(sizeof(char) * 7);
        strcpy(result, "(null)");
        return result;
    }

    char buffer[1000];
    sprintf(buffer, "%s, %s, %s, %.2f %.2f, %d, %s, %s", a->gpsId, a->type, a->name, a->latitude, a->longitude, a->elevationFeet, a->city, a->countryAbbrv);
    char *result = (char *) malloc( (strlen(buffer) + 1) *sizeof(char));
    strcpy(result, buffer);
    return result;
}

double getAirDistance(const Airport* origin, const Airport* destination) {
    int earthRadius = 6371;
    double orLatInRad = ((origin->latitude) / 180) * M_PI;
    double orLongInRad = ((origin->longitude) / 180) * M_PI;
    double destLatInRad = ((destination->latitude) / 180) * M_PI;
    double destLongInRad = ((destination->longitude) / 180) * M_PI;
    double longDiff = (destLongInRad - orLongInRad);
    double result = (acos(((sin(orLatInRad)) * sin(destLatInRad)) + (cos(orLatInRad) * cos(destLatInRad) * cos(longDiff))) * earthRadius);

    return result;
}

double getEstimatedTravelTime(const Airport* stops,
                              int size,
                              double aveKmsPerHour,
                              double aveLayoverTimeHrs) {

        if(stops == NULL) {
            return 2;
    }
    double total = 0;

        for(int i = 0; i < size - 1; i++) {
            total += getAirDistance(&stops[i ], &stops[i-1]);
        }
    double travelTime = total / aveKmsPerHour;
    double totalTime = (double) travelTime + (aveLayoverTimeHrs * (size - 1.0));

    return totalTime;

}

int cmpByGPSId(const void* a, const void* b) {
    const Airport *x = (const Airport *)a;
    const Airport *y = (const Airport *)b;

    int r = strcmp(x->gpsId, y->gpsId);
    return r;

}

int cmpByType(const void* a, const void* b) {
    const Airport *x = (const Airport *)a;
    const Airport *y = (const Airport *)b;

    int r = strcmp(x->type, y->type);
    return r;
}

int cmpByName(const void* a, const void* b) {
    const Airport *x = (const Airport *)a;
    const Airport *y = (const Airport *)b;

    int r = strcmp(x->name, y->name);
    return r;
}

int cmpByNameDesc(const void* a, const void* b) {
    return cmpByName(b, a);
}


int cmpByCountryCity(const void* a, const void* b) {
    const Airport *x = (const Airport *)a;
    const Airport *y = (const Airport *)b;

    int r = strcmp(x->countryAbbrv, y->countryAbbrv);
    if(r == 0) {
        return strcmp(x->city, y->city);
    } else {
        return r;
    }
}


int cmpByLatitude(const void* a, const void* b) {
    const Airport *x = (const Airport *)a;
    const Airport *y = (const Airport *)b;
    if(x->latitude < y->latitude) {
        return 1;
    } else if(x->latitude > y->latitude) {
        return -1;
    } else {
        return 0;
    }
}


int cmpByLongitude(const void* a, const void* b) {
    const Airport *x = (const Airport *)a;
    const Airport *y = (const Airport *)b;
    if(x->longitude < y->longitude) {
        return -1;
    } else if(x->longitude > y->longitude) {
        return 1;
    } else {
        return 0;
    }
}


int cmpByLincolnDistance(const void* a, const void* b) {
    const Airport *x = (const Airport *)a;
    const Airport *y = (const Airport *)b;

    Airport *c = createAirport("0R2", "Local", "York", 40.8507, -96.7581, 1245, "Lincoln", "USA");

    double fort = getAirDistance(x, c);
    double nite = getAirDistance(y, c);
    if(fort > nite) {
        return 1;
    } else if(nite < fort) {
        return -1;
    } else {
        return 0;
    }
}

void printAirport(const Airport *a, int n) {
    for(int i = 0; i < n; i++) {
printf("%s, %s, %s, %.2f %.2f, %d, %s, %s\n", a[i].gpsId, a[i].type, a[i].name, a[i].latitude, a[i].longitude, a[i].elevationFeet, a[i].city, a[i].countryAbbrv);
    }
    return;
}

void printFoundAirport(const Airport *a) {
    printf("%s, %s, %s, %.2f %.2f, %d, %s, %s\n", a->gpsId, a->type, a->name, a->latitude, a->longitude, a->elevationFeet, a->city, a->countryAbbrv);
}

void generateReports(Airport *airports, int n) {
    printf("\n\n-=-=-=-Airports (Regular Order) -=-=-=- \n");
    printAirport(airports, n);

    qsort(airports, n, sizeof(Airport), cmpByGPSId);
    printf("\n\n-=-=-=-Airports (By GPS ID)-=-=-=- \n");
    printAirport(airports, n);

    qsort(airports, n, sizeof(Airport), cmpByType);
    printf("\n\n-=-=-=-Airports (By Type)-=-=-=- \n");
    printAirport(airports, n);

    qsort(airports, n, sizeof(Airport), cmpByName);
    printf("\n\n-=-=-=-Airports (By Name)-=-=-=- \n");
    printAirport(airports, n);

    qsort(airports, n, sizeof(Airport), cmpByNameDesc);
    printf("\n\n-=-=-=-Airports (By Name Descending Order)-=-=-=- \n");
    printAirport(airports, n);

    qsort(airports, n, sizeof(Airport), cmpByLatitude);
    printf("\n\n-=-=-=-Airports (By Latitude)-=-=-=- \n");
    printAirport(airports, n);

    qsort(airports, n, sizeof(Airport), cmpByLongitude);
    printf("\n\n-=-=-=-Airports (Longitude)-=-=-=- \n");
    printAirport(airports, n);

    qsort(airports, n, sizeof(Airport), cmpByCountryCity);
    printf("\n\n-=-=-=-Airports (By Country then City)-=-=-=- \n");
    printAirport(airports, n);

    qsort(airports, n, sizeof(Airport), cmpByLincolnDistance);
    printf("\n\n-=-=-=-Airports (By Distance from Lincoln)-=-=-=- \n");
    printAirport(airports, n);

    // Search for the airport that is closest to Lincoln (40.8507, -967581)

    qsort(airports, n, sizeof(Airport), cmpByLongitude);
    Airport *closestToLinc = &airports[0];
    printf("\n\nAirport Closest To Lincoln Is: \n");
    printFoundAirport(closestToLinc);
    // Search for the airport that is is the middle in terms of longitude

    qsort(airports, n, sizeof(Airport), cmpByLongitude);
    Airport *midLong = &airports[n/2];
    printf("\nFound East-West Median: \n");
    printFoundAirport(midLong);

    // Search for the airport that is located in the city "New York". If one doesn't
    // exist, print an appropriate message
    qsort(airports, n, sizeof(Airport), cmpByCountryCity);
    Airport *dummyKey = createAirport("", "", "", 0.0, 0.0, 0, "New York", "USA");
    Airport *newYorkResult = NULL;
    newYorkResult = bsearch(dummyKey, airports, n, sizeof(Airport), cmpByCountryCity);
    if(newYorkResult != NULL) {
    printf("\nAirport in New York City: \n");
    printFoundAirport(newYorkResult);
    } else {
        printf("There was not an airport found in New York\n");
    }

    // Search for the airport type "large_airport" and print it out. If it doesn't exist
    // print out the appropriate message

    qsort(airports, n, sizeof(Airport), cmpByType);
    Airport *dummyKey2 = createAirport("", "large_airport", "", 0.0, 0.0, 0, "", "");
    Airport *largeAirportResult = NULL;
    largeAirportResult = bsearch(dummyKey2, airports, n, sizeof(Airport), cmpByType);
    if(largeAirportResult != NULL) {
        printf("\nLarge Airport found: \n");
        printFoundAirport(largeAirportResult);
        printf("\n");
    } else {
        printf("There were not any large airports found.\n\n");
    }
}

