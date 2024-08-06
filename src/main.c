#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <complex.h>
#include "../include/sound_generator.h"
#include "../include/utils.h"
#include "../include/fourier_transform.h"

#define BUFFER_SIZE 4096
#define FFT_SIZE 2048

void audio_callback(void* userdata, Uint8* stream, int len) {
    int16_t* buffer = (int16_t*)stream;
    int num_samples = len / sizeof(int16_t);
    
    static double time = 0.0;
    Note note = {440.0, 0.0, 1.0};  // A4 note
    
    generate_sine_wave(buffer, num_samples, note);
    
    // Apply FFT for spectral analysis
    cplx fft_buffer[FFT_SIZE];
    for (int i = 0; i < FFT_SIZE; i++) {
        fft_buffer[i] = i < num_samples ? buffer[i] : 0;
    }
    
    fft(fft_buffer, FFT_SIZE);
    
    // Here you can manipulate the frequency domain data if needed
    
    // Apply inverse FFT to get back to time domain
    ifft(fft_buffer, FFT_SIZE);
    
    // Copy the processed data back to the output buffer
    for (int i = 0; i < num_samples; i++) {
        buffer[i] = (int16_t)creal(fft_buffer[i]);
    }
    
    time += (double)num_samples / SAMPLE_RATE;
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        fprintf(stderr, "SDL initialization failed: %s\n", SDL_GetError());
        return 1;
    }

    SDL_AudioSpec want, have;
    SDL_AudioDeviceID dev;

    SDL_memset(&want, 0, sizeof(want));
    want.freq = SAMPLE_RATE;
    want.format = AUDIO_S16SYS;
    want.channels = 1;
    want.samples = BUFFER_SIZE;
    want.callback = audio_callback;

    dev = SDL_OpenAudioDevice(NULL, 0, &want, &have, 0);
    if (dev == 0) {
        fprintf(stderr, "Failed to open audio device: %s\n", SDL_GetError());
        return 1;
    }

    SDL_PauseAudioDevice(dev, 0);

    printf("Playing sound for 5 seconds...\n");
    SDL_Delay(5000);

    SDL_CloseAudioDevice(dev);
    SDL_Quit();

    return 0;
}
