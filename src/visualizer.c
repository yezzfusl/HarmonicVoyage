#include "../include/visualizer.h"
#include <math.h>

#define MAX_SAMPLES 2048
#define MAX_BARS 128
#define BAR_WIDTH ((SCREEN_WIDTH - (MAX_BARS - 1)) / MAX_BARS)

static float spectrum[MAX_BARS] = {0};
static RenderTexture2D target;

void init_visualizer(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Jingle Bells Synth Visualizer");
    SetTargetFPS(60);
    target = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);
}

void update_visualizer(const int16_t* buffer, int buffer_size) {
    float samples[MAX_SAMPLES] = {0};
    int sample_count = (buffer_size < MAX_SAMPLES) ? buffer_size : MAX_SAMPLES;

    // Normalize samples and apply Hann window
    for (int i = 0; i < sample_count; i++) {
        float hann = 0.5f * (1 - cosf(2 * PI * i / (sample_count - 1)));
        samples[i] = hann * ((float)buffer[i] / 32768.0f);
    }

    // Compute spectrum using a simple FFT-like approach
    for (int i = 0; i < MAX_BARS; i++) {
        float sum = 0;
        for (int j = 0; j < sample_count; j++) {
            sum += fabsf(samples[j] * sinf(2 * PI * i * j / MAX_BARS));
        }
        spectrum[i] = fmaxf(spectrum[i] * 0.95f, sum / sample_count);
    }
}

void draw_visualizer(void) {
    BeginTextureMode(target);
    ClearBackground(RAYWHITE);

    for (int i = 0; i < MAX_BARS; i++) {
        float bar_height = spectrum[i] * SCREEN_HEIGHT;
        DrawRectangle(i * (BAR_WIDTH + 1), SCREEN_HEIGHT - bar_height, BAR_WIDTH, bar_height, ColorFromHSV(i * 360.0f / MAX_BARS, 0.8f, 0.8f));
    }

    DrawFPS(10, 10);
    EndTextureMode();

    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawTextureRec(target.texture, (Rectangle){0, 0, SCREEN_WIDTH, -SCREEN_HEIGHT}, (Vector2){0, 0}, WHITE);
    EndDrawing();
}

void close_visualizer(void) {
    UnloadRenderTexture(target);
    CloseWindow();
}
