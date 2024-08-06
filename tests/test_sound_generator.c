#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../include/sound_generator.h"
#include "../include/utils.h"

#define TEST_BUFFER_SIZE 1000
#define EPSILON 1e-6

void test_sine_wave() {
    int16_t buffer[TEST_BUFFER_SIZE];
    Note note = {440.0, 0.0, 1.0, 1.0};
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

void test_adsr_envelope() {
    int16_t buffer[TEST_BUFFER_SIZE];
    for (int i = 0; i < TEST_BUFFER_SIZE; i++) {
        buffer[i] = AMPLITUDE;
    }

    ADSR envelope = {0.1, 0.1, 0.5, 0.1};
    apply_adsr_envelope(buffer, TEST_BUFFER_SIZE, envelope);

    // Check attack
    if (buffer[0] != 0 || buffer[TEST_BUFFER_SIZE / 10] != AMPLITUDE) {
        fprintf(stderr, "ADSR test failed: Attack phase incorrect\n");
        exit(1);
    }

    // Check sustain
    if (fabs((double)buffer[TEST_BUFFER_SIZE / 2] / AMPLITUDE - envelope.sustain) > EPSILON) {
        fprintf(stderr, "ADSR test failed: Sustain level incorrect\n");
        exit(1);
    }

    // Check release
    if (buffer[TEST_BUFFER_SIZE - 1] != 0) {
        fprintf(stderr, "ADSR test failed: Release phase incorrect\n");
        exit(1);
    }

    printf("ADSR envelope test passed\n");
}

void test_jingle_bells_melody() {
    int16_t buffer[SAMPLE_RATE * 10];  // 10 seconds of audio
    generate_jingle_bells_melody(buffer, SAMPLE_RATE * 10);

    // Check if the buffer contains non-zero values
    int non_zero_count = 0;
    for (int i = 0; i < SAMPLE_RATE * 10; i++) {
        if (buffer[i] != 0) {
            non_zero_count++;
        }
    }

    if (non_zero_count == 0) {
        fprintf(stderr, "Jingle Bells melody test failed: Buffer is empty\n");
        exit(1);
    }

    printf("Jingle Bells melody test passed\n");
}

int main() {
    test_sine_wave();
    test_adsr_envelope();
    test_jingle_bells_melody();
    return 0;
}
