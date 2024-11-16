#include <stdarg.h>
#include <stdio.h>

#include "cmathematics.h"

#ifndef VEC_H
#define VEC_H


/*
Vector struct, with an unsigned int for the number of dimensions and a float pointer for the values
*/
typedef struct {
    unsigned int dim;
    float *elements;
} vec;

/*
NULL or 0 value definition for a vector, with a size of 0 and NULL pointer.
*/
extern const vec VEC_UNDEFINED;

/*
Create a vector object with the float array being allocated in the Heap.
*/
vec allocateVec(unsigned int dim);


/*
Create a vector of size 'dim' and fills each element with float 'val'.
*/
vec constructDefaultVector(unsigned int dim, float val);

/*
Create a vector with number of dimensions 'dim' with all values set to 0.0.
*/
vec constructEmptyVector(unsigned int dim);

/*
Create a vector of dimesions 'dim', filled with values inputted as args.
*/
vec newVector(unsigned int dim, ...);

/*
Macro for creating a vector by directly inputting values.
Will create a vector object with the args as the inputted values and dimensions as the number of args by calling newVector
*/
#define vector(...) newVector(NUMARGS(float, __VA_ARGS__), ##__VA_ARGS__)

/*
Copies a vector into another vector by reference of v.
*/
vec copyVecPtr(vec* v);

/*
Copies a vector into another vector by value of v.
*/
vec copyVec(vec v);

/*
Prints out values in vector v.
*/
void printVec(vec v);

/*
Returns true if all values in v1 are equal to all respective values in v2, otherwise returns false.
*/
bool vecEquals(vec v1, vec v2);

/*
Returns a vector equal to each value in v plus k.
*/
vec vecScalarAddition(vec v, float k);

/*
Increments each value in vector v by k.
*/
void vecScalarAdditionBy(vec *v, float k);

/*
Returns a vector equal to each value in v minus k.
*/
vec vecScalarSubtraction(vec v, float k);

/*
Decrements each value in vector v by k.
*/
void vecScalarSubtractionBy(vec *v, float k);

/*
Returns a vector equal to each value in v multiplied by k.
*/
vec vecScalarMultiplication(vec v, float k);

/*
Multiplies each value in vector v by k.
*/
void vecScalarMultiplicationBy(vec *v, float k);

/*
Returns a vector equal to each value in v divided by k.
*/
vec vecScalarDivision(vec v, float k);

/*
Divides each value in vector v by k.
*/
void vecScalarDivisionBy(vec *v, float k);

/*
Returns a vector of each value in v raised to the power k.
*/
vec vecPower(vec v, float k);

/*
Raises every value in v to the power of k.
*/
vec vecPowerOf(vec* v, float k);

/*
Returns a vector of each value in v1 summed with the respective value in v2.
*/
vec vecAdd(vec v1, vec v2);

/*
Adds each value in v2 to its respective value in v1.
*/
bool vecAddTo(vec *v1, vec v2);

/*
Returns a vector of each value in v2 subtracted from the respective value in v1.
*/
vec vecSubtract(vec v1, vec v2);

/*
Subtracts each value in v2 from its respective value in v1.
*/
bool vecSubtractFrom(vec *v1, vec v2);

/*
Returns a vector of each value in v1 multiplied by the respective value in v2.
*/
vec vecMultiply(vec v1, vec v2);

/*
Multiplies each value in v1 by its respective value in v2.
*/
bool vecMultiplyBy(vec *v1, vec v2);

/*
Returns a vector of each value in v1 divided by the respective value in v2.
*/
vec vecDivide(vec v1, vec v2);

/*
Divides each value in v1 by its respective value in v2.
*/
bool vecDivideBy(vec *v1, vec v2);

/*
Returns the float value obtained by performing the dot product of v1 and v2, (v1 . v2).
*/
float dot(vec v1, vec v2);

/*
Returns true if v1 and v2 are perpendicular, else return false.
*/
bool orthogonal(vec v1, vec v2);

/*
Returns a vector equal to the cross product of v1 and v2 (v1 x v2).
*/
vec cross(vec v1, vec v2);

/*
Returns the float value of the magnitude of v.
*/
float vecMagnitude(vec v);

/*
Returns the float value of the magnitude of v, squared.
*/
float vecMagnitudeSquared(vec v);

/*
Returns the unit vector of v.
*/
vec vecNormalised(vec v);

/*
Normalises vector v.
*/
void vecNormalise(vec* v);

#endif