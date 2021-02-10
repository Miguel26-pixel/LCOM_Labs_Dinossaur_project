#include "while_game.h"

extern uint8_t scancode;
extern int past_time;
extern int past_counter;
extern int score_counter;
extern enum xpm_image_type type;
extern uint8_t kbc_bit_no;
extern uint8_t timer_bit_no;
extern uint8_t mouse_bit_no;
extern uint8_t rtc_bit_no;

extern int cactus_x[200000];
extern int meteor_x[200000];
extern int meteor_y[200000];
extern int bird_x[200000];
extern bool bird_orientation[200000];
extern User* high[3];
extern int high_sc[3];
extern char nick[6];

extern bool jump_up;
extern bool jump_down;
extern bool fix_image;
extern bool menu_complete;
extern bool crouch;
extern bool complete;
extern bool nick_complete;
extern bool n_record;
bool kbd=false;

extern int cnt;
extern int counter_meteor;
extern int counter_dis_meteor;
extern int counter_spawn;
extern int counter_dispawn;

int actual_mouse_x = 0;
int actual_mouse_y = 0;
extern int temp_y,temp_x;

extern int score_no;


//extern struct Sprite;


void (while_game)(){
    memset(cactus_x,0,sizeof(cactus_x));
    memset(meteor_x,0,sizeof(meteor_x));
    memset(meteor_y,0,sizeof(meteor_y));
    memset(bird_x,0,sizeof(bird_x));
    memset(bird_orientation,false,sizeof(bird_orientation));
    memset(high_sc,0,sizeof(high_sc));
    memset(nick,0,sizeof(nick));
    actual_mouse_y=0;
    actual_mouse_x=0;
    nick_complete=false;
    read_file();

    message msg;
    int ro;
    int ipc_status;
    scancode = 0x00;
    past_time=0;
    past_counter=0;


    xpm_image_t img_cactus;
    xpm_image_t img_meteor;
    xpm_image_t img_cursor;
    xpm_image_t img_game_over;
    xpm_image_t img_dino_normal;
    xpm_image_t img_dino_right_down;
    xpm_image_t img_dino_left_down;
    xpm_image_t img_dino_right;
    xpm_image_t img_dino_left;
    xpm_image_t img_menu_with_spacebar; 
    xpm_image_t img_menu_without_spacebar;
    xpm_image_t img_bird_down;
    xpm_image_t img_bird_up;
    xpm_image_t img_zero;
    xpm_image_t img_one;
    xpm_image_t img_two;
    xpm_image_t img_three;
    xpm_image_t img_four;
    xpm_image_t img_five;
    xpm_image_t img_six;
    xpm_image_t img_seven;
    xpm_image_t img_eight;
    xpm_image_t img_nine;
    xpm_image_t img_a;
    xpm_image_t img_b;
    xpm_image_t img_c;
    xpm_image_t img_d;
    xpm_image_t img_e;
    xpm_image_t img_f;
    xpm_image_t img_g;
    xpm_image_t img_h;
    xpm_image_t img_i;
    xpm_image_t img_j;
    xpm_image_t img_k;
    xpm_image_t img_l;
    xpm_image_t img_m;
    xpm_image_t img_n;
    xpm_image_t img_o;
    xpm_image_t img_p;
    xpm_image_t img_q;
    xpm_image_t img_r;
    xpm_image_t img_s;
    xpm_image_t img_t;
    xpm_image_t img_u;
    xpm_image_t img_v;
    xpm_image_t img_w;
    xpm_image_t img_x;
    xpm_image_t img_y;
    xpm_image_t img_z;

    uint8_t *cactus_pointer = xpm_load(cactus_xpm, type, &img_cactus);
    uint8_t *meteor_pointer = xpm_load(meteor_xpm, type, &img_meteor);
    uint8_t *cursor_pointer = xpm_load(cursor_xpm, type, &img_cursor);
    uint8_t *game_over_pointer = xpm_load(gameover_xpm,type,&img_game_over);
    uint8_t *dino_normal_pointer = xpm_load(dino_normal_xpm, type, &img_dino_normal);
    uint8_t *right_down_pointer = xpm_load(dino_baixo_dir_xpm, type, &img_dino_right_down);
    uint8_t *left_down_pointer = xpm_load(dino_baixo_esq_xpm, type, &img_dino_left_down);
    uint8_t *right_pointer = xpm_load(dino_rightleg_xpm, type, &img_dino_right);
    uint8_t *left_pointer = xpm_load(dino_leftleg_xpm, type, &img_dino_left);
    uint8_t *spacebar_pointer = xpm_load(init_spacebar_xpm, type, &img_menu_with_spacebar);
    uint8_t *no_spacebar_pointer = xpm_load(init_no_spacebar_xpm, type, &img_menu_without_spacebar);
    uint8_t *bird_down_pointer = xpm_load(avebaixo_xpm, type, &img_bird_down);
    uint8_t *bird_up_pointer = xpm_load(avecima_xpm, type, &img_bird_up);
    uint8_t *zero_pointer = xpm_load(zero_xpm, type, &img_zero);
    uint8_t *one_pointer = xpm_load(one_xpm, type, &img_one);
    uint8_t *two_pointer = xpm_load(two_xpm, type, &img_two);
    uint8_t *three_pointer = xpm_load(three_xpm, type, &img_three);
    uint8_t *four_pointer = xpm_load(four_xpm, type, &img_four);
    uint8_t *five_pointer = xpm_load(five_xpm, type, &img_five);
    uint8_t *six_pointer = xpm_load(six_xpm, type, &img_six);
    uint8_t *seven_pointer = xpm_load(seven_xpm, type, &img_seven);
    uint8_t *eight_pointer = xpm_load(eight_xpm, type, &img_eight);
    uint8_t *nine_pointer = xpm_load(nine_xpm, type, &img_nine);
    uint8_t *a_pointer = xpm_load(a_xpm,type,&img_a);
    uint8_t *b_pointer = xpm_load(b_xpm,type,&img_b);
    uint8_t *c_pointer = xpm_load(c_xpm,type,&img_c);
    uint8_t *d_pointer = xpm_load(d_xpm,type,&img_d);
    uint8_t *e_pointer = xpm_load(e_xpm,type,&img_e);
    uint8_t *f_pointer = xpm_load(f_xpm,type,&img_f);
    uint8_t *g_pointer = xpm_load(g_xpm,type,&img_g);
    uint8_t *h_pointer = xpm_load(h_xpm,type,&img_h);
    uint8_t *i_pointer = xpm_load(i_xpm,type,&img_i);
    uint8_t *j_pointer = xpm_load(j_xpm,type,&img_j);
    uint8_t *k_pointer = xpm_load(k_xpm,type,&img_k);
    uint8_t *l_pointer = xpm_load(l_xpm,type,&img_l);
    uint8_t *m_pointer = xpm_load(m_xpm,type,&img_m);
    uint8_t *n_pointer = xpm_load(n_xpm,type,&img_n);
    uint8_t *o_pointer = xpm_load(o_xpm,type,&img_o);
    uint8_t *p_pointer = xpm_load(p_xpm,type,&img_p);
    uint8_t *q_pointer = xpm_load(q_xpm,type,&img_q);
    uint8_t *r_pointer = xpm_load(r_xpm,type,&img_r);
    uint8_t *s_pointer = xpm_load(s_xpm,type,&img_s);
    uint8_t *t_pointer = xpm_load(t_xpm,type,&img_t);
    uint8_t *u_pointer = xpm_load(u_xpm,type,&img_u);
    uint8_t *v_pointer = xpm_load(v_xpm,type,&img_v);
    uint8_t *w_pointer = xpm_load(w_xpm,type,&img_w);
    uint8_t *x_pointer = xpm_load(x_xpm,type,&img_x);
    uint8_t *y_pointer = xpm_load(y_xpm,type,&img_y);
    uint8_t *z_pointer = xpm_load(z_xpm,type,&img_z);
    


    Sprite *cactus = create_sprite(getHR()-20,430,-7,0,img_cactus.width,img_cactus.height,cactus_pointer,img_cactus);

    Sprite *meteor = create_sprite(getHR()-50,0,-5,2,img_meteor.width,img_meteor.height,meteor_pointer,img_meteor);

    Sprite *cursor = create_sprite(0,0,0,0,img_cursor.width,img_cursor.height,cursor_pointer,img_cursor);

    Sprite *game_over = create_sprite((getHR()/2)-498,300,0,0,img_game_over.width,img_game_over.height,game_over_pointer,img_game_over);

    Sprite *dino_normal = create_sprite(20,415,0,5,img_dino_normal.width,img_dino_normal.height,dino_normal_pointer,img_dino_normal);

    Sprite *right_down = create_sprite(20,448,0,0,img_dino_right_down.width,img_dino_right_down.height,right_down_pointer,img_dino_right_down);

    Sprite *left_down = create_sprite(20,448,0,0,img_dino_left_down.width,img_dino_left_down.height,left_down_pointer,img_dino_left_down);

    Sprite *right = create_sprite(20,415,0,0,img_dino_right.width,img_dino_right.height,right_pointer,img_dino_right);

    Sprite *left = create_sprite(20,415,0,0,img_dino_left.width,img_dino_left.height,left_pointer,img_dino_left);

    Sprite *spacebar = create_sprite((getHR()/2)-598,520,0,0,img_menu_with_spacebar.width,img_menu_with_spacebar.height,spacebar_pointer,img_menu_with_spacebar);

    Sprite *no_spacebar = create_sprite((getHR()/2)-598,520,0,0,img_menu_with_spacebar.width,img_menu_with_spacebar.height,no_spacebar_pointer,img_menu_without_spacebar);

    Sprite *up_bird = create_sprite(getHR()-60,355,-7,0,img_bird_up.width,img_bird_up.height,bird_up_pointer,img_bird_up);

    Sprite *down_bird = create_sprite(getHR()-70,355,-7,0,img_bird_down.width,img_bird_down.height,bird_down_pointer,img_bird_down);

    Sprite *zero = create_sprite(0,0,0,0,img_zero.width,img_zero.height,zero_pointer,img_zero);

    Sprite *one = create_sprite(0,0,0,0,img_one.width,img_one.height,one_pointer,img_one);

    Sprite *two = create_sprite(0,0,0,0,img_two.width,img_two.height,two_pointer,img_two);

    Sprite *three = create_sprite(0,0,0,0,img_three.width,img_three.height,three_pointer,img_three);

    Sprite *four = create_sprite(0,0,0,0,img_four.width,img_four.height,four_pointer,img_four);

    Sprite *five = create_sprite(0,0,0,0,img_five.width,img_five.height,five_pointer,img_five);

    Sprite *six = create_sprite(0,0,0,0,img_six.width,img_six.height,six_pointer,img_six);

    Sprite *seven = create_sprite(0,0,0,0,img_seven.width,img_seven.height,seven_pointer,img_seven);

    Sprite *eight = create_sprite(0,0,0,0,img_eight.width,img_eight.height,eight_pointer,img_eight);

    Sprite *nine = create_sprite(0,0,0,0,img_nine.width,img_nine.height,nine_pointer,img_nine);

    Sprite *a = create_sprite(0,0,0,0,img_a.width,img_a.height,a_pointer,img_a);

    Sprite *b = create_sprite(0,0,0,0,img_b.width,img_b.height,b_pointer,img_b);

    Sprite *c = create_sprite(0,0,0,0,img_c.width,img_c.height,c_pointer,img_c);

    Sprite *d = create_sprite(0,0,0,0,img_d.width,img_d.height,d_pointer,img_d);

    Sprite *e = create_sprite(0,0,0,0,img_e.width,img_e.height,e_pointer,img_e);

    Sprite *f = create_sprite(0,0,0,0,img_f.width,img_f.height,f_pointer,img_f);

    Sprite *g = create_sprite(0,0,0,0,img_g.width,img_g.height,g_pointer,img_g);

    Sprite *h = create_sprite(0,0,0,0,img_h.width,img_h.height,h_pointer,img_h);

    Sprite *i = create_sprite(0,0,0,0,img_i.width,img_i.height,i_pointer,img_i);

    Sprite *j = create_sprite(0,0,0,0,img_j.width,img_j.height,j_pointer,img_j);

    Sprite *k = create_sprite(0,0,0,0,img_k.width,img_k.height,k_pointer,img_k);

    Sprite *l = create_sprite(0,0,0,0,img_l.width,img_l.height,l_pointer,img_l);

    Sprite *m = create_sprite(0,0,0,0,img_m.width,img_m.height,m_pointer,img_m);

    Sprite *n = create_sprite(0,0,0,0,img_n.width,img_n.height,n_pointer,img_n);

    Sprite *o = create_sprite(0,0,0,0,img_o.width,img_o.height,o_pointer,img_o);

    Sprite *p = create_sprite(0,0,0,0,img_p.width,img_p.height,p_pointer,img_p);

    Sprite *q = create_sprite(0,0,0,0,img_q.width,img_q.height,q_pointer,img_q);

    Sprite *r = create_sprite(0,0,0,0,img_r.width,img_r.height,r_pointer,img_r);

    Sprite *s = create_sprite(0,0,0,0,img_s.width,img_s.height,s_pointer,img_s);

    Sprite *t = create_sprite(0,0,0,0,img_t.width,img_t.height,t_pointer,img_t);

    Sprite *u = create_sprite(0,0,0,0,img_u.width,img_u.height,u_pointer,img_u);

    Sprite *v = create_sprite(0,0,0,0,img_v.width,img_v.height,v_pointer,img_v);

    Sprite *w = create_sprite(0,0,0,0,img_w.width,img_w.height,w_pointer,img_w);

    Sprite *x = create_sprite(0,0,0,0,img_x.width,img_x.height,x_pointer,img_x);

    Sprite *y = create_sprite(0,0,0,0,img_y.width,img_y.height,y_pointer,img_y);

    Sprite *z = create_sprite(0,0,0,0,img_z.width,img_z.height,z_pointer,img_z);


    setBackground();
    print_whitout_back(spacebar->x,spacebar->y,&spacebar->image,spacebar->pixel_pointer);
    PageFlipping();

    while (scancode != ESC_KEY ){

        if ( (ro = driver_receive(ANY, &msg, &ipc_status)) != OK ) { 
                printf("driver_receive failed with: %d", ro);
                continue;
        }

        if (is_ipc_notify(ipc_status)) {
            switch (_ENDPOINT_P(msg.m_source)) {
                case HARDWARE:
                    if (msg.m_notify.interrupts & timer_bit_no){
                        timer_int_handler();
                        if(!menu_complete){
                            menu_handler(spacebar,no_spacebar,a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, zero, one,two,three,four,five,six,seven,eight,nine);
                        }
                        else{
                            if(!fix_image){
                                setBackground();
                                print_whitout_back(actual_mouse_x,actual_mouse_y,&cursor->image,
                                cursor->pixel_pointer);
                                write_text_on_screen(nick,getHR()/2-120,50,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z, zero,one,two,three,four,five,six,seven,eight,nine);
                                obstacles_spawn(cactus,meteor, up_bird, down_bird);	
                                if(jump_up){
                                    jumpup(dino_normal,game_over);
                                }
                                else if(jump_down){
                                    jumpdown(dino_normal, game_over);
                                }
                                else if(crouch){
                                    down(dino_normal, game_over, right_down, left_down);
                                }
                                else{
                                    switch_leg(dino_normal, game_over, right, left);
                                } 
                                score_no += 1;      
                                score(zero,one,two,three,four,five,six,seven,eight,nine);
                            PageFlipping();
                            }
                        }

                    }
                    if (msg.m_notify.interrupts & kbc_bit_no) {
                        kbc_ih();
                        if(state_h(cactus,meteor,cursor,game_over,dino_normal,right_down,left_down,right,left,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z, zero,one,two,three,four,five,six,seven,eight,nine)){
                            while_game(); 
                        }
                    }
                    if (msg.m_notify.interrupts & mouse_bit_no) {
                        mouse_ih();
                        if(complete){
                            new_mouse_pos(cursor,meteor);
                        }
                    }
                    break;
                default:
                    break;
            }
        }
    }
    
}
