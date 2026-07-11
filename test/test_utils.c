#include "unity.h"
#include "utils.h"

// Funzioni richieste da Unity, eseguite prima e dopo ogni test
void setUp(void) {}
void tearDown(void) {}

void test_temperatura_sotto_soglia_non_critica(void) {
    TEST_ASSERT_FALSE(is_temperature_critical(45.0f));
}

void test_temperatura_sopra_soglia_critica(void) {
    TEST_ASSERT_TRUE(is_temperature_critical(55.0f));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_temperatura_sotto_soglia_non_critica);
    RUN_TEST(test_temperatura_sopra_soglia_critica);
    return UNITY_END();
}