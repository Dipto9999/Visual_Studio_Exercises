/*
 * File:         discrete_fourier_transform.h
 * Purpose:      Contains Prototypes For a Fast Discrete Fourier
 *               transformation based on code available at:
 *               http://paulbourke.net/miscellaneous/dft/
 * Author:       Muntakim Rahman
 * Date:         March 12th 2021
*/

#ifndef DISCRETE_FOURIER_TRANSFORM_H
#define DISCRETE_FOURIER_TRANSFORM_H

/* Function Prototype */
void fft(short int dir, long m, double x[], double y[]);

#endif