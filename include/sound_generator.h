#ifndef SOUND_GENERATOR_H
#define SOUND_GENERATOR_H

#include <stdint.h>

#define SAMPLE_RATE 44100
#define AMPLITUDE 32760

typedef struct {
    double frequency;
    double phase;
    double duration;
} Note;

void generate_sine_wave(int16_t* buffer, int num_samples, Note note);
void generate_square_wave(int16_t* buffer, int num_samples, Note note);
void generate_triangle_wave(int16_t* buffer, int num_samples, Note note);
void generate_sawtooth_wave(int16_t* buffer, int num_samples, Note note);

#endif // SOUND_GENERATOR_H
