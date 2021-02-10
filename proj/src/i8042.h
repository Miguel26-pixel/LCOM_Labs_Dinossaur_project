#include <minix/sysutil.h>

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
#define MOUSE_IRQ 12
#define CMD_2_WRITE_MOUSE 0xD4
#define CMD_ENABLE_MOUSE 0xF4
#define CMD_DISABLE_MOUSE 0xF5
#define AUX_BIT 0x20
#define BIT_3_FIRST_READ BIT(3)
#define ENTER_BREAK 0x9C




#define DELAY_US    20000

//Scancodes
#define ESC_KEY 0x81

//Colors
#define WHITE 0xffffffff
#define BLACK 0


//alpha
#define A  0x1E
#define B  0x30
#define C  0x2E
#define D  0x20
#define E  0x12
#define F  0x21
#define G  0x22
#define H  0x23
#define I  0x17
#define J  0x24
#define K  0x25
#define L  0x26
#define M  0x32
#define N  0x31
#define O  0x18
#define P  0x19
#define Q  0x10
#define R  0x13
#define S  0x1F
#define T  0x14
#define U  0x16
#define V  0x2F
#define W  0x11
#define X  0x2D
#define Y  0x15
#define Z  0x2C
#define SPACE 0x39



//RTC
#define RTC_IRQ             8

#define RTC_ADDR_REG        0x70
#define RTC_DATA_REG        0x71 

#define RTC_SECONDS 	    	0   
#define RTC_MINUTES 	    	2   
#define RTC_HOURS 		    	4   
#define RTC_DAYOFWEEK 	    6   
#define RTC_DAYOFMONTH      7   
#define RTC_MONTH			      8   
#define RTC_YEAR			      9

#define PERIODIC_INTERRUPT_ENABLE   BIT(6)

#define RTC_REG_A	    	    10
#define RTC_REG_B		        11
#define RTC_REG_C	         	12
#define RTC_REG_D	         	13

#define RTC_UIP             BIT(7)
#define RTC_PF              BIT(6)
