#include "misc_service.h"
#include <new>
#include "stdio.h"

MiscService::MiscService() : red_rgb(RED_RGB_PIN), 
    blue_rgb(BLUE_RGB_PIN), green_rgb(GREEN_RGB_PIN) {

    red_rgb.write(red_rgb_val);
    blue_rgb.write(blue_rgb_val);
    green_rgb.write(green_rgb_val);
}

MiscService::~MiscService() {
    delete instance;
}

MiscService* MiscService::instance = NULL;

MiscService* MiscService::get_instance(void) {
    if(NULL == instance) {
        instance = new (std::nothrow)MiscService;
        if(NULL == instance) {
            printf("Cannot create MiscService instance\n");
        }
    }

    return instance;
}

void MiscService::handle_request(rab_os_msg *msg){
    switch (msg->cmd_id) {
        case CMD_TOGGLE_RED_RGB:
            red_rgb.write(red_rgb_val = !red_rgb_val);
            blue_rgb.write(0);
            green_rgb.write(0);
            break;
        case CMD_TOGGLE_BLUE_RGB:
            blue_rgb.write(blue_rgb_val = !blue_rgb_val);
            red_rgb.write(0);
            green_rgb.write(0);
            break;
        case CMD_TOGGLE_GREEN_RGB:
            green_rgb.write(green_rgb_val = !green_rgb_val);
            red_rgb.write(0);
            blue_rgb.write(0);
            break;

        default:
            break;
    }

    delete msg;
}