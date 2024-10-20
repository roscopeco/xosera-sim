#include <stdint.h>

#include "xosera.h"

#ifdef DEBUG_XO_REGISTERS
#define DEBUGF      printf
#else
#define DEBUGF(...) (((void)0))
#endif

// This determines the features reported by the simulated XM_FEATURE register.
#define XOSERA_SIM_FEATURES  ((0\
    | XO_FEATURE_MONRES_848_480 \
    | XO_FEATURE_PFB_ENABLED    \
    | XO_FEATURE_AUDIO_0        \
    | XO_FEATURE_CONFIG_0       \
    ))


inline uint8_t xo_bus_read_xr_reg_8_u(__attribute__((unused)) Xosera *xosera, __attribute__((unused)) XO_XR_REG_TYPE reg) {
    return 0;
}

inline uint8_t xo_bus_read_xr_reg_8_l(__attribute__((unused)) Xosera *xosera, __attribute__((unused)) XO_XR_REG_TYPE reg) {
    return 0;
}

inline void xo_bus_write_xr_reg_8_u(__attribute__((unused)) Xosera *xosera, __attribute__((unused)) XO_XR_REG_TYPE reg, __attribute__((unused)) uint8_t value) {

}

inline void xo_bus_write_xr_reg_8_l(__attribute__((unused)) Xosera *xosera, __attribute__((unused)) XO_XR_REG_TYPE reg, __attribute__((unused)) uint8_t value) {

}

uint8_t xo_bus_read_xm_reg_8_u(__attribute__((unused)) Xosera *xosera, __attribute__((unused)) XO_XM_REG_TYPE reg) {
    switch (reg) {
        case XM_SYS_CTRL:
        case XM_INT_CTRL:
        case XM_TIMER:
        case XM_RD_XADDR:
        case XM_WR_XADDR:
        case XM_RD_INCR:
        case XM_RD_ADDR:
        case XM_WR_INCR:
        case XM_WR_ADDR:
            return WORD_UPPER_BYTE(xosera->xm_regs[reg]);
        case XM_PIXEL_X:
        case XM_PIXEL_Y:
            DEBUGF("WARN: Read from write-only XM register 0x%04x\n", reg);
            return 0;
        case XM_XDATA:
            return 0;
        case XM_DATA:
        case XM_DATA_2:
            return 0;
        case XM_UART:
            DEBUGF("WARN: Write to unimplemented XM register 0x%04x\n", reg);
            return 0;
        case XM_FEATURE:
            return WORD_UPPER_BYTE(XOSERA_SIM_FEATURES);
    }
}

uint8_t xo_bus_read_xm_reg_8_l(__attribute__((unused)) Xosera *xosera, __attribute__((unused)) XO_XM_REG_TYPE reg) {
    switch (reg) {
        case XM_SYS_CTRL:
        case XM_INT_CTRL:
        case XM_TIMER:
        case XM_RD_XADDR:
        case XM_WR_XADDR:
        case XM_RD_INCR:
        case XM_RD_ADDR:
        case XM_WR_INCR:
        case XM_WR_ADDR:
            return WORD_LOWER_BYTE(xosera->xm_regs[reg]);
        case XM_PIXEL_X:
        case XM_PIXEL_Y:
            DEBUGF("WARN: Read from write-only XM register 0x%04x\n", reg);
            return 0;
        case XM_XDATA:
            return 0;
        case XM_DATA:
        case XM_DATA_2:
            return 0;
        case XM_UART:
            DEBUGF("WARN: Write to unimplemented XM register 0x%04x\n", reg);
            return 0;
        case XM_FEATURE:
            return WORD_LOWER_BYTE(XOSERA_SIM_FEATURES);
    }
}

void xo_bus_write_xm_reg_8_u(__attribute__((unused)) Xosera *xosera, __attribute__((unused)) XO_XM_REG_TYPE reg, __attribute__((unused)) uint8_t value) {
}

void xo_bus_write_xm_reg_8_l(__attribute__((unused)) Xosera *xosera, __attribute__((unused)) XO_XM_REG_TYPE reg, __attribute__((unused)) uint8_t value) {

}

inline uint16_t xo_bus_read_xr_reg_16(Xosera *xosera, XO_XR_REG_TYPE reg) {
    return xosera->xr_regs[reg];
}

inline void xo_bus_write_xr_reg_16(Xosera *xosera, XO_XR_REG_TYPE reg, uint16_t value) {
    xosera->xr_regs[reg] = value;
}

uint16_t xo_bus_read_xm_reg_16(Xosera *xosera, XO_XM_REG_TYPE reg) {
    uint16_t *xm_regs;
    uint16_t temp;

    switch (reg) {
        case XM_SYS_CTRL:
        case XM_INT_CTRL:
        case XM_TIMER:
        case XM_RD_XADDR:
        case XM_WR_XADDR:
        case XM_RD_INCR:
        case XM_RD_ADDR:
        case XM_WR_INCR:
        case XM_WR_ADDR:
            return xosera->xm_regs[reg];
        case XM_PIXEL_X:
        case XM_PIXEL_Y:
            DEBUGF("WARN: Read from write-only XM register 0x%04x\n", reg);
            return 0;
        case XM_XDATA:
            return xo_bus_read_xr_reg_16(xosera, xosera->xm_regs[XM_RD_XADDR]++);
        case XM_DATA:
        case XM_DATA_2:
            xm_regs = xosera->xm_regs;
            temp = xo_vram_read(xosera->vram, xm_regs[XM_RD_ADDR]);
            xm_regs[XM_RD_ADDR] += xm_regs[XM_RD_INCR];
            return temp;
        case XM_UART:
            DEBUGF("WARN: Write to unimplemented XM register 0x%04x\n", reg);
            return 0;
        case XM_FEATURE:
            return XOSERA_SIM_FEATURES;
    }
}

void xo_bus_write_xm_reg_16(Xosera *xosera, XO_XM_REG_TYPE reg, uint16_t value) {
    uint16_t *xm_regs;

    switch (reg) {
        case XM_SYS_CTRL:
        case XM_INT_CTRL:
        case XM_TIMER:
        case XM_RD_XADDR:
        case XM_WR_XADDR:
        case XM_RD_INCR:
        case XM_RD_ADDR:
        case XM_WR_INCR:
        case XM_WR_ADDR:
        case XM_PIXEL_X:
        case XM_PIXEL_Y:        
            xosera->xm_regs[reg] = value;
            return;
        case XM_XDATA:
            xo_bus_write_xr_reg_16(xosera, xosera->xm_regs[XM_WR_XADDR]++, value);
            return;
        case XM_DATA:
        case XM_DATA_2:
            xm_regs = xosera->xm_regs;
            xo_vram_write(xosera->vram, xm_regs[XM_WR_ADDR], value);
            xm_regs[XM_WR_ADDR] += xm_regs[XM_WR_INCR];
            return;
        case XM_UART:
            DEBUGF("WARN: Write to unimplemented XM register 0x%04x\n", reg);
            return;
        case XM_FEATURE:
            DEBUGF("WARN: Write to read-only XM register 0x%04x\n", reg);
            return;
    }
}
