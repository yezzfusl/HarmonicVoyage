#ifndef FOURIER_TRANSFORM_H
#define FOURIER_TRANSFORM_H

#include <complex.h>
#include <stddef.h>

typedef double complex cplx;

void fft(cplx buf[], int n);
void ifft(cplx buf[], int n);
void apply_window(double* buffer, int size, const char* window_type);

#endif // FOURIER_TRANSFORM_H
