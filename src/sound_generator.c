#include "../include/sound_generator.h"
#include "../include/utils.h"
#include <math.h>
#include <string.h>

#define PI 3.14159265358979323846

static double sine_wave(double t, double frequency, double phase) {
    return sin(2.0 * PI * frequency * t + phase);
}

static double square_wave(double t, double frequency, double phase) {
    return sine_wave(t, frequency, phase) >= 0 ? 1.0 : -1.0;
}

static double triangle_wave(double t, double frequency, double phase) {
    double period = 1.0 / frequency;
    double normalized_t = fmod(t + phase / (2.0 * PI * frequency), period) / period;
    return 2.0 * fabs(2.0 * normalized_t - 1.0) - 1.0;
}

static double sawtooth_wave(double t, double frequency, double phase) {
    double period = 1.0 / frequency;
    double normalized_t = fmod(t + phase / (2.0 * PI * frequency), period) / period;
    return 2.0 * normalized_t - 1.0;
}

void generate_waveform(int16_t* buffer, int num_samples, Note note, Waveform waveform) {
    double (*wave_function)(double, double, double);

    switch (waveform) {
        case WAVEFORM_SQUARE:
            wave_function = square_wave;
            break;
        case WAVEFORM_TRIANGLE:
            wave_function = triangle_wave;
            break;
        case WAVEFORM_SAWTOOTH:
            wave_function = sawtooth_wave;
            break;
        case WAVEFORM_SINE:
        default:
            wave_function = sine_wave;
            break;
    }

    for (int i = 0; i < num_samples; i++) {
        double t = (double)i / SAMPLE_RATE;
        buffer[i] = (int16_t)(note.amplitude * AMPLITUDE * wave_function(t, note.frequency, note.phase));
    }
}

void apply_adsr_envelope(int16_t* buffer, int num_samples, ADSR envelope) {
    int attack_samples = envelope.attack * SAMPLE_RATE;
    int decay_samples = envelope.decay * SAMPLE_RATE;
    int sustain_samples = (num_samples - attack_samples - decay_samples - envelope.release * SAMPLE_RATE);
    int release_samples = envelope.release * SAMPLE_RATE;

    for (int i = 0; i < num_samples; i++) {
        double envelope_value;
        if (i < attack_samples) {
            envelope_value = (double)i / attack_samples;
        } else if (i < attack_samples + decay_samples) {
            envelope_value = 1.0 - (1.0 - envelope.sustain) * ((double)(i - attack_samples) / decay_samples);
        } else if (i < attack_samples + decay_samples + sustain_samples) {
            envelope_value = envelope.sustain;
        } else {
            envelope_value = envelope.sustain * (1.0 - (double)(i - attack_samples - decay_samples - sustain_samples) / release_samples);
        }
        buffer[i] = (int16_t)(buffer[i] * envelope_value);
    }
}

void generate_jingle_bells_melody(int16_t* buffer, int buffer_size) {
    memset(buffer, 0, buffer_size * sizeof(int16_t));

    const int num_notes = 26;
    const int notes[] = {
        71, 71, 71,
        71, 71, 71,
        71, 74, 67, 69, 71,
        72, 72, 72, 72,
        72, 71, 71, 71, 71,
        71, 69, 69, 71, 69, 74
    };
    const double durations[] = {
        0.25, 0.25, 0.5,
        0.25, 0.25, 0.5,
        0.25, 0.25, 0.25, 0.25, 1.0,
        0.25, 0.25, 0.25, 0.25,
        0.25, 0.25, 0.25, 0.125, 0.125,
        0.25, 0.25, 0.25, 0.25, 0.5, 0.5
    };

    int current_sample = 0;
    for (int i = 0; i < num_notes; i++) {
        Note note = {
            .frequency = note_to_frequency(notes[i]),
            .phase = 0.0,
            .duration = durations[i],
            .amplitude = 0.5
        };

        int note_samples = durations[i] * SAMPLE_RATE;
        int16_t note_buffer[note_samples];
        generate_waveform(note_buffer, note_samples, note, WAVEFORM_SINE);

        ADSR envelope = {0.01, 0.1, 0.7, 0.1};
        apply_adsr_envelope(note_buffer, note_samples, envelope);

        for (int j = 0; j < note_samples && current_sample < buffer_size; j++) {
            buffer[current_sample++] += note_buffer[j];
        }
    }
}
