CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I../include
LDFLAGS = -lm -lSDL2

SRC_DIR = ../src
BUILD_DIR = .
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

EXECUTABLE = jingle_bells_synth

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(BUILD_DIR)/*.o $(EXECUTABLE)

test: $(BUILD_DIR)/test_sound_generator $(BUILD_DIR)/test_fourier_transform
	./$(BUILD_DIR)/test_sound_generator
	./$(BUILD_DIR)/test_fourier_transform

$(BUILD_DIR)/test_sound_generator: ../tests/test_sound_generator.c $(filter-out $(BUILD_DIR)/main.o, $(OBJECTS))
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(BUILD_DIR)/test_fourier_transform: ../tests/test_fourier_transform.c $(filter-out $(BUILD_DIR)/main.o, $(OBJECTS))
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
