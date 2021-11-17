#include "trans_gateway.h"
#include "misc_service.h"
#include <cstdint>
#include <cstdio>
#include <new>
#include "rtos.h"

TransGateway::TransGateway() : serial_uart(USBTX, USBRX, DEFAULT_BAUD), 
    cond_queue(mutex_queue) {
    instance = NULL;
}

TransGateway::~TransGateway() {
    delete instance;
    delete service;
}

TransGateway* TransGateway::instance = NULL;

TransGateway* TransGateway::get_instance(void) {
    if(NULL == instance) {
        instance = new (std::nothrow)TransGateway;
        if(NULL == instance) {
            printf("Error when creating TransGateway instance\n");
        }
    }

    return instance;
}

void TransGateway::uart_recv(void) {
    uint32_t read_len = 0;
    uint8_t read_buff[MAX_BUFF_LEN] = {0};

    while(1) {
        memset(read_buff, 0, MAX_BUFF_LEN);
        read_len = serial_uart.read(read_buff, MAX_BUFF_LEN);
        if(read_len) {
            if(read_buff[RAB_OS_SOP_OFF] == RAB_OS_SOP 
                && read_buff[read_len - 1] == RAB_OS_EOP){
                    
                uint8_t data[MAX_BUFF_LEN - 4] = {0};
                uint32_t data_len = read_buff[RAB_OS_LEN_OFF];
                uint8_t cmd_id = read_buff[RAB_OS_CMD_OFF];

                memcpy(data, read_buff + 3, data_len);

                rab_os_msg *os_msg = new rab_os_msg(cmd_id, data_len, data);

                mutex_queue.lock();
                msg_queue.put(os_msg);
                cond_queue.notify_one();
                mutex_queue.unlock();
            }

            serial_uart.sync();
        }
    }
}

void TransGateway::uart_handler(void) {
    while(1) {
        mutex_queue.lock();
        if(msg_queue.empty()) {
            cond_queue.wait();
        }

        rab_os_msg *msg = (rab_os_msg*)msg_queue.get().value.p;

        mutex_queue.unlock();

        switch (msg->cmd_id) {
            case CMD_TOGGLE_RED_RGB:
            case CMD_TOGGLE_BLUE_RGB:
            case CMD_TOGGLE_GREEN_RGB:
            case CMD_TOGGLE_ALL_RGB:
                service = static_cast<MiscService*>(MiscService::get_instance());
                service->handle_request(msg);
                break;

            default:
                break;
        }

        ThisThread::sleep_for(100);
    }
}
