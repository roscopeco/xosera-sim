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
    // nothing
}

void test_xo_copper_pixel_should_do_blah_and_blah(void) {
    //TODO test stuff
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_xo_copper_pixel_should_do_blah_and_blah);
    return UNITY_END();
}
