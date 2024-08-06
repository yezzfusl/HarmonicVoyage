#include "../include/visualizer.h"
#include <math.h>

#define MAX_SAMPLES 1024
#define MAX_BARS 64
#define BAR_WIDTH ((SCREEN_WIDTH - (MAX_BARS - 1)) / MAX_BARS)

static float spectrum[MAX_BARS] = {0};

void init_visualizer(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Jingle Bells Synth Visualizer");
    SetTargetFPS(60);
}

void update_visualizer(const int16_t* buffer, int buffer_size) {
    float samples[MAX_SAMPLES] = {0};
    int sample_count = (buffer_size < MAX_SAMPLES) ? buffer_size : MAX_SAMPLES;

    // Normalize samples
    for (int i = 0; i < sample_count; i++) {
        samples[i] = (float)buffer[i] / 32768.0f;
    }

    // Compute spectrum using a simple FFT-like approach
    for (int i = 0; i < MAX_BARS; i++) {
        float sum = 0;
        for (int j = 0; j < sample_count; j++) {
            sum += fabsf(samples[j] * sinf(2 * PI * i * j / MAX_BARS));
        }
        spectrum[i] = sum / sample_count;
    }
}

void draw_visualizer(void) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    for (int i = 0; i < MAX_BARS; i++) {
        float bar_height = spectrum[i] * SCREEN_HEIGHT;
        DrawRectangle(i * (BAR_WIDTH + 1), SCREEN_HEIGHT - bar_height, BAR_WIDTH, bar_height, MAROON);
    }

    DrawFPS(10, 10);
    EndDrawing();
}

void close_visualizer(void) {
    CloseWindow();
}
