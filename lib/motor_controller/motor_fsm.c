#include "motor_fsm.h"

static motor_state_t current_state;
static motor_fsm_hal_t hal_ops;
static bool last_button_state = false;

// Funzione interna per simulare is_temperature_critical se non hai utils.h sottomano
static bool check_temp_is_critical(float temp) {
    return temp > 50.0f; 
}

void motor_fsm_init(const motor_fsm_hal_t *hal) {
    // Inizializzazione manuale esplicita (fondamentale in bare-metal)
    if (hal) {
        hal_ops.set_motor = hal->set_motor;
        hal_ops.read_button = hal->read_button;
        hal_ops.read_temp = hal->read_temp;
    }
    current_state = STATE_IDLE;
    last_button_state = false;
    
    if (hal_ops.set_motor) hal_ops.set_motor(false);
}

void motor_fsm_update(void) {
    bool current_button = false;
    float temp = 20.0f;

    if (hal_ops.read_button) current_button = hal_ops.read_button();
    if (hal_ops.read_temp)   temp = hal_ops.read_temp();

    // Rilevamento fronte di salita (pressione tasto)
    bool button_pressed_now = (current_button && !last_button_state);
    last_button_state = current_button;

    // Emergenza temperatura: se critica, vai in errore sempre
    if (check_temp_is_critical(temp)) {
        current_state = STATE_ERROR;
        if (hal_ops.set_motor) hal_ops.set_motor(false);
    }

    switch (current_state) {
        case STATE_IDLE:
            if (button_pressed_now) {
                current_state = STATE_RUNNING;
                if (hal_ops.set_motor) hal_ops.set_motor(true);
            }
            break;

        case STATE_RUNNING:
            if (button_pressed_now) {
                current_state = STATE_IDLE;
                if (hal_ops.set_motor) hal_ops.set_motor(false);
            }
            break;

        case STATE_ERROR:
            if (!check_temp_is_critical(temp)) {
                current_state = STATE_IDLE;
            }
            break;
    }
}