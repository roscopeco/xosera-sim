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

static void test_xo_registers_bus_read_16_XM_SYS_CTRL_correct_defaults(void) {
    uint16_t feature = xo_bus_read_xm_reg_16(xosera, XM_SYS_CTRL);

    TEST_ASSERT_BITS_MESSAGE(XO_SYS_CTRL_NIBBLE_MASK_MASK,  0x000f,     feature,    "[All nibbles should be unmasked by default]");
    TEST_ASSERT_BITS_MESSAGE(XO_SYS_CTRL_RESERVED1_MASK,    0x0000,     feature,    "[Reserved bits 1 should be zero]");

    TEST_ASSERT_BITS_LOW_MESSAGE(XO_SYS_CTRL_PIX_8B_MASK_MASK,          feature,    "[PIX_8B_MASK should be disabled]");
    TEST_ASSERT_BITS_LOW_MESSAGE(XO_SYS_CTRL_PIX_NO_MASK_MASK,          feature,    "[PIX_NO_MASK should be disabled]");
    TEST_ASSERT_BITS_LOW_MESSAGE(XO_SYS_CTRL_VBLANK_FLAG_MASK,          feature,    "[Should not be in VBLANK at init]");
    TEST_ASSERT_BITS_LOW_MESSAGE(XO_SYS_CTRL_HBLANK_FLAG_MASK,          feature,    "[Should not be in HBLANK at init]");
    TEST_ASSERT_BITS_LOW_MESSAGE(XO_SYS_CTRL_BLIT_BUSY_FLAG_MASK,       feature,    "[Blitter should not be busy at init]");
    TEST_ASSERT_BITS_LOW_MESSAGE(XO_SYS_CTRL_BLIT_FULL_FLAG_MASK,       feature,    "[Blitter should not be full at init]");
    TEST_ASSERT_BITS_LOW_MESSAGE(XO_SYS_CTRL_MEM_WAIT_FLAG_MASK,        feature,    "[Memory should not be busy at init]");
}

static void test_xo_registers_bus_read_8_u_XM_SYS_CTRL_correct_defaults(void) {
    uint8_t feature = xo_bus_read_xm_reg_8_u(xosera, XM_SYS_CTRL);

    TEST_ASSERT_BITS_LOW_MESSAGE(XO_SYS_CTRL_PIX_NO_MASK_MASK,          feature,    "[PIX_NO_MASK should be disabled]");
    TEST_ASSERT_BITS_LOW_MESSAGE(XO_SYS_CTRL_VBLANK_FLAG_MASK,          feature,    "[Should not be in VBLANK at init]");
    TEST_ASSERT_BITS_LOW_MESSAGE(XO_SYS_CTRL_HBLANK_FLAG_MASK,          feature,    "[Should not be in HBLANK at init]");
    TEST_ASSERT_BITS_LOW_MESSAGE(XO_SYS_CTRL_BLIT_BUSY_FLAG_MASK,       feature,    "[Blitter should not be busy at init]");
    TEST_ASSERT_BITS_LOW_MESSAGE(XO_SYS_CTRL_BLIT_FULL_FLAG_MASK,       feature,    "[Blitter should not be full at init]");
    TEST_ASSERT_BITS_LOW_MESSAGE(XO_SYS_CTRL_MEM_WAIT_FLAG_MASK,        feature,    "[Memory should not be busy at init]");
}

static void test_xo_registers_bus_read_8_l_XM_SYS_CTRL_correct_defaults(void) {
    uint8_t feature = xo_bus_read_xm_reg_8_l(xosera, XM_SYS_CTRL);

    TEST_ASSERT_BITS_MESSAGE(XO_SYS_CTRL_NIBBLE_MASK_MASK,  0x000f,     feature,    "[All nibbles should be unmasked by default]");
    TEST_ASSERT_BITS_MESSAGE(XO_SYS_CTRL_RESERVED1_MASK,    0x0000,     feature,    "[Reserved bits 1 should be zero]");

    TEST_ASSERT_BITS_LOW_MESSAGE(XO_SYS_CTRL_PIX_8B_MASK_MASK,          feature,    "[PIX_8B_MASK should be disabled]");
}

static void test_xo_registers_bus_read_16_XM_FEATURE_correct_values(void) {
    uint16_t feature = xo_bus_read_xm_reg_16(xosera, XM_FEATURE);

    TEST_ASSERT_BITS_MESSAGE(XO_FEATURE_MONRES_MASK,        0x0001,     feature,    "[Monitor resolution should be 848x480]");
    TEST_ASSERT_BITS_MESSAGE(XO_FEATURE_AUDCHAN_MASK,       0x0000,     feature,    "[Should have zero audio channels]");
    TEST_ASSERT_BITS_MESSAGE(XO_FEATURE_CONFIG_MASK,        0x0000,     feature,    "[Should report to config zero]");
    TEST_ASSERT_BITS_MESSAGE(XO_FEATURE_RESERVED_MASK,      0x0000,     feature,    "[Reserved bits should be zero]");

    TEST_ASSERT_BITS_LOW_MESSAGE(XO_FEATURE_COPPER_EN_MASK,             feature,    "[Copper should be disabled]");
    TEST_ASSERT_BITS_LOW_MESSAGE(XO_FEATURE_BLITTER_EN_MASK,            feature,    "[Blitter should be disabled]");
    TEST_ASSERT_BITS_HIGH_MESSAGE(XO_FEATURE_PFB_EN_MASK,               feature,    "[Playfield B should be enabled]");
    TEST_ASSERT_BITS_LOW_MESSAGE(XO_FEATURE_UART_EN_MASK,               feature,    "[UART should be disabled]");
}

static void test_xo_registers_bus_read_8_u_XM_FEATURE_correct_values(void) {
    uint8_t feature = xo_bus_read_xm_reg_8_u(xosera, XM_FEATURE);

    TEST_ASSERT_BITS_MESSAGE(XO_FEATURE_AUDCHAN_MASK,       0x0000,     feature,    "[Should have zero audio channels]");
    TEST_ASSERT_BITS_MESSAGE(XO_FEATURE_CONFIG_MASK,        0x0000,     feature,    "[Should report to config zero]");
    TEST_ASSERT_BITS_MESSAGE(XO_FEATURE_RESERVED_MASK,      0x0000,     feature,    "[Reserved bits should be zero]");
}

static void test_xo_registers_bus_read_8_l_XM_FEATURE_correct_values(void) {
    uint16_t feature = xo_bus_read_xm_reg_8_l(xosera, XM_FEATURE);

    TEST_ASSERT_BITS_MESSAGE(XO_FEATURE_MONRES_MASK,        0x0001,     feature,    "[Monitor resolution should be 848x480]");

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

    RUN_TEST(test_xo_registers_bus_read_16_XM_SYS_CTRL_correct_defaults);
    RUN_TEST(test_xo_registers_bus_read_8_u_XM_SYS_CTRL_correct_defaults);
    RUN_TEST(test_xo_registers_bus_read_8_l_XM_SYS_CTRL_correct_defaults);

    RUN_TEST(test_xo_registers_bus_read_16_XM_FEATURE_correct_values);
    RUN_TEST(test_xo_registers_bus_read_8_u_XM_FEATURE_correct_values);
    RUN_TEST(test_xo_registers_bus_read_8_l_XM_FEATURE_correct_values);
    RUN_TEST(test_xo_registers_bus_write_16_XM_FEATURE_is_noop);

    return UNITY_END();
}
