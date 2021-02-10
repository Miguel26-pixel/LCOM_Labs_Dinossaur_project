#include <stdint.h>
#include <stdio.h>
#include <minix/drivers.h>

#include "rtc.h"


int rtc_hook_id = RTC_IRQ;
int delta_x_meteor=3,delta_y_meteor=1, delta_bird=5, delta_cactus=5;

int rtc_write_cmd(uint8_t reg){
    
    if(sys_outb(RTC_ADDR_REG, reg) != OK) 
        return 1; 

    else
        return OK;
}

int rtc_read_cmd(uint8_t *data){
    
    if(util_sys_inb(RTC_ADDR_REG, data) != OK) 
        return 1; 

    else
        return OK;
}


int rtc_reg_data(uint8_t reg, uint8_t *data){

  sys_outb(RTC_ADDR_REG,reg); 

  util_sys_inb(RTC_DATA_REG,data);
  return 1;
}

int rtc_year(){
  uint8_t year;
  rtc_reg_data(RTC_YEAR,&year);
  return year;
}

int rtc_month(){
  uint8_t month;
  rtc_reg_data(RTC_MONTH,&month);
  return month;
}

int rtc_day(){
  uint8_t day;
  rtc_reg_data(RTC_DAYOFMONTH,&day);
  return day;
}

int rtc_hour(){
  uint8_t hour;
  rtc_reg_data(RTC_HOURS,&hour);
  return hour;
}

int rtc_minute(){
  uint8_t minute;
  rtc_reg_data(RTC_MINUTES,&minute);
  return minute;
}

int rtc_second(){
  uint8_t seconds;
  rtc_reg_data(RTC_SECONDS,&seconds);
  return seconds;
}

void char_date(char *date){

    uint8_t year, month, day;

    day = rtc_day();
 
    month = rtc_month();

    year = rtc_year();

    sprintf(date, "%02x %02x 20%02x", day, month, year);
}

void rtc_subscribe(uint8_t *rtc_bit_no) {

	*rtc_bit_no = BIT(rtc_hook_id);

	unsigned char regC;
	sys_outb(RTC_ADDR_REG, RTC_REG_C);
	util_sys_inb(RTC_DATA_REG, &regC);	

	printf("%x",regC);


	if(sys_irqsetpolicy(RTC_IRQ, IRQ_REENABLE, &rtc_hook_id) != OK) {
		printf("RTC: subscribe: couldn't set policy\n");
		return;
	}
}


void rtc_unsubscribe() { 
    if(sys_irqdisable(&rtc_hook_id) != OK) {
    	printf("RTC: unsubscribe: couldn't disable interrupts\n");
    	return;
    }
}

