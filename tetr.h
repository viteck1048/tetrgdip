


#define V_LIN 22
#define H_LIN 11

#define pryskorennia 200
#define shvydkist 1000 

extern int mas_pr[V_LIN][H_LIN];
extern int mas_preview[V_LIN][H_LIN];
extern int fig_next[4][4];
extern int fl_s;
extern int hc;
extern int vaj_mem_2;
extern int total;
extern int max_total_norm, max_total_adv;
extern int pause;
extern int etap;
extern unsigned long takt, prsc;
extern int sopli[V_LIN];
extern int f_sop, f_sop_ver;
extern int ready;
extern int f_next_level;
extern int anim;
extern int x, y, x_old, y_old;

int loop(int, int);
void setup_00();
void setup_0(int);
void setup_1(int);
void setup_2(int);
void setup_3();
void prnt_podg(int);