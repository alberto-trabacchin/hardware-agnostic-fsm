#include "utils.h"

bool is_temperature_critical(float temp) {
    return temp > 50.0f;
}