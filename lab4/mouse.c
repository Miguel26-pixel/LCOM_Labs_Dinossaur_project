#include <lcom/lcf.h>
//#include "keyboard.h"
#include "mouse.h"
#include "i8042.h"

int mouse_hook_id = 2;

uint8_t mouse_scan =0;

bool complete = false;

extern int counter;

extern struct packet pp;

extern uint8_t count;

bool ltb,rtb= false;

extern int read_state;

extern uint8_t sum_x;

int (mouse_enable_report)(){
	uint8_t m = 0;
	sys_outb(KBC_CMD_REG,CMD_2_WRITE_MOUSE);
	sys_outb(KBC_OUT_BUF,CMD_ENABLE_MOUSE);
	util_sys_inb(KBC_OUT_BUF,&m);
	if(m == 0xFA) return 0;
	return 1;
}

int (mouse_subscribe_int)(uint8_t *mouse_bit_no) {
  
  *mouse_bit_no = BIT(mouse_hook_id);
  sys_irqsetpolicy(MOUSE_IRQ, IRQ_REENABLE|IRQ_EXCLUSIVE, &mouse_hook_id);
  return 0;
}

int (mouse_unsubscribe_int)() {

  sys_irqrmpolicy(&mouse_hook_id);

  return 1;
}

bool (left_button)() {
	return pp.bytes[0] & BIT(0);
}

bool (right_button)() {
	return pp.bytes[0] & BIT(1);
}

bool (middle_button)() {
	return pp.bytes[0] & BIT(2);
}

bool (deltaX)(uint8_t tolerance){
	return abs(pp.delta_x)>tolerance && abs(pp.delta_x)>1;
}

bool (deltaY)(uint8_t tolerance){
	if(ltb)
		return abs(pp.delta_y)<tolerance;
	else
		return abs(pp.delta_x)<tolerance;	
}

bool (slope)(){
	if(ltb)
		return pp.delta_y/pp.delta_x >1;
	else
		return pp.delta_y/pp.delta_x <-1;
}

bool (left_state_func)(uint8_t x_len, uint8_t tolerance){
	if(!ltb && left_button() && !right_button() && !middle_button())
		ltb = true;
	if(left_button() && !right_button() && !middle_button() && deltaY(tolerance) && deltaX(tolerance) && slope()){
		sum_x += pp.delta_x;
		return true;
	}
	if(ltb && !left_button()&& !right_button() && !middle_button() && sum_x >= x_len)	{
		sum_x=0;
		ltb = false;
		read_state++;
		return true;
	}
	return false;
}

bool (middle_state_func)(uint8_t x_len,uint8_t tolerance){
	if(!rtb && !ltb && !left_button() && right_button() && !middle_button())	{
		rtb = true;
		read_state++;
		return true;
	}
	if(!rtb && !ltb && !left_button() && !right_button() && !middle_button() && deltaY(tolerance) && deltaX(tolerance))
		return true;
	return false;
}

bool (right_state_func)(uint8_t x_len, uint8_t tolerance){
	if(!left_button() && right_button() && !middle_button() && deltaY(tolerance) && deltaX(tolerance) && slope()){
		sum_x+= x_len;
		return true;
	}
	if(rtb && !left_button() && !right_button() && !middle_button() && sum_x>=x_len)	{
		sum_x=0;
		rtb = false;
		read_state++;
		return true;
	}
	return false;
}

void state_ih(uint8_t x_len,uint8_t tolerance){
	printf("%d",read_state);
	switch (read_state){
		case 0:
			if(!left_state_func(x_len,tolerance)){
				read_state=0;
			}
		case 1:
			if(!middle_state_func(x_len,tolerance))
				read_state=0;
		case 2:
			if(!right_state_func(x_len,tolerance))
				read_state=0;
	}
}

void (mouse_read_byte)(uint8_t mouse_scan){
	
	//if(!(mouse_scan & BIT_3_FIRST_READ)) count = 0;	
	if (count==0 && (mouse_scan & BIT_3_FIRST_READ) == 0)
		return;
	
	pp.bytes[count]=mouse_scan;
	switch (count){
	case 0:
		pp.lb = mouse_scan & BIT(0);
		pp.rb = mouse_scan & BIT(1);
		pp.mb = mouse_scan & BIT(2);
		pp.x_ov = mouse_scan & BIT(6);
		pp.y_ov = mouse_scan & BIT(7);
		break;
	case 1:
		if (pp.bytes[0] & BIT(4))
			pp.delta_x= 0xFF00 | pp.bytes[1];
		else 
			pp.delta_x = pp.bytes[1];
		break;

	case 2:
		complete = true;
		if (pp.bytes[0] & BIT(5))
			pp.delta_y = 0xFF00 | pp.bytes[2];
		else 
			pp.delta_y = pp.bytes[2];
		break;
	}
	
	count++;
	
}


void (mouse_ih)(){

	uint8_t status = 0;

	util_sys_inb(STATUS_PORT, &status);
	util_sys_inb(KBD_OUT_BUF, &mouse_scan);
	
	if ((status & (OUT_BUF_FULL | AUX_BIT)) == (OUT_BUF_FULL | AUX_BIT)) {
		if (status & (PARITY_EVEN | RCV_TMOUT)) 
			return;

		mouse_read_byte(mouse_scan);
	}
}


int (mouse_disable_report)(){
	uint8_t m = 0;
	sys_outb(KBC_CMD_REG,CMD_2_WRITE_MOUSE);
	sys_outb(KBC_OUT_BUF,CMD_DISABLE_MOUSE);
	util_sys_inb(KBC_OUT_BUF,&m);
	if(m == 0xFA) return 0;
	return 1;
}
