#include "motor_fsm.h"
#include "utils.h" // Riutilizziamo la funzione is_temperature_critical
#include <stddef.h>

static motor_state_t current_state = STATE_IDLE;
static motor_fsm_hal_t hal_ops = {0};

void motor_fsm_init(const motor_fsm_hal_t *hal) {
    if (hal) {
        hal_ops = *hal;
    }
    current_state = STATE_IDLE;
    if (hal_ops.set_motor) {
        hal_ops.set_motor(false);
    }
}

void motor_fsm_update(void) {
    float temp = 0.0f;
    bool button_pressed = false;

    // Lettura input tramite callback protette da puntatore nullo
    if (hal_ops.read_temp) {
        temp = hal_ops.read_temp();
    }
    if (hal_ops.read_button) {
        button_pressed = hal_ops.read_button();
    }

    // Gestione della logica degli stati
    switch (current_state) {
        case STATE_IDLE:
            if (button_pressed) {
                current_state = STATE_STARTING;
            }
            break;

        case STATE_STARTING:
            if (is_temperature_critical(temp)) {
                current_state = STATE_ERROR;
                if (hal_ops.set_motor) hal_ops.set_motor(false);
            } else {
                current_state = STATE_RUNNING;
                if (hal_ops.set_motor) hal_ops.set_motor(true);
            }
            break;

        case STATE_RUNNING:
            if (is_temperature_critical(temp)) {
                current_state = STATE_ERROR;
                if (hal_ops.set_motor) hal_ops.set_motor(false);
            } else if (!button_pressed) {
                current_state = STATE_IDLE;
                if (hal_ops.set_motor) hal_ops.set_motor(false);
            }
            break;

        case STATE_ERROR:
            // Sblocca l'errore solo se la temperatura torna normale
            if (!is_temperature_critical(temp)) {
                current_state = STATE_IDLE;
            }
            break;
    }
}

motor_state_t motor_fsm_get_state(void) {
    return current_state;
}