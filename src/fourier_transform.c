#include "../include/fourier_transform.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define PI 3.14159265358979323846

void fft(cplx buf[], int n) {
    if (n <= 1) return;

    cplx* even = malloc(n/2 * sizeof(cplx));
    cplx* odd = malloc(n/2 * sizeof(cplx));
    for (int i = 0; i < n/2; i++) {
        even[i] = buf[2*i];
        odd[i] = buf[2*i+1];
    }

    fft(even, n/2);
    fft(odd, n/2);

    for (int k = 0; k < n/2; k++) {
        cplx t = cexp(-2 * PI * I * k / n) * odd[k];
        buf[k] = even[k] + t;
        buf[k+n/2] = even[k] - t;
    }

    free(even);
    free(odd);
}

void ifft(cplx buf[], int n) {
    for (int i = 0; i < n; i++) {
        buf[i] = conj(buf[i]);
    }

    fft(buf, n);

    for (int i = 0; i < n; i++) {
        buf[i] = conj(buf[i]) / n;
    }
}

void apply_window(double* buffer, int size, const char* window_type) {
    if (strcmp(window_type, "hann") == 0) {
        for (int i = 0; i < size; i++) {
            buffer[i] *= 0.5 * (1 - cos(2 * PI * i / (size - 1)));
        }
    } else if (strcmp(window_type, "hamming") == 0) {
        for (int i = 0; i < size; i++) {
            buffer[i] *= 0.54 - 0.46 * cos(2 * PI * i / (size - 1));
        }
    } else if (strcmp(window_type, "blackman") == 0) {
        for (int i = 0; i < size; i++) {
            buffer[i] *= 0.42 - 0.5 * cos(2 * PI * i / (size - 1)) + 0.08 * cos(4 * PI * i / (size - 1));
        }
    }
    // Add more window types as needed
}
