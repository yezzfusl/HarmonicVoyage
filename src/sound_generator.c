#include "../include/sound_generator.h"
#include "../include/utils.h"
#include <math.h>

void generate_sine_wave(int16_t* buffer, int num_samples, Note note) {
    for (int i = 0; i < num_samples; i++) {
        double t = (double)i / SAMPLE_RATE;
        buffer[i] = (int16_t)(AMPLITUDE * sin(2.0 * PI * note.frequency * t + note.phase));
    }
}

void generate_square_wave(int16_t* buffer, int num_samples, Note note) {
    for (int i = 0; i < num_samples; i++) {
        double t = (double)i / SAMPLE_RATE;
        double value = sin(2.0 * PI * note.frequency * t + note.phase);
        buffer[i] = (int16_t)(AMPLITUDE * (value >= 0 ? 1 : -1));
    }
}

void generate_triangle_wave(int16_t* buffer, int num_samples, Note note) {
    for (int i = 0; i < num_samples; i++) {
        double t = (double)i / SAMPLE_RATE;
        double period = 1.0 / note.frequency;
        double normalized_t = fmod(t + note.phase / (2.0 * PI * note.frequency), period) / period;
        double value = 4.0 * fabs(normalized_t - 0.5) - 1.0;
        buffer[i] = (int16_t)(AMPLITUDE * value);
    }
}

void generate_sawtooth_wave(int16_t* buffer, int num_samples, Note note) {
    for (int i = 0; i < num_samples; i++) {
        double t = (double)i / SAMPLE_RATE;
        double period = 1.0 / note.frequency;
        double normalized_t = fmod(t + note.phase / (2.0 * PI * note.frequency), period) / period;
        double value = 2.0 * normalized_t - 1.0;
        buffer[i] = (int16_t)(AMPLITUDE * value);
    }
}
