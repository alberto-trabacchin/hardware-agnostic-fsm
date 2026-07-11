#ifndef MOTOR_FSM_H
#define MOTOR_FSM_H

#include <stdbool.h>

typedef enum {
    STATE_IDLE,
    STATE_STARTING,
    STATE_RUNNING,
    STATE_ERROR
} motor_state_t;

// "Contratto" Hardware (Dependency Injection)
typedef struct {
    void (*set_motor)(bool on);
    bool (*read_button)(void);
    float (*read_temp)(void);
} motor_fsm_hal_t;

// API della FSM
void motor_fsm_init(const motor_fsm_hal_t *hal);
void motor_fsm_update(void);
motor_state_t motor_fsm_get_state(void);

#endif // MOTOR_FSM_H