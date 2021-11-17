#ifndef __TRANS_GATEWAY_H__c
#define __TRANS_GATEWAY_H__c

#include "common.h"
#include "BufferedSerial.h"
#include "Queue.h"
#include "ConditionVariable.h"
#include "IService.h"

#define DEFAULT_BAUD 115200
#define QUEUE_MAX_LEN 3

class TransGateway {

public:
    virtual ~TransGateway();
    static TransGateway* get_instance(void);
    void uart_recv(void);
    void uart_handler(void);

private:
    explicit TransGateway();
    static TransGateway* instance;
    mbed::BufferedSerial serial_uart;
    rtos::Queue<rab_os_msg, QUEUE_MAX_LEN> msg_queue;
    rtos::Mutex mutex_queue;
    rtos::ConditionVariable cond_queue;
    IService *service;
};

#endif