#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../include/sound_generator.h"
#include "../include/utils.h"

#define TEST_BUFFER_SIZE 1000
#define EPSILON 1e-6

void test_sine_wave() {
    int16_t buffer[TEST_BUFFER_SIZE];
    Note note = {440.0, 0.0, 1.0};
    generate_sine_wave(buffer, TEST_BUFFER_SIZE, note);

    // Check if the first sample is close to 0
    if (fabs(buffer[0]) > EPSILON) {
        fprintf(stderr, "Sine wave test failed: First sample should be close to 0\n");
        exit(1);
    }

    // Check if the sample at quarter period is close to maximum amplitude
    int quarter_period_sample = (int)(SAMPLE_RATE / (4 * note.frequency));
    if (fabs(buffer[quarter_period_sample] - AMPLITUDE) > EPSILON) {
        fprintf(stderr, "Sine wave test failed: Sample at quarter period should be close to maximum amplitude\n");
        exit(1);
    }

    printf("Sine wave test passed\n");
}

int main() {
    test_sine_wave();
    return 0;
}
