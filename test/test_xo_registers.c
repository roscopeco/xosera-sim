#include <string.h>

#include "unity.h"
#include "xosera.h"

static Xosera xosera_b;
static Xosera *xosera = &xosera_b;

void setUp(void) {
    memset(xosera, 0, sizeof(Xosera));
    if (!xo_init(xosera)) {
        TEST_FAIL_MESSAGE("Xosera init failed!");
    }
}

void tearDown(void) {
    // Nothing
}

static void test_xo_registers_bus_read_16_XM_FEATURE_correct_values(void) {
    uint16_t feature = xo_bus_read_xm_reg_16(xosera, XM_FEATURE);

    TEST_ASSERT_BITS_MESSAGE(XO_FEATURE_MONRES_MASK,        0x0001,     feature,    "[Monitor resolution should be 848x480]");
    TEST_ASSERT_BITS_MESSAGE(XO_FEATURE_AUDCHAN_MASK,       0x0000,     feature,    "[Should have zero audio channels]");
    TEST_ASSERT_BITS_MESSAGE(XO_FEATURE_CONFIG_MASK,        0x0000,     feature,    "[Should report to config zero]");

    TEST_ASSERT_BITS_LOW_MESSAGE(XO_FEATURE_COPPER_EN_MASK,             feature,    "[Copper should be disabled]");
    TEST_ASSERT_BITS_LOW_MESSAGE(XO_FEATURE_BLITTER_EN_MASK,            feature,    "[Blitter should be disabled]");
    TEST_ASSERT_BITS_HIGH_MESSAGE(XO_FEATURE_PFB_EN_MASK,               feature,    "[Playfield B should be enabled]");
    TEST_ASSERT_BITS_LOW_MESSAGE(XO_FEATURE_UART_EN_MASK,               feature,    "[UART should be disabled]");
}

static void test_xo_registers_bus_write_16_XM_FEATURE_is_noop(void) {    
    xo_bus_write_xm_reg_16(xosera, XM_FEATURE, 0xffff);

    test_xo_registers_bus_read_16_XM_FEATURE_correct_values();
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_xo_registers_bus_read_16_XM_FEATURE_correct_values);
    RUN_TEST(test_xo_registers_bus_write_16_XM_FEATURE_is_noop);
    return UNITY_END();
}