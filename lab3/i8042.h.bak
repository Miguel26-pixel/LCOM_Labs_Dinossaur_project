//Initializing the 8042 Keyboard Controller
#define STATUS_PORT  0x64
#define KBD_OUT_BUF  0x60
#define KBD_INPT_BUF  0x60
#define KBD_CMD_BUF  0x64
#define KBD_DATA_BUF  0x60
#define PORT_A  0x60
#define PORT_B  0x61
#define OUT_BUF_FULL  0x01
#define INPT_BUF_FULL  0x02
#define SYS_FLAG  0x04
#define CMD_DATA  0x08
#define KEYBD_IN  0x10
#define TRANS_TMOUT  0x20
#define RCV_TMOUT  0x40
#define PARITY_EVEN  0x80
#define IN_KEYBOARD  0x10
#define KBD_ENA  0xAE
#define KBD_DIS  0xAD
#define ESC_KEY_BREAK 0x81
#define KBC_ST_REG 0x64
#define KBC_CMD_REG 0x64
#define KBC_OUT_BUF 0x60

//Keyboard Commands
#define KB_MENU  0xF1
#define KB_ENABLE  0xF4
#define KB_MAKEBREAK  0xF7
#define KB_ECO  0xFE
#define KB_RESET  0xFF
#define KB_LED_CMD  0xED

//Keyboard responses
#define KB_OK  0xAA
#define KB_ACK  0xFA
#define KB_OVERRUN  0xFF
#define KB_RESEND  0xFE
#define KB_BREAK  0xF0
#define KB_FA  0x10
#define KB_FE  0x20

//static variables
#define FIRST_PART_OF_2_BYTES 0xE0
#define KBC_IRQ1 1 
#define TIMER0_IRQ 0 /* @brief Timer 0 IRQ line */

#include <minix/sysutil.h>

#define DELAY_US    20000
