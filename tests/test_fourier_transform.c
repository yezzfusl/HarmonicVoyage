#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include "../include/fourier_transform.h"

#define TEST_SIZE 8
#define EPSILON 1e-6

void test_fft_ifft() {
    cplx input[TEST_SIZE] = {1, 1, 1, 1, 0, 0, 0, 0};
    cplx original[TEST_SIZE];
    for (int i = 0; i < TEST_SIZE; i++) {
        original[i] = input[i];
    }

    fft(input, TEST_SIZE);
    ifft(input, TEST_SIZE);

    for (int i = 0; i < TEST_SIZE; i++) {
        if (cabs(input[i] - original[i]) > EPSILON) {
            fprintf(stderr, "FFT/IFFT test failed: Difference at index %d\n", i);
            exit(1);
        }
    }

    printf("FFT/IFFT test passed\n");
}

void test_window_functions() {
    double buffer[TEST_SIZE] = {1, 1, 1, 1, 1, 1, 1, 1};
    
    apply_window(buffer, TEST_SIZE, "hann");
    if (fabs(buffer[0]) > EPSILON || fabs(buffer[TEST_SIZE-1]) > EPSILON) {
        fprintf(stderr, "Hann window test failed: Endpoints should be zero\n");
        exit(1);
    }

    for (int i = 0; i < TEST_SIZE; i++) {
        buffer[i] = 1;
    }
    apply_window(buffer, TEST_SIZE, "hamming");
    if (fabs(buffer[0]) < 0.08 || fabs(buffer[TEST_SIZE-1]) < 0.08) {
        fprintf(stderr, "Hamming window test failed: Endpoints should be non-zero\n");
        exit(1);
    }

    printf("Window functions test passed\n");
}

int main() {
    test_fft_ifft();
    test_window_functions();
    return 0;
}
