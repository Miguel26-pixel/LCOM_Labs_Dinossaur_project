#include <lcom/lcf.h>
#include <stdbool.h>
#include <stdint.h>
#include <minix/sysutil.h>

#include "keyboard.h"
#include "i8042.h"

extern int cnt;

uint8_t scancode = 0x00; //scancode initialized

uint8_t scan_array[2]; //array of scans, used when the scancode has more than 8 bits

bool complete = false;

uint8_t size = 0;

extern int kbc_hook_id;

extern int timer_hook_id;

extern int past_time;

int main(int argc, char* argv[]) {
    // sets the language of LCF messages (can be either EN-US or PT-PT)
    lcf_set_language("EN-US");

    // enables to log function invocations that are being "wrapped" by LCF
    // [comment this out if you don't want/need it]
    lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

    // enables to save the output of printf function calls on a file
    // [comment this out if you don't want/need it]
    lcf_log_output("/home/lcom/labs/lab3/output.txt");

    // handles control over to LCF
    // [LCF handles command line arguments and invokes the right function]
    if (lcf_start(argc, argv))
        return 1;

    // LCF clean up tasks
    // [must be the last statement before return]
    lcf_cleanup();

    return 0;
}

int(kbd_test_scan)() {                                             //print of scancode or breakcode

    int ipc_status;
    message msg;
    uint8_t kbc_bit_no = 1;
    kbc_subscribe_int(&kbc_bit_no);

    do {                                                            //the input to stop is the esc key
        int r;
        if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
            printf("driver_receive failed with: %d", r);
            continue;
        }

        if (is_ipc_notify(ipc_status)) {                            /* received notification */
            switch (_ENDPOINT_P(msg.m_source)) {
                case HARDWARE:                                      /* hardware interrupt notification */				
                    if (msg.m_notify.interrupts & kbc_bit_no) {    /* subscribed interrupt */
                       kbc_ih(); 
                       if (complete){
                            bool make = !(scan_array[1] & 0x80);
                            if (scan_array[0] != 0)
                                size = 2;
                            else {
                                size = 1;
                                scan_array[0] = scan_array[1];
                            }
                            kbd_print_scancode(make, size, scan_array);
                            complete = false;
                            scan_array[0]=0;
                            scan_array[1]=0;
                        }  
                    }
                    break;
                default:
                    break;                                          /* no other notifications expected: do nothing */	
            }
        } 
    }    
    while(scancode != ESC_KEY_BREAK); 
    
    kbd_print_no_sysinb(cnt);
    cnt = 0;
    kbc_unsubscribe_int();
    return 0;
}

int(kbd_test_poll)() {

    uint8_t cmd_reg = 0x00;                     //its gonna save the last cmd
    sys_outb(STATUS_PORT,TRANS_TMOUT);          //comand to read
    util_sys_inb(KBD_OUT_BUF, &cmd_reg);         //read
    cmd_reg = cmd_reg & 0xFC;                   //disables the interrupts
    sys_outb(STATUS_PORT,RCV_TMOUT);            //comand to write
    sys_outb(KBD_OUT_BUF,cmd_reg);              //writes

    uint8_t stat = 0x00;
    uint8_t data = 0x00;

    while( 1 ) {
        if (util_sys_inb(KBC_ST_REG, &stat) != 0){
            printf("Reading Error.");
        }; 
        /* loop while 8042 output buffer is empty */
        if( (stat & 0x01) != 0 && (stat & 0x20) == 0){     //verify if the OBF and the AUS bytes are correct
            if (util_sys_inb(KBC_OUT_BUF, &data) != 0){
                printf("Reading Error.");
            };
            
            if ( (stat & (PARITY_EVEN | RCV_TMOUT)) != 0 )  //sees if there is some error 
                return -1;
            else{
                kbc_read_data(data);
                if (complete){
                    bool make = !(scan_array[1] & 0x80);

                    if (scan_array[0] != 0)
                        size = 2;
                    else {size = 1;
                        scan_array[0] = scan_array[1];
                    }
                    
                    printf("scan: %d",scan_array[1]);
                    kbd_print_scancode(make, size,scan_array);
                    complete = false;
                    scan_array[0]=0;
                    scan_array[1]=0;
                }
                if (data == ESC_KEY_BREAK){
                    break;
                    printf("omg");
                }
            }

            tickdelay(micros_to_ticks(DELAY_US)); // e.g. tickdelay()          
        }
    }

    sys_outb(STATUS_PORT,TRANS_TMOUT);     //comand to read
    util_sys_inb(KBD_OUT_BUF,&cmd_reg);    //read
    cmd_reg = cmd_reg | 0x03;              //disables the interrupts
    sys_outb(STATUS_PORT,RCV_TMOUT);       //comand to write
    sys_outb(KBD_OUT_BUF,cmd_reg);         //writes
    kbd_print_no_sysinb(cnt);
    cnt = 0;

    return 0;
}

int(kbd_test_timed_scan)(uint8_t n) {
    int ipc_status;
    uint8_t data = 0;
    message msg;
    uint8_t kbc_bit_no = 1;
    kbc_subscribe_int(&kbc_bit_no);
    uint8_t timer_bit_no = 0;
    timer_subscribe_int(&timer_bit_no);
    do{
        int r;
        if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
            printf("driver_receive failed with: %d", r);
            continue;
        }
        if (is_ipc_notify(ipc_status)) {
            switch (_ENDPOINT_P(msg.m_source)) {
                case HARDWARE: /* hardware interrupt notification */
                    if (msg.m_notify.interrupts & timer_bit_no) { // Timer0 int?
                        timer_int_handler();
                    }
                    if (msg.m_notify.interrupts & kbc_bit_no) { // KBD int?
                        past_time=0;
                        kbc_ih();
                        if (complete){
                            bool make = !(scan_array[1] & 0x80);
                            if (scan_array[0] != 0)
                                size = 2;
                            else {
                                size = 1;
                                scan_array[0] = scan_array[1];
                            }
                            kbd_print_scancode(make, size, scan_array);
                            complete = false;
                            scan_array[0]=0;
                            scan_array[1]=0;
                        }
                    }
                    break;
                default:
                    break; /* no other notifications expected: do nothing */
                }
        }
    }
    while (data != ESC_KEY_BREAK && (past_time/60)<n );
    kbd_print_no_sysinb(cnt);
    cnt = 0;
    kbc_unsubscribe_int();
    timer_unsubscribe_int();
    return 0;
}



