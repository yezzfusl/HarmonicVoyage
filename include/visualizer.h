#ifndef VISUALIZER_H
#define VISUALIZER_H

#include <raylib.h>
#include <stdint.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450

void init_visualizer(void);
void update_visualizer(const int16_t* buffer, int buffer_size);
void draw_visualizer(void);
void close_visualizer(void);

#endif // VISUALIZER_H
