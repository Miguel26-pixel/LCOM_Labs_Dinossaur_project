#include "sprite.h"
#include <time.h>                // For time
#include <stdlib.h>                // For rand();

extern uint8_t scancode;
extern int past_time;
extern int past_counter;
enum xpm_image_type type = XPM_5_6_5;
extern uint8_t kbc_bit_no;
extern uint8_t timer_bit_no;
int cnt=0;
int counter_dispawn=0, counter_meteor = 0, counter_dis_meteor = 0, counter_spawn = 0, bird_spawn =0, bird_dispawn=0;
bool jump_down= false, jump_up= false,crouch= false,fix_image= false,menu_complete=false;
bool nick_complete=false, n_record=false, show_record=false;
extern bool complete;
extern struct packet pp;
extern int count;
extern int counter;
int count_name=0;
int cactus_x[200000]={0};
int meteor_x[200000]={0};
int meteor_y[200000]={0};
int bird_x[200000]={0};
char nick[6] = {"\0"} ;
extern User* high[3];
extern int high_sc[3];
bool bird_orientation[200000]={false};
int temp_y=415;
int temp_x=20;
long int score_no =0;
extern int actual_mouse_x;
extern int actual_mouse_y;
extern int delta_x_meteor,delta_y_meteor, delta_bird, delta_cactus;

Sprite *create_sprite(int x, int y,int xspeed, int yspeed, int width, int height,uint8_t *pixel_pointer,xpm_image_t image){
  Sprite *s = (Sprite *) malloc ( sizeof(Sprite));
  s->x=x;
  s->y=y;
  s->xspeed=xspeed;
  s->yspeed=yspeed;
  s->width=width;
  s->height=height;
  s->pixel_pointer=pixel_pointer;
  s->image = image;
  return s;
}

void destroy_sprite(Sprite *sp) {
  if( sp == NULL )
    return;
  free(sp);
  sp = NULL; 
}

void destroy_all(Sprite *cactus,Sprite *meteor,Sprite *cursor,Sprite *game_over,Sprite *dino_normal,Sprite *right_down,Sprite *left_down,Sprite *right,Sprite *left,Sprite *zero,Sprite *one,Sprite *two,Sprite *three,Sprite *four,Sprite *five,Sprite *six,Sprite *seven,Sprite *eight,Sprite *nine){
  destroy_sprite(cactus);
  destroy_sprite(meteor);
  destroy_sprite(cursor);
  destroy_sprite(game_over);
  destroy_sprite(dino_normal);
  destroy_sprite(right_down);
  destroy_sprite(left_down);
  destroy_sprite(right);
  destroy_sprite(zero);
  destroy_sprite(one);
  destroy_sprite(two);
  destroy_sprite(three);
  destroy_sprite(four);
  destroy_sprite(five);
  destroy_sprite(six);
  destroy_sprite(seven);
  destroy_sprite(eight);
  destroy_sprite(nine);
}


int write_text_on_screen(char text[], int xr, int yr, Sprite *a, Sprite *b, Sprite *c, Sprite *d, Sprite *e, Sprite *f, Sprite *g, Sprite *h, Sprite *i, Sprite *j, Sprite *k, Sprite *l, Sprite *m, Sprite *n, Sprite *o, Sprite *p, Sprite *q, Sprite *r, Sprite *s, Sprite *t, Sprite *u, Sprite *v, Sprite *w, Sprite *x, Sprite *y, Sprite *z, Sprite *zero, Sprite *one,Sprite *two,Sprite *three,Sprite *four,Sprite *five,Sprite *six,Sprite *seven,Sprite *eight,Sprite *nine)
{		
	for (size_t it = 0; it!=strlen(text); it++) {		
		if ((text[it] == 'a') || (text[it] == 'A')) {
			print_whitout_back(xr,yr,&a->image,a->pixel_pointer);
		}
		else if ((text[it] == 'b') || (text[it] == 'B')) {
			print_whitout_back(xr,yr,&b->image,b->pixel_pointer);
		}
		else if ((text[it] == 'c') || (text[it] == 'C')) {
			print_whitout_back(xr,yr,&c->image,c->pixel_pointer);
		}
		else if ((text[it] == 'd') || (text[it] == 'D')) {
			print_whitout_back(xr,yr,&d->image,d->pixel_pointer);
		}
		else if ((text[it] == 'e') || (text[it] == 'E')) {
			print_whitout_back(xr,yr,&e->image,e->pixel_pointer);
		}
		else if ((text[it] == 'f') || (text[it] == 'F')) {
			print_whitout_back(xr,yr,&f->image,f->pixel_pointer);
		}
		else if ((text[it] == 'g') || (text[it] == 'G')) {
			print_whitout_back(xr,yr,&g->image,g->pixel_pointer);
		}
		else if ((text[it] == 'h') || (text[it] == 'H')) {
			print_whitout_back(xr,yr,&h->image,h->pixel_pointer);
		}
		else if ((text[it] == 'i') || (text[it] == 'I')) {
			print_whitout_back(xr,yr,&i->image,i->pixel_pointer);
		}
		else if ((text[it] == 'j') || (text[it] == 'J')) {
			print_whitout_back(xr,yr,&j->image,j->pixel_pointer);
		}
		else if ((text[it] == 'k') || (text[it] == 'K')) {
			print_whitout_back(xr,yr,&k->image,k->pixel_pointer);
		}
		else if ((text[it] == 'l') || (text[it] == 'L')) {
			print_whitout_back(xr,yr,&l->image,l->pixel_pointer);
		}
		else if ((text[it] == 'm') || (text[it] == 'M')) {
			print_whitout_back(xr,yr,&m->image,m->pixel_pointer);
		}
		else if ((text[it] == 'n') || (text[it] == 'N')) {
			print_whitout_back(xr,yr,&n->image,n->pixel_pointer);
		}
		else if ((text[it] == 'o') || (text[it] == 'O')) {
			print_whitout_back(xr,yr,&o->image,o->pixel_pointer);
		}
		else if ((text[it] == 'p') || (text[it] == 'P')) {
			print_whitout_back(xr,yr,&p->image,p->pixel_pointer);
		}
		else if ((text[it] == 'q') || (text[it] == 'Q')) {
			print_whitout_back(xr,yr,&q->image,q->pixel_pointer);
		}
		else if ((text[it] == 'r') || (text[it] == 'R')) {
			print_whitout_back(xr,yr,&r->image,r->pixel_pointer);
		}
		else if ((text[it] == 's') || (text[it] == 'S')) {
			print_whitout_back(xr,yr,&s->image,s->pixel_pointer);
		}
		else if ((text[it] == 't') || (text[it] == 'T')) {
			print_whitout_back(xr,yr,&t->image,t->pixel_pointer);
		}
		else if ((text[it] == 'u') || (text[it] == 'U')) {
			print_whitout_back(xr,yr,&u->image,u->pixel_pointer);
		}
		else if ((text[it] == 'v') || (text[it] == 'V')) {
			print_whitout_back(xr,yr,&v->image,v->pixel_pointer);
		}
		else if ((text[it] == 'w') || (text[it] == 'W')) {
			print_whitout_back(xr,yr,&w->image,w->pixel_pointer);
		}
		else if ((text[it] == 'x') || (text[it] == 'X')) {
			print_whitout_back(xr,yr,&x->image,x->pixel_pointer);
		}
		else if ((text[it] == 'y') || (text[it] == 'Y')) {
			print_whitout_back(xr,yr,&y->image,y->pixel_pointer);
		}
		else if ((text[it] == 'z') || (text[it] == 'Z')) {
			print_whitout_back(xr,yr,&z->image,z->pixel_pointer);
		}
		else if (text[it] == '0') {
			print_whitout_back(xr,yr,&zero->image,zero->pixel_pointer);
		}
		else if (text[it] == '1') {
			print_whitout_back(xr,yr,&one->image,one->pixel_pointer);
		}
		else if (text[it] == '2') {
			print_whitout_back(xr,yr,&two->image,two->pixel_pointer);
		}
		else if (text[it] == '3') {
			print_whitout_back(xr,yr,&three->image,three->pixel_pointer);
		}
		else if (text[it] == '4') {
			print_whitout_back(xr,yr,&four->image,four->pixel_pointer);
		}
		else if (text[it] == '5') {
			print_whitout_back(xr,yr,&five->image,five->pixel_pointer);
		}
		else if (text[it] == '6') {
			print_whitout_back(xr,yr,&six->image,six->pixel_pointer);
		}
		else if (text[it] == '7') {
			print_whitout_back(xr,yr,&seven->image,seven->pixel_pointer);
		}
		else if (text[it] == '8') {
			print_whitout_back(xr,yr,&eight->image,eight->pixel_pointer);
		}
		else if (text[it] == '9') {
			print_whitout_back(xr,yr,&nine->image,nine->pixel_pointer);
		}
    else if(text[it] == ' '){
      xr+=15;
    }
		xr += 40;
  }
  return xr;
}

int write_int_on_screen(long int number, int xr, int yr, Sprite *zero, Sprite *one,Sprite *two,Sprite *three,Sprite *four,Sprite *five,Sprite *six,Sprite *seven,Sprite *eight,Sprite *nine)
{
  long int ni = number;
  int co=-1;
  while (ni!=0)
  {
    co++;
    ni/=10;
  }
  while (co!=-1)
  {
    ni = (number/pow(10,co)>=10) ? (int)(number/pow(10,co))%10 : (int)(number/pow(10,co));
    if (ni == 0) {
			print_whitout_back(xr,yr,&zero->image,zero->pixel_pointer);
		}
		else if (ni == 1) {
			print_whitout_back(xr,yr,&one->image,one->pixel_pointer);
		}
		else if (ni == 2) {
			print_whitout_back(xr,yr,&two->image,two->pixel_pointer);
		}
		else if (ni == 3) {
			print_whitout_back(xr,yr,&three->image,three->pixel_pointer);
		}
		else if (ni == 4) {
			print_whitout_back(xr,yr,&four->image,four->pixel_pointer);
		}
		else if (ni == 5) {
			print_whitout_back(xr,yr,&five->image,five->pixel_pointer);
		}
		else if (ni == 6) {
			print_whitout_back(xr,yr,&six->image,six->pixel_pointer);
		}
		else if (ni == 7) {
			print_whitout_back(xr,yr,&seven->image,seven->pixel_pointer);
		}
		else if (ni == 8) {
			print_whitout_back(xr,yr,&eight->image,eight->pixel_pointer);
		}
		else if (ni == 9) {
			print_whitout_back(xr,yr,&nine->image,nine->pixel_pointer);
		}
    xr+=40;
    co--;
  }
  return xr;
}

void menu_handler(Sprite *spacebar,Sprite *no_spacebar, Sprite *a, Sprite *b, Sprite *c, Sprite *d, Sprite *e, Sprite *f, Sprite *g, Sprite *h, Sprite *i, Sprite *j, Sprite *k, Sprite *l, Sprite *m, Sprite *n, Sprite *o, Sprite *p, Sprite *q, Sprite *r, Sprite *s, Sprite *t, Sprite *u, Sprite *v, Sprite *w, Sprite *x, Sprite *y, Sprite *z, Sprite *zero, Sprite *one,Sprite *two,Sprite *three,Sprite *four,Sprite *five,Sprite *six,Sprite *seven,Sprite *eight,Sprite *nine){
  if(!show_record || !nick_complete){
      if (past_time%7==0&&cnt%2==0){
          cnt++;
          setBackground();
          write_text_on_screen(nick,getHR()/2-120,200,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z, zero,one,two,three,four,five,six,seven,eight,nine);
          print_whitout_back(spacebar->x,spacebar->y,&spacebar->image,spacebar->pixel_pointer);
          PageFlipping();
      }
      else if (past_time%7==0&&cnt%2!=0){
          cnt++;
          setBackground();
          write_text_on_screen(nick,getHR()/2-120,200,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z, zero,one,two,three,four,five,six,seven,eight,nine);
          print_whitout_back(no_spacebar->x,no_spacebar->y,&no_spacebar->image,no_spacebar->pixel_pointer);
          PageFlipping();
    }
  }
  else
  {
    setBackground();
    char rec[12]={"LEADERBOARD"};
    write_text_on_screen(rec,getHR()/2-220,200,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z, zero,one,two,three,four,five,six,seven,eight,nine);
    int yr = 400;
    int xr = 20;
    char scr[6]={"SCORE"};
    write_text_on_screen(scr,xr,yr-100,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z, zero,one,two,three,four,five,six,seven,eight,nine);
    char dat[5]={"DATE"};
    write_text_on_screen(dat,xr+380,yr-100,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z, zero,one,two,three,four,five,six,seven,eight,nine);
    for (int it =0;it<3;it++)
    {
      if(high_sc[it]==0)break;
      xr = write_int_on_screen(high[it]->sc,xr,yr,zero,one,two,three,four,five,six,seven,eight,nine);
      xr += 160;
      xr = write_text_on_screen(high[it]->date,xr,yr,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z, zero,one,two,three,four,five,six,seven,eight,nine);
      yr += 60;
      xr=20;
    }
    PageFlipping();
  }
}

void jumpup(Sprite *dino_normal, Sprite *game_over){
  if(past_time/60==1/2){ 
    past_time=0;
    temp_y -= dino_normal->yspeed;
    
    if(collision(dino_normal->x,temp_y,&dino_normal->image,dino_normal->pixel_pointer)){
      if(new_record(score_no)){ n_record=true;}
      fix_image=true;
      print_whitout_back(game_over->x,game_over->y,&game_over->image,game_over->pixel_pointer);
    }

    print_whitout_back(dino_normal->x,temp_y,&dino_normal->image,dino_normal->pixel_pointer);
    if(temp_y==300){
        jump_up = false;
        jump_down = true;
    }
  }
}

void jumpdown(Sprite *dino_normal, Sprite *game_over){
  if(past_time/60==1/2){
    past_time=0;
    temp_y += dino_normal->yspeed;
    
    if(collision(dino_normal->x,temp_y,&dino_normal->image,dino_normal->pixel_pointer)){
      if(new_record(score_no)){ n_record=true;}
      fix_image=true;
      print_whitout_back(game_over->x,game_over->y,&game_over->image,game_over->pixel_pointer);
    }
    print_whitout_back(dino_normal->x,temp_y,&dino_normal->image,dino_normal->pixel_pointer);
    if(temp_y==415){
        jump_down=false;
    }
  }
}

void down(Sprite *dino_normal, Sprite *game_over, Sprite *right_down, Sprite *left_down){
  if (past_time % 2 == 0 && cnt % 2 == 0){
      cnt++;
      if(collision(right_down->x,right_down->y,&right_down->image,right_down->pixel_pointer)){
        if(new_record(score_no)){ n_record=true;}
        fix_image = true;
        print_whitout_back(game_over->x,game_over->y,&game_over->image,game_over->pixel_pointer);
      }
      print_whitout_back(right_down->x,right_down->y,&right_down->image,right_down->pixel_pointer);
  }
  else if (past_time % 2 != 0 && cnt % 2 != 0){
      cnt++;
      if(collision(left_down->x,left_down->y,&left_down->image,left_down->pixel_pointer)){
        if(new_record(score_no)){ n_record=true;}
        fix_image = true;
        print_whitout_back(game_over->x,game_over->y,&game_over->image,game_over->pixel_pointer);
      }
      print_whitout_back(left_down->x,left_down->y,&left_down->image,left_down->pixel_pointer);
  }       
}

void switch_leg(Sprite *dino_normal, Sprite *game_over, Sprite *right, Sprite *left){
  if (past_time % 2 == 0){
      cnt++;
      if(collision(dino_normal->x,temp_y,&dino_normal->image,dino_normal->pixel_pointer)){
        if(new_record(score_no)){{ n_record=true;}}
        fix_image=true;
        print_whitout_back(game_over->x,game_over->y,&game_over->image,game_over->pixel_pointer);
      }
      print_whitout_back(right->x,right->y,&right->image,right->pixel_pointer);
  }
  else if (past_time % 2 != 0){
      cnt++;
      if(collision(dino_normal->x,temp_y,&dino_normal->image,dino_normal->pixel_pointer)){
        if(new_record(score_no)){ n_record=true;}
        fix_image=true;
        print_whitout_back(game_over->x,game_over->y,&game_over->image,game_over->pixel_pointer);
      }
      print_whitout_back(left->x,left->y,&left->image,left->pixel_pointer);
  }
}

void obstacles_spawn(Sprite *cactus,Sprite *meteor, Sprite *up_bird , Sprite *down_bird){
  for (int i=bird_dispawn;i<bird_spawn;i++){
    if(bird_x[i]-20<0){
        bird_dispawn++;
    }
    else{
      if(bird_orientation[i]){
        print_whitout_back(bird_x[i]-delta_bird,down_bird->y,&down_bird->image,down_bird->pixel_pointer);
        bird_x[i]=bird_x[i]-delta_bird;
        bird_orientation[i]=false;
      }
      else{
        print_whitout_back(bird_x[i]-delta_bird,up_bird->y,&up_bird->image,up_bird->pixel_pointer);
        bird_x[i]=bird_x[i]-delta_bird;
        bird_orientation[i]=true;
      }
    }
  }
  for (int i=counter_dispawn;i<counter_spawn;i++){
    if(cactus_x[i]-10<0){
        counter_dispawn++;
    }
    else{
        print_whitout_back(cactus_x[i]-delta_cactus,cactus->y,&cactus->image,cactus->pixel_pointer);
        cactus_x[i]=cactus_x[i]-delta_cactus;
    }
  }
  for (int i=counter_dis_meteor;i<counter_meteor;i++){
    if(meteor_y[i]+50>=500 || meteor_x[i]-7<0){
        meteor_x[i]=0; 
        meteor_y[i]=0;
        counter_dis_meteor++;
    }
    else{
        meteor_x[i]=meteor_x[i]-delta_x_meteor;
        meteor_y[i]=meteor_y[i]+delta_y_meteor;
        print_whitout_back(meteor_x[i],meteor_y[i],&meteor->image,meteor->pixel_pointer);
    }
  }
  if(past_counter%100==0){
    int a = (rand()%11);
    if(a%2==0){
      print_whitout_back(cactus->x,cactus->y,&cactus->image,cactus->pixel_pointer);
      cactus_x[counter_spawn]=cactus->x; 
      counter_spawn++;
    }
    else{
      print_whitout_back(up_bird->x,up_bird->y,&up_bird->image,up_bird->pixel_pointer);
      bird_x[bird_spawn]=up_bird->x; 
      bird_orientation[bird_spawn]=true;
      bird_spawn++;
    }
  }
  if(past_counter%600==0){
    print_whitout_back(meteor->x,meteor->y,&meteor->image,meteor->pixel_pointer);
    meteor_x[counter_meteor]=meteor->x; 
    meteor_y[counter_meteor]=meteor->y; 
    counter_meteor++;
  }
}

void score(Sprite *zero, Sprite *one,Sprite *two,Sprite *three,Sprite *four,Sprite *five,Sprite *six,Sprite *seven,Sprite *eight,Sprite *nine)
{
  int s_number = score_no;
  int it=0;
  while(s_number!=0)
  {
    int digit = s_number%10;
    s_number/=10;
    switch (digit){
      case 0:
        print_whitout_back(getHR()-it*40-50,30,&zero->image,zero->pixel_pointer);
        break;
      case 1:
        print_whitout_back(getHR()-it*40-50,30,&one->image,one->pixel_pointer);
        break;
      case 2:
        print_whitout_back(getHR()-it*40-50,30,&two->image,two->pixel_pointer);
        break;
      case 3:
        print_whitout_back(getHR()-it*40-50,30,&three->image,three->pixel_pointer);
        break;
      case 4:
        print_whitout_back(getHR()-it*40-50,30,&four->image,four->pixel_pointer);
        break;
      case 5:
        print_whitout_back(getHR()-it*40-50,30,&five->image,five->pixel_pointer);
        break;
      case 6:
        print_whitout_back(getHR()-it*40-50,30,&six->image,six->pixel_pointer);
        break;
      case 7:
        print_whitout_back(getHR()-it*40-50,30,&seven->image,seven->pixel_pointer);
        break;
      case 8:
        print_whitout_back(getHR()-it*40-50,30,&eight->image,eight->pixel_pointer);
        break;
      case 9:
        print_whitout_back(getHR()-it*40-50,30,&nine->image,nine->pixel_pointer);
        break;
    }
    it++;
  }
}

void nickname(Sprite *a, Sprite *b, Sprite *c, Sprite *d, Sprite *e, Sprite *f, Sprite *g, Sprite *h, Sprite *i, Sprite *j, Sprite *k, Sprite *l, Sprite *m, Sprite *n, Sprite *o, Sprite *p, Sprite *q, Sprite *r, Sprite *s, Sprite *t, Sprite *u, Sprite *v, Sprite *w, Sprite *x, Sprite *y, Sprite *z, Sprite *zero, Sprite *one,Sprite *two,Sprite *three,Sprite *four,Sprite *five,Sprite *six,Sprite *seven,Sprite *eight,Sprite *nine)
{
    char nt[5];
		if (scancode == A) {
			strcpy(nt, "A");
			strcat(nick, nt);
			count_name++;
		}
		if (scancode == B) {
			strcpy(nt, "B");
			strcat(nick, nt);
      count_name++;
		}
		if (scancode == C) {
			strcpy(nt, "C");
			strcat(nick, nt);
      count_name++;
		}
		if (scancode == D) {
			strcpy(nt, "D");
			strcat(nick, nt);
      count_name++;
		}
		if (scancode == E) {
			strcpy(nt, "E");
			strcat(nick, nt);
      count_name++;
		}
		if (scancode == F) {
			strcpy(nt, "F");
			strcat(nick, nt);
      count_name++;
		}
		if (scancode == G) {
			strcpy(nt, "G");
			strcat(nick, nt);
      count_name++;
		}
		if (scancode == H) {
			strcpy(nt, "H");
			strcat(nick, nt);
      count_name++;
		}
		if (scancode == I) {
			strcpy(nt, "I");
			strcat(nick, nt);
      count_name++;
		}
		if (scancode == J) {
			strcpy(nt, "J");
			strcat(nick, nt);
      count_name++;
		}
		if (scancode == K) {
			strcpy(nt, "K");
			strcat(nick, nt);
      count_name++;
		}
		if (scancode == L) {
			strcpy(nt, "L");
			strcat(nick, nt);
      count_name++;
		}
		if (scancode == M) {
			strcpy(nt, "M");
			strcat(nick, nt);
      count_name++;
		}
		if (scancode == N) {
			strcpy(nt, "N");
			strcat(nick, nt);
      count_name++;
		}
		if (scancode == O) {
			strcpy(nt, "O");
			strcat(nick, nt);
      count_name++;
		}
		if (scancode == P) {
			strcpy(nt, "P");
			strcat(nick, nt);
      count_name++;
		}
		if (scancode == Q) {
			strcpy(nt, "Q");
			strcat(nick, nt);
      count_name++;
		}
		if (scancode == R) {
			strcpy(nt, "R");
			strcat(nick, nt);
      count_name++;
		}
		if (scancode == S) {
			strcpy(nt, "S");
			strcat(nick, nt);
      count_name++;
		}
		if (scancode == T) {
			strcpy(nt, "T");
			strcat(nick, nt);
      count_name++;
		}
		if (scancode == U) {
			strcpy(nt, "U");
			strcat(nick, nt);
      count_name++;
		}
		if (scancode == V) {
			strcpy(nt, "V");
			strcat(nick, nt);
      count_name++;
		}
		if (scancode == W) {
      
			strcpy(nt, "W");
			strcat(nick, nt);
      
      count_name++;
		}
		if (scancode == X) {
			strcpy(nt, "X");
			strcat(nick, nt);
      count_name++;
		}
		if (scancode == Y) {
			strcpy(nt, "Y");
			strcat(nick, nt);
      count_name++;
		}
		if (scancode == Z) {
			strcpy(nt, "Z");
			strcat(nick, nt);
      count_name++;
		}
		if (count_name ==5) {
      count_name =0;
			nick_complete=true;
		}
}

void insert_new_record(User *u)
{
  bool fake = false;
  for (int it=0;it<3;it++)
  {
    if(high_sc[it]==0)
    {
      high[it]=u;
      high_sc[it]=u->sc;
      fake = true;
      break;
    }
  }
  if(!fake){
    for (int it=0;it<3;it++)
    {
      if (u->sc>high_sc[it])
      {
        if(it==0)
        {
          high[2]=high[1];
          high[1]=high[0];
          high_sc[2]=high_sc[1];
          high_sc[1]=high_sc[0];
        }
        else if(it==1)
        {
          high[2]=high[1];
          high_sc[2]=high_sc[1];
        }
        high[it]=u;
        high_sc[it]=u->sc;
        break;
      }
    }
  }
}

bool new_record(int sc)
{
  for (int i=0;i<3;i++)
  {
    if(high_sc[i]==0)
    {
      return true;
    }
  }
  for (int i=0;i<3;i++)
  {
    if (sc>high_sc[i])
    {
        return true;
    }
  }
  return false;
}

void new_mouse_pos(Sprite *cursor, Sprite *meteor){
  if(!pp.x_ov)
    actual_mouse_x = max(min(getHR(),actual_mouse_x+pp.delta_x),0);
  if(!pp.y_ov)
	  actual_mouse_y = max(min(500,actual_mouse_y-pp.delta_y),0);

  for (int i=counter_dis_meteor;i<counter_meteor;i++){
      if(meteor_y[i]<=actual_mouse_y && meteor_y[i]+meteor->image.height>=actual_mouse_y && meteor_x[i]<=actual_mouse_x && meteor_x[i]+meteor->image.width>=actual_mouse_x && pp.lb){
          meteor_x[i]=0; 
          meteor_y[i]=0;
          break;
      }
  }
  memset(&pp,0,sizeof(pp));
  count = 0;
  complete=false;
}

bool state_h(Sprite *cactus,Sprite *meteor,Sprite *cursor,Sprite *game_over,Sprite *dino_normal,Sprite *right_down,Sprite *left_down,Sprite *right,Sprite *left,Sprite *a, Sprite *b, Sprite *c, Sprite *d, Sprite *e, Sprite *f, Sprite *g, Sprite *h, Sprite *i, Sprite *j, Sprite *k, Sprite *l, Sprite *m, Sprite *n, Sprite *o, Sprite *p, Sprite *q, Sprite *r, Sprite *s, Sprite *t, Sprite *u, Sprite *v, Sprite *w, Sprite *x, Sprite *y, Sprite *z, Sprite *zero, Sprite *one,Sprite *two,Sprite *three,Sprite *four,Sprite *five,Sprite *six,Sprite *seven,Sprite *eight,Sprite *nine){
  if(n_record)
  {
    setBackground();
    char rec[11]={"NEW RECORD"};
    write_text_on_screen(rec,getHR()/2-220,200,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z, zero,one,two,three,four,five,six,seven,eight,nine);
    write_int_on_screen(score_no,getHR()/2-100,300,zero,one,two,three,four,five,six,seven,eight,nine);
    char dt[11];
    char_date(dt);
    insert_new_record(create_user(nick,dt,score_no));
    write_file();
    n_record=false;
    scancode=0;
    PageFlipping();
  }
  else if(!nick_complete)
  {
    nickname(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z, zero,one,two,three,four,five,six,seven,eight,nine);
  }
  else{
    if(!menu_complete&&scancode==0x1C){
      scancode=0;
      show_record=true;
    }
    if(!menu_complete&&scancode==57&&show_record){
      show_record=false;
      scancode=0;
    }
    if(!menu_complete&&scancode==57&&!show_record){
      menu_complete=true;
      scancode=0;
      past_time=0;
      past_counter=0;
    }
    if(fix_image&&scancode==57&&!n_record){
      destroy_all(cactus,meteor,cursor,game_over,dino_normal,right_down,left_down,right,left,zero,one,two,three,four,five,six,seven,eight,nine);
      menu_complete=false;
      fix_image=false;
      jump_up=false;
      jump_down=false;
      crouch=false;
      score_no =0;
      return true;
    }
    if(!jump_up && !jump_down){    
        if(scancode==0x48){
            jump_up=true;
            past_time=0;
        }
    }
    if(scancode==0x50){
        crouch=true;
    }
    else if(scancode==0xd0){
        crouch=false;
    } 
  }
  return false;
}
