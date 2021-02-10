#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>
#include <stdio.h>
#include "i8254.h"

int hook_id;

extern int past_time;

int (timer_set_frequency)(uint8_t timer, uint32_t freq) { //imensas duvidas neste
  uint8_t control_word = 0x30; // inicializar a control_word com LSB + MSB
  
  uint8_t where = 0x00; //registos para escrita de valores dos counters

  uint8_t st;

  uint8_t lsb_or_msb;

  //verifica se nao ha valores q n deviam
  if (!(timer == 0 || timer == 1 || timer == 2)) {
     return 1;
  }
  if (freq <= 0)
    return 1;

  timer_get_conf(timer, &st); //le os valores atuais


  uint16_t div = TIMER_FREQ / freq;  // onde e q ponho este valor?? valor inicial do timer

  //regista em qual timer estamos
  if (timer == 0) {
    where = 0x40;
  } 
  else if (timer == 1) {
    control_word = control_word | 0x40;
    where = 0x41;
  }
  else {
    control_word = control_word | 0x80;
    where = 0x42;
  }

  control_word = control_word | 0x30; //e para por a ler com MSB_LSB

  uint8_t st2 = st & 0x0F;

  control_word = control_word | st2; //os primeiros 4 bits tem de ser iguais


  sys_outb(TIMER_CTRL, control_word); //bons comentarios miguel

  util_get_LSB(div, &lsb_or_msb);
  sys_outb(where, lsb_or_msb);

  util_get_MSB(div, &lsb_or_msb);
  sys_outb(where, lsb_or_msb);

  return 0;
}

int (timer_subscribe_int)(uint8_t *bit_no) {
	
  hook_id = *bit_no;

  sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &hook_id);

  return 0;
}

int (timer_unsubscribe_int)() {
  
  sys_irqrmpolicy(&hook_id);

  return 0;
}

void (timer_int_handler)() {
  
  past_time++;  
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  uint8_t read_back_command = 0x00; //inicializar o read_back_command
  
  //tipo de timer , bits correspondentes ao tipo de timer , ver na tabela
  read_back_command = TIMER_RB_CMD | TIMER_RB_COUNT_ | BIT(timer + 1);

  if (sys_outb(TIMER_CTRL, read_back_command) != OK) {
    printf("ERROR in sys_outb()\n");
    return 1;
  }
  if (timer == 0)
    util_sys_inb(TIMER_0, st);
  else if (timer == 1)
    util_sys_inb(TIMER_1, st);         //ler os novos valores e manda-lo para o st
  else if (timer == 2)
    util_sys_inb(TIMER_2, st);


  return 0;
}

/*print*/

int(timer_display_conf)(uint8_t timer, uint8_t st, enum timer_status_field field) {
  
  union timer_status_field_val conf; //inicializar o conf
  
  switch (field) {  //verificar o q esta presente nop field , o argumento

    case tsf_all:
      conf.byte = st;
      break;

    case tsf_mode:
      conf.count_mode = (st & 0x0E) >> 1;
      if (conf.count_mode == 7)
        conf.count_mode = 3;
      else if (conf.count_mode == 6)
        conf.count_mode = 2;
      break;

    case tsf_initial: 
      conf.in_mode = (st & 0x30) >> 4;
      if (conf.in_mode == 1)
        conf.in_mode = LSB_only;
      else if (conf.in_mode == 2)
        conf.in_mode = MSB_only;
      else if (conf.in_mode == 3)
        conf.in_mode = MSB_after_LSB;
      else conf.in_mode = INVAL_val;
      break;

    case tsf_base:  
        conf.bcd= st & 0x01;
        break;

  }
  timer_print_config(timer, field, conf); //funcao dada para printar melhor


  return 1;
}
