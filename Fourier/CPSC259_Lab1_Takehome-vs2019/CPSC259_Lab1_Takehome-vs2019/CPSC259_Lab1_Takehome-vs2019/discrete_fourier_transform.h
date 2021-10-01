/*
 * File:         discrete_fourier_transform.h
 * Purpose:      Contains Prototypes For a Fast Discrete Fourier
 *               transformation based on code available at:
 *               http://paulbourke.net/miscellaneous/dft/
 * Author:       Muntakim Rahman and Hao Qi
 * Student #s:   71065221 and 50813344
 * CS Accounts:  y0f2b and d5j2b
 * Date:         September 9th 2019
*/

/*
 ********************************************************************
 * DO NOT EDIT THIS FILE
 ******************************************************************
 */

#pragma once

/* Function Prototype */
void fft(short int dir, long m, double x[], double y[]);