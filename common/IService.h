#ifndef __ISERVICE_H__
#define __ISERVICE_H__

#include "common.h"

class IService {
public:
    virtual ~IService() {};
    virtual void handle_request(rab_os_msg* msg) = 0;
};

#endif