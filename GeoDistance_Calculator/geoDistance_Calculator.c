#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define PI 3.14159265358979323846 // Define constant for PI

// Structure to hold geographical coordinates
struct geoCoord {
    double latitudes;  // Latitude of the coordinate
    double longitudes; // Longitude of the coordinate
};

// Function prototypes
double DistanceKm(double lat1, double lat2, double lon1, double lon2);
double totalDistanceKm(struct geoCoord* coordinates, int numWaypoints);

int main() {
    int waypntsNum; // Number of waypoints
    printf("Enter the number of waypoints (minimum = 2): ");

    // Input validation loop for the number of waypoints
    do {
        if ((scanf("%d", &waypntsNum)) != 1 || waypntsNum <= 1) {
            printf("Invalid input. Expected a number greater than 1.\nPlease try again: ");
            while (getchar() != '\n'); // Clear invalid input
        }
    } while (waypntsNum <= 1);

    // Allocate memory for waypoints
    struct geoCoord* coordinates = (struct geoCoord*)malloc(waypntsNum * sizeof(struct geoCoord));
    if (coordinates == NULL)
        exit(EXIT_FAILURE); // Exit if memory allocation fails

    printf("\nEnter the coordinates of the waypoints as <latitude> <longitude>\n");

    // Input loop for waypoints' coordinates
    for (int i = 0; i < waypntsNum; i++) {
        printf("Waypoint %d:", i + 1);

        do {
            // Read latitude and longitude, validate the input
            if (scanf("%lf %lf", &coordinates[i].latitudes, &coordinates[i].longitudes) != 2 ||
                coordinates[i].latitudes < -90.0 || coordinates[i].latitudes > 90.0 ||
                coordinates[i].longitudes < -180.0 || coordinates[i].longitudes > 180.0) {
                printf("Invalid input. Expected <latitude> <longitude>.\nPlease try again: ");
            }
            while (getchar() != '\n'); // Clear invalid input
        } while (coordinates[i].latitudes < -90.0 || coordinates[i].latitudes > 90.0 ||
            coordinates[i].longitudes < -180.0 || coordinates[i].longitudes > 180.0);
    }

    // Calculate the total distance between waypoints
    double result = totalDistanceKm(coordinates, waypntsNum);
    printf("\nBy taking this route you will travel %.2lf Km\n", result);

    // Free allocated memory
    free(coordinates);

    getchar(); // Wait for user input before exiting
    return 0;
}

// Function to calculate the distance between two geographic points using the Haversine formula
double DistanceKm(double lat1, double lat2, double lon1, double lon2) {
    // Calculate distance using the formula
    double distance = 6378.388 * acos(sin(lat1 * PI / 180.0) * sin(lat2 * PI / 180.0) +
        cos(lat1 * PI / 180.0) * cos(lat2 * PI / 180.0) * cos((lon2 - lon1) * PI / 180.0));
    return distance; // Return the calculated distance
}

// Function to calculate the total distance for a series of waypoints
double totalDistanceKm(struct geoCoord* coordinates, int numWaypoints) {
    double totalDistance = 0.0; // Initialize total distance
    // Iterate through each pair of waypoints to calculate total distance
    for (int i = 0; i < numWaypoints - 1; i++) {
        totalDistance += DistanceKm(coordinates[i].latitudes, coordinates[i + 1].latitudes,
            coordinates[i].longitudes, coordinates[i + 1].longitudes);
    }
    return totalDistance; // Return the total calculated distance
}
