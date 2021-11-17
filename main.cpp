#include "trans_gateway.h"
#include "rtos.h"

int main()
{
    Thread trans_recv_thread, trans_hand_thread;
    TransGateway *trans_gate = TransGateway::get_instance();

    if(NULL != trans_gate) {
        trans_recv_thread.start([&] {
            trans_gate->uart_recv();
        });

        trans_hand_thread.start([&] {
            trans_gate->uart_handler();
        });
    }
    else 
        exit(0);
    while(1) {
        ThisThread::sleep_for(100);
    }

}

