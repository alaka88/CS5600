/*
 * mpg2km.h / Assignment1 - Learn C
 *
 * ZW / CS5600 / Northeastern University
 * Fall 2025 / Sep 8, 2025
 *
 * This header file contains the function declarations for converting
 * fuel efficiency metrics:
 *   1. mpg2kml()  - miles per gallon to kilometers per liter
 *   2. mpg2lphm() - miles per gallon to liters per 100 kilometers
 *   3. lph2mpg()  - liters per 100 kilometers to miles per gallon
 */
#ifndef MPG2KM_H
#define MPG2KM_H

double mpg2kml(double mpg);
double mpg2lphm(double mpg);
double lph2mpg(double lph);

#endif
