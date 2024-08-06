#include "../include/utils.h"

double note_to_frequency(int note) {
    return 440.0 * pow(2.0, (note - 69) / 12.0);
}
