#include "unity.h"
#include "motor_fsm.h"

// Mock state variables
static bool mock_motor_state = false;
static bool mock_button_state = false;
static float mock_temp_state = 25.0f;

// Mock functions
static void mock_set_motor(bool on) {
    mock_motor_state = on;
}

static bool mock_read_button(void) {
    return mock_button_state;
}

static float mock_read_temp(void) {
    return mock_temp_state;
}

// Configurazione iniziale per ogni test
void setUp(void) {
    mock_motor_state = false;
    mock_button_state = false;
    mock_temp_state = 25.0f;

    motor_fsm_hal_t hal = {
        .set_motor = mock_set_motor,
        .read_button = mock_read_button,
        .read_temp = mock_read_temp
    };
    motor_fsm_init(&hal);
}

void tearDown(void) {}

// Test 1: Verifica dello stato iniziale
void test_inizializzazione_fsm(void) {
    TEST_ASSERT_EQUAL(STATE_IDLE, motor_fsm_get_state());
    TEST_ASSERT_FALSE(mock_motor_state);
}

// Test 2: Transizione normale IDLE -> STARTING -> RUNNING
void test_transizione_fino_a_running(void) {
    mock_button_state = true;
    
    motor_fsm_update(); // Transizione a STARTING
    TEST_ASSERT_EQUAL(STATE_STARTING, motor_fsm_get_state());

    motor_fsm_update(); // Transizione a RUNNING
    TEST_ASSERT_EQUAL(STATE_RUNNING, motor_fsm_get_state());
    TEST_ASSERT_TRUE(mock_motor_state); // Il motore deve accendersi
}

// Test 3: Arresto di emergenza in caso di temperatura elevata
void test_arresto_emergenza_temperatura_alta(void) {
    // Portiamo la FSM in stato RUNNING
    mock_button_state = true;
    motor_fsm_update();
    motor_fsm_update();
    TEST_ASSERT_EQUAL(STATE_RUNNING, motor_fsm_get_state());

    // Simuliamo innalzamento temperatura
    mock_temp_state = 55.0f;
    motor_fsm_update();

    TEST_ASSERT_EQUAL(STATE_ERROR, motor_fsm_get_state());
    TEST_ASSERT_FALSE(mock_motor_state); // Il motore deve essere spento subito
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_inizializzazione_fsm);
    RUN_TEST(test_transizione_fino_a_running);
    RUN_TEST(test_arresto_emergenza_temperatura_alta);
    return UNITY_END();
}