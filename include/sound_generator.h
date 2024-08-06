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

typedef enum {
    WAVEFORM_SINE,
    WAVEFORM_SQUARE,
    WAVEFORM_TRIANGLE,
    WAVEFORM_SAWTOOTH
} Waveform;

void generate_waveform(int16_t* buffer, int num_samples, Note note, Waveform waveform);
void apply_adsr_envelope(int16_t* buffer, int num_samples, ADSR envelope);
void generate_jingle_bells_melody(int16_t* buffer, int buffer_size);

#endif // SOUND_GENERATOR_H
