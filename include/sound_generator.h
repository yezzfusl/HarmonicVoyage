#ifndef SOUND_GENERATOR_H
#define SOUND_GENERATOR_H

#include <stdint.h>

#define SAMPLE_RATE 44100
#define AMPLITUDE 32760

typedef struct {
    double frequency;
    double phase;
    double duration;
    double amplitude;
} Note;

typedef struct {
    double attack;
    double decay;
    double sustain;
    double release;
} ADSR;

void generate_sine_wave(int16_t* buffer, int num_samples, Note note);
void generate_square_wave(int16_t* buffer, int num_samples, Note note);
void generate_triangle_wave(int16_t* buffer, int num_samples, Note note);
void generate_sawtooth_wave(int16_t* buffer, int num_samples, Note note);
void apply_adsr_envelope(int16_t* buffer, int num_samples, ADSR envelope);
void generate_jingle_bells_melody(int16_t* buffer, int buffer_size);

#endif // SOUND_GENERATOR_H
