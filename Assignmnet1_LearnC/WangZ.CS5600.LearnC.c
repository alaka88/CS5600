/*
 * WangZ.CS5600.LearnC.c / Assignment1 - Learn C
 *
 * ZW / CS5600 / Northeastern University
 * Fall 2025 / Sep 8, 2025
 *
 *
 * Description:
 *   This program tests three fuel efficiency conversion functions:
 *   1. mpg2kml()  - miles per gallon to kilometers per liter
 *   2. mpg2lphm() - miles per gallon to liters per 100 kilometers
 *   3. lph2mpg()  - liters per 100 kilometers to miles per gallon
 *   The functions are defined in mpg2km.c and declared in mpg2km.h.
 * 
 * The main() function tests both normal and "bad" argument values.
 */


#include <stdio.h>
#include "mpg2km.h"

int main() {
    // ==========================
    // Normal value tests
    // ==========================
    double mpg_values[] = {10, 20, 30, 50}; // Test mpg values
    double lph_values[] = {2.5, 5.0, 7.84, 12.0}; // Test l/100km values

    printf("=== Normal value tests ===\n");
    for (int i = 0; i < 4; i++) {
        printf("%.2f mpg = %.2f km/l, %.2f l/100km\n",
               mpg_values[i], mpg2kml(mpg_values[i]), mpg2lphm(mpg_values[i]));
    }

    for (int i = 0; i < 4; i++) {
        printf("%.2f l/100km = %.2f mpg\n",
               lph_values[i], lph2mpg(lph_values[i]));
    }

    // ==========================
    // "Bad" value tests
    // ==========================
    double bad_mpg[] = {0, -10}; // Invalid mpg values
    double bad_lph[] = {0, -5};  // Invalid liters per 100 km values

    printf("\n=== Bad value tests ===\n");
    for (int i = 0; i < 2; i++) {
        double km_per_l = mpg2kml(bad_mpg[i]);
        double l_per_100km = mpg2lphm(bad_mpg[i]);
        if (km_per_l < 0 || l_per_100km < 0)
            printf("%.2f mpg = invalid input\n", bad_mpg[i]);
        else
            printf("%.2f mpg = %.2f km/l, %.2f l/100km\n",
                   bad_mpg[i], km_per_l, l_per_100km);
    }

    for (int i = 0; i < 2; i++) {
        double mpg = lph2mpg(bad_lph[i]);
        if (mpg < 0)
            printf("%.2f l/100km = invalid input\n", bad_lph[i]);
        else
            printf("%.2f l/100km = %.2f mpg\n", bad_lph[i], mpg);
    }

    return 0;
}
