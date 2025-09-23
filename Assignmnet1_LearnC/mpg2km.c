/*
 * mpg2km.c / Assignment1 - Learn C
 *
 * ZW / CS5600 / Northeastern University
 * Fall 2025 / Sep 8, 2025
 *
 */

#include "mpg2km.h"

/*
 * Convert miles per gallon (mpg) to kilometers per liter (km/l)
 * Parameters:
 *   mpg - fuel efficiency in miles per gallon
 * Returns:
 *   equivalent fuel efficiency in kilometers per liter
 */
double mpg2kml(double mpg) {
    return mpg * 1.60934 / 3.78541;
}

/*
 * Convert miles per gallon (mpg) to liters per 100 kilometers (l/100km)
 * Parameters:
 *   mpg - fuel efficiency in miles per gallon
 * Returns:
 *   equivalent fuel consumption in liters per 100 kilometers
 */
double mpg2lphm(double mpg) {
    return 100 / mpg2kml(mpg);
}

/*
 * Convert liters per 100 kilometers (l/100km) to miles per gallon (mpg)
 * Parameters:
 *   lph - fuel consumption in liters per 100 kilometers
 * Returns:
 *   equivalent fuel efficiency in miles per gallon
 */
double lph2mpg(double lph) {
    return 100 / lph * 3.78541 / 1.60934;
}

