#include <stdarg.h>
#include <stdio.h>

#include "cmathematics.h"
#include "vec.h"

#ifndef MATRIX_H
#define MATRIX_H

typedef struct{
    unsigned int rows;
    unsigned int cols;
    float **elements;
} mat;

extern const mat MAT_UNDEFINED;

mat allocateMat(unsigned int rows, unsigned int cols);

mat identity(unsigned int dim);

mat zeroMatrix(unsigned int rows, unsigned int cols);

mat newMatrix(unsigned int rows, unsigned int cols, ...);

mat copyMat(mat m);

mat copyMatPtr(mat* m);

void printMat(mat m);

vec getMatRow(mat *m, unsigned int row);

vec getMatCol(mat *m, unsigned int row);

mat toRowVec(vec *v);

mat toColVec(vec *v);

mat matScalarAddition(mat m, float k);

void matScalarAdditionTo(mat* m, float k);

//ADD SCALAR SUB, MUL AND DIV


mat matAdd(mat m1, mat m2);

bool matAddTo(mat* m1, mat m2);

mat matSubtract(mat m1, mat m2);

vec matVecMultiplication(mat m, vec v);

mat matDot(mat m1, mat m2);

#endif