#ifndef __COMMON_H__
#define __COMMON_H__

#include "stdint.h"
#include <cstdint>
#include "cstring"

#define RAB_OS_SOP          0xBB
#define RAB_OS_EOP          0x55

#define RAB_OS_SOP_OFF      0
#define RAB_OS_CMD_OFF      1  
#define RAB_OS_LEN_OFF      2

#define MAX_BUFF_LEN 16

typedef enum {
    CMD_TOGGLE_RED_RGB          = 0x1A,
    CMD_TOGGLE_BLUE_RGB         = 0x1B,
    CMD_TOGGLE_GREEN_RGB        = 0x1C,
    CMD_TOGGLE_ALL_RGB          = 0x1D,

} RAB_CMD;

typedef struct _rab_os_msg {
    uint8_t cmd_id;
    uint32_t pkg_len;
    uint8_t data[MAX_BUFF_LEN];

    _rab_os_msg() {
        memset(this, 0, sizeof(_rab_os_msg));
    }

    _rab_os_msg(uint8_t cmd, uint32_t len, uint8_t* da) {
        _rab_os_msg();
        cmd_id = cmd;
        pkg_len = len > MAX_BUFF_LEN ? MAX_BUFF_LEN : len;
        std::memcpy(data, da, len);
    }
} rab_os_msg;
#endif