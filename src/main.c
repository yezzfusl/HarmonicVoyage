#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <complex.h>
#include "../include/sound_generator.h"
#include "../include/utils.h"
#include "../include/fourier_transform.h"

#define BUFFER_SIZE 44100 * 10  // 10 seconds of audio

void audio_callback(void* userdata, Uint8* stream, int len) {
    int16_t* buffer = (int16_t*)userdata;
    static int current_sample = 0;
    
    int samples_to_copy = len / sizeof(int16_t);
    if (current_sample + samples_to_copy > BUFFER_SIZE) {
        samples_to_copy = BUFFER_SIZE - current_sample;
    }
    
    memcpy(stream, &buffer[current_sample], samples_to_copy * sizeof(int16_t));
    current_sample += samples_to_copy;
    
    if (current_sample >= BUFFER_SIZE) {
        current_sample = 0;
    }
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        fprintf(stderr, "SDL initialization failed: %s\n", SDL_GetError());
        return 1;
    }

    int16_t* audio_buffer = (int16_t*)malloc(BUFFER_SIZE * sizeof(int16_t));
    if (!audio_buffer) {
        fprintf(stderr, "Failed to allocate audio buffer\n");
        return 1;
    }

    generate_jingle_bells_melody(audio_buffer, BUFFER_SIZE);

    SDL_AudioSpec want, have;
    SDL_AudioDeviceID dev;

    SDL_memset(&want, 0, sizeof(want));
    want.freq = SAMPLE_RATE;
    want.format = AUDIO_S16SYS;
    want.channels = 1;
    want.samples = 4096;
    want.callback = audio_callback;
    want.userdata = audio_buffer;

    dev = SDL_OpenAudioDevice(NULL, 0, &want, &have, 0);
    if (dev == 0) {
        fprintf(stderr, "Failed to open audio device: %s\n", SDL_GetError());
        free(audio_buffer);
        return 1;
    }

    SDL_PauseAudioDevice(dev, 0);

    printf("Playing Jingle Bells melody. Press Enter to stop...\n");
    getchar();

    SDL_CloseAudioDevice(dev);
    SDL_Quit();
    free(audio_buffer);

    return 0;
}
