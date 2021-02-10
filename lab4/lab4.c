// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>
#include "timer.h"
#include "mouse.h"


extern int mouse_hook_id;

extern bool complete;

uint32_t counter = 0;

uint8_t def_count=0;

struct packet pp;

uint8_t count = 0;

extern int past_time;

int read_state=0;

uint8_t sum_x = 0;


int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need/ it]
  lcf_trace_calls("/home/lcom/labs/g05/lab4/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/g05/lab4/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}


int (mouse_test_packet)(uint32_t cnt) {
	
	int r;
    message msg;
	int ipc_status;
    uint8_t mouse_bit_no = 1;
	
	mouse_enable_data_reporting();
	
	mouse_subscribe_int(&mouse_bit_no);
    //if (mouse_enable_report()==1) return 1;

    while (counter!=cnt) {                                                            //the input to stop is the esc key
        //printf("%d",counter);
        if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
            printf("driver_receive failed with: %d", r);
            continue;
        }

        if (is_ipc_notify(ipc_status)) {                            /* received notification */
            switch (_ENDPOINT_P(msg.m_source)) {
                case HARDWARE:                                      /* hardware interrupt notification */				
                    if (msg.m_notify.interrupts & mouse_bit_no) {    /* subscribed interrupt */
                        mouse_ih(); 
                         //printf("%d",complete);
                        if (complete){
							mouse_print_packet(&pp);
							complete = false;
							pp.bytes[0]=0;
							pp.bytes[1]=0;
							pp.bytes[2]=0;
							pp.lb = 0;
							pp.rb = 0;
							pp.mb = 0;
							pp.x_ov = 0;
							pp.y_ov = 0;
							counter++;
							count = 0;
                        } 
                    }
                    break;
                default:
                    break;                                          /* no other notifications expected: do nothing */	
            }
            //tickdelay(micros_to_ticks(DELAY_US));
        } 
    }   

    mouse_unsubscribe_int();
    if (mouse_disable_report()==1) return 1;
    return 0;
}

int (mouse_test_async)(uint8_t idle_time) {
    int r;
    message msg;
	int ipc_status;
    uint8_t mouse_bit_no = 2;
    uint8_t timer_bit_no = 0;

    timer_subscribe_int(&timer_bit_no);
	
	mouse_enable_data_reporting();
	
	mouse_subscribe_int(&mouse_bit_no);
    //if (mouse_enable_report()==1) return 1;


    do{                                                            //the input to stop is the esc key
        
        if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
            printf("driver_receive failed with: %d", r);
            continue;
        }

        if (is_ipc_notify(ipc_status)) {                            /* received notification */
            switch (_ENDPOINT_P(msg.m_source)) {
                case HARDWARE:                                      /* hardware interrupt notification */	
                    if (msg.m_notify.interrupts & timer_bit_no)	{
                        timer_int_handler();
                    }		
                    if (msg.m_notify.interrupts & mouse_bit_no) {    /* subscribed interrupt */
                        past_time=0;
                        mouse_ih(); 
                        if (complete){
							mouse_print_packet(&pp);
							complete = false;
							pp.bytes[0]=0;
							pp.bytes[1]=0;
							pp.bytes[2]=0;
							pp.lb = 0;
							pp.rb = 0;
							pp.mb = 0;
							pp.x_ov = 0;
							pp.y_ov = 0;
							counter++;
							count = 0;
                        } 
                    }
                    break;
                default:
                    break;                                          /* no other notifications expected: do nothing */	
            }
            //tickdelay(micros_to_ticks(DELAY_US));
        } 
    }while ((past_time/sys_hz())<idle_time) ;   

    timer_unsubscribe_int();
    mouse_unsubscribe_int();
    if (mouse_disable_report()) return 1;
    return 0;
}


int (mouse_test_gesture)(uint8_t x_len, uint8_t tolerance) {
    int r;
    message msg;
	int ipc_status;
    uint8_t mouse_bit_no = 2;
    printf("%d",read_state);
    mouse_enable_data_reporting();
	
	mouse_subscribe_int(&mouse_bit_no);

    while (read_state!=3){                                                            //the input to stop is the esc key
        
        if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
            printf("driver_receive failed with: %d", r);
            continue;
        }

        if (is_ipc_notify(ipc_status)) {                            /* received notification */
            switch (_ENDPOINT_P(msg.m_source)) {
                case HARDWARE:                                      /* hardware interrupt notification */		
                    if (msg.m_notify.interrupts & mouse_bit_no) {    /* subscribed interrupt */
                        mouse_ih(); 
                        if (complete){
							mouse_print_packet(&pp);
                            //printf("%d",read_state);
                            //state_ih(x_len,tolerance);
							complete = false;
							pp.bytes[0]=0;
							pp.bytes[1]=0;
							pp.bytes[2]=0;
							pp.lb = 0;
							pp.rb = 0;
							pp.mb = 0;
							pp.x_ov = 0;
							pp.y_ov = 0;
							count = 0;
                        } 
                    }
                    break;
                default:
                    break;                                          /* no other notifications expected: do nothing */	
            }
            //tickdelay(micros_to_ticks(DELAY_US));
        } 

    }
    mouse_unsubscribe_int();
    if (mouse_disable_report()) return 1;
    return 0;
}

int (mouse_test_remote)(uint16_t period, uint8_t cnt) {
    /* To be completed */
    printf("%s(%u, %u): under construction\n", __func__, period, cnt);
    return 1;
}
