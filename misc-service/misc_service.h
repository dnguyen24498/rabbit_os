#ifndef __MISC_SERVICE_H__
#define __MISC_SERVICE_H__

#include "IService.h"
#include "DigitalOut.h"

#define RED_RGB_PIN     PA_0
#define BLUE_RGB_PIN    PA_6
#define GREEN_RGB_PIN   PA_7

class MiscService : public IService {
public:
    virtual ~MiscService();
    static MiscService* get_instance(void);
    virtual void handle_request(rab_os_msg* msg) override;

private:
    explicit MiscService();
    static MiscService* instance;
    mbed::DigitalOut red_rgb;
    mbed::DigitalOut blue_rgb;
    mbed::DigitalOut green_rgb;
    bool red_rgb_val = 0;
    bool blue_rgb_val = 0;
    bool green_rgb_val = 0;
};

#endif