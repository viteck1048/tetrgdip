//#include <stdio.h>
//#include <conio.h>
//#include <Windows.h>
#include <time.h>
#include <stdlib.h>
//#include <malloc.h>
//#include <stdlib.h>

#include "tetr.h"

void rot(int n_fig_p);
void gen();
void setup_1(int);
void setup_2(int);
void setup_3();
int prov_lin();
int prov_krok(int new_x, int new_y);
int prov_rot(int new_fig_p);
void prnt_podg(int ff);
int loop(int, int);
void gen_vaj();

int mas_rab[V_LIN + 3][H_LIN + 3];
int fig_tec[4][4] = {0};
int fig_b[4][4] = {0};
int fig_next[4][4] = {0};
int x, y, x_old, y_old;
int fig_t = 0, fig_p = 0, fig_t_n = 0, fig_p_n = 0, fig_c = 0, fig_c_n = 0;
unsigned long takt, prsc;
int fl_s = 0;
int hc;
int vaj;
int vaj_mem;
int vaj_mem_2;
int total;
int max_total_norm, max_total_adv;
int pause;
int etap = 0;
int sopli[V_LIN];
int f_sop, f_sop_ver;
int ready;
int f_next_level;
int anim;

int mas_pr[V_LIN][H_LIN] = {0};
int mas_preview[V_LIN][H_LIN] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 100, 100, 0},
	{0, 30, 0, 0, 0, 200, 0, 0, 0, 100, 0},
	{0, 30, 0, 0, 0, 200, 0, 0, 0, 100, 0},
	{0, 30, 0, 0, 200, 200, 0, 0, 0, 0, 0},
	{0, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 1, 1, 0, 0, 0, 50, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 50, 50, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 50, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 70, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 70, 70, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 70, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 140, 140, 0, 0},
	{0, 0, 0, 0, 0, 0, 140, 140, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 220, 0},
	{0, 0, 116, 116, 116, 0, 0, 0, 0, 220, 0},
	{0, 0, 116, 0, 0, 0, 0, 0, 0, 220, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 220, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

const int f[7][4][4] = {
	{{1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
	{{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},
	{{0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
	{{1, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
	{{0, 0, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
	{{1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
	{{0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}
};


void rot(int n_fig_p) 
{
	int i, j;
	if(fig_t < 2) {
		for(i = 0; i < 4; i++)
			for(j = 0; j < 4; j++) {
				if(n_fig_p % 2) fig_b[i][j] = f[fig_t][i][j] * fig_c;
				else fig_b[i][j] = f[fig_t][j][i] * fig_c;
			}
	}else{
		fig_b[1][3] = 0;
		fig_b[3][1] = 0;
		if(fig_t < 5)
			for(i = 0; i < 3; i++)
				for(j = 0; j < 3; j++) {
					if(!(n_fig_p % 4)) fig_b[i][j] = f[fig_t][i][j] * fig_c;
					else if (n_fig_p % 4 == 1) fig_b[i][j] = f[fig_t][2 - j][i] * fig_c;
					else if (n_fig_p % 4 == 2) fig_b[i][j] = f[fig_t][2 - i][2 - j] * fig_c;
					else fig_b[i][j] = f[fig_t][j][2 - i] * fig_c;
				}
		else
			for(i = 0; i < 3; i++)
				for(j = 0; j < 3; j++) {
					if(!(n_fig_p % 2)) fig_b[i][j] = f[fig_t][i][j] * fig_c;
					else fig_b[i][j] = f[fig_t][2 - j][i] * fig_c;
				}
	}			
}


short int rand_color(int ccc)
{
	short int aaa;
	short int aa[3];
	short int min, max;
	do {
		if(!ccc)
			aaa = (rand() % 256) + 1;
		else
			aaa = ccc;
		
		break;
		
		aa[0] = aaa & 0xc0;
		aa[1] = (aaa & 0x30) << 2;
		aa[2] = (aaa & 0x0c) << 4;
		min = aa[0] + aa[1] + aa[2];
		if(min > 400) {
			aaa = 0;
			continue;
		}
		
		if(min <= 192)
			break;
		
		min = aa[0] < aa[1] ? (aa[0] < aa[2] ? aa[0] : aa[2]) : (aa[1] < aa[2] ? aa[1] : aa[2]);
		max = aa[0] > aa[1] ? (aa[0] > aa[2] ? aa[0] : aa[2]) : (aa[1] > aa[2] ? aa[1] : aa[2]);
		if((max - min) > 120)
			break;
		aaa = 0;
		
	}while(!ccc);
	
	return aaa;
}


void gen(int prnt)
{
	int i, j;
	x = 2;
	y = (H_LIN / 2) + 1;
	fig_t = fig_t_n;
	fig_p = fig_p_n;
	fig_c = fig_c_n;
	fig_t_n = rand() % 7;
	fig_p_n = rand() % 4;
	fig_c_n = rand_color(0);
	if(true) {
		int mem[2] = {fig_t, fig_c};
		fig_t = fig_t_n;
		fig_c = fig_c_n;
		rot(fig_p_n);
		for(i = 0; i < 4; i++) {
			for(j = 0; j < 4; j++)
				fig_next[i][j] = fig_b[i][j];
		}
		fig_t = mem[0];
		fig_c = mem[1];
		rot(fig_p);
		for(i = 0; i < 4; i++)
			for(j = 0; j < 4; j++)
				fig_tec[i][j] = fig_b[i][j];
		if(fig_tec[0][0] + fig_tec[0][1] + fig_tec[0][2] + fig_tec[0][3] == 0)
			x--;
	}
	if(prnt)
		total++;
}


void gen_vaj()
{
	if(vaj_mem_2 > vaj_mem) {
		int j = 1;
		for(; j <= vaj_mem_2; j++)
			for(int i = 1; i <= H_LIN; i++)
				mas_rab[V_LIN - j + 1][i] = (rand() % 3 ? 0 : 1) * (rand_color(0));
		vaj = vaj_mem = vaj_mem_2;
		for(; V_LIN - j >= 0; j++)
			for(int i = 1; i <= H_LIN; i++)
				mas_rab[V_LIN - j + 1][i] = 0;
	}
	else if(vaj_mem != vaj) {
		if(vaj > vaj_mem)
			for(int i = 1; i <= H_LIN; i++) {
				mas_rab[V_LIN - vaj + 1][i] = (rand() % 3 ? 0 : 1) * (rand_color(0));
			}
		else
			for(int i = 1; i <= H_LIN; i++) {
				mas_rab[V_LIN - vaj][i] = 0;
			}
		vaj_mem_2 = vaj_mem = vaj;
	}
}


void setup_00()
{
//	max_total_norm = 0;
//	max_total_adv = 0;
	pause = 1;
	srand((unsigned int)time(NULL));
	gen(0);
	fl_s = 0;
	f_sop = 0;
	f_sop_ver = 0;
	takt = shvydkist;
	etap = 0;
	ready = 0;
	f_next_level = 0;
	hc = rand() % 10000;
	anim = 0;
	
//	for(int i = 0; i < V_LIN * H_LIN; i++)
//		*(&(mas_preview[0][0]) + i) = rand_color(1 + i);
	
}


void setup_0(int no_adv)
{
	vaj_mem_2 = no_adv == 1 ? vaj_mem_2 : 1;
	etap = 1;
}


void setup_1(int no_adv)
{
	int i, j;
	vaj = 0;
	vaj_mem = 0;
	if(no_adv || vaj_mem_2 == 1) {
		gen(0);
		total = 0;
	}
	for(i = 0; i < (V_LIN + 3); i++)
		for(j = 0; j < (H_LIN + 3); j++) {
			if(!i || !j || i == (V_LIN + 1) || j == (H_LIN + 1) || i == (V_LIN + 2) || j == (H_LIN + 2)) mas_rab[i][j] = 1;
			else mas_rab[i][j] = 0;
		}
	for(i = 0; i < 4; i++)
		for(j = 0; j < 4; j++)
			fig_tec[i][j] = 0;
	if(!no_adv && vaj_mem_2 != 18)
		vaj_mem_2++;
	gen(0);
	if(vaj_mem_2 > 1)
		do{gen_vaj();}while(prov_lin());
	else
		gen_vaj();
	fl_s = 0;
	if(no_adv) {
		gen_vaj();
		prnt_podg(0);
		etap = 2;
	}else {
		etap = 3;
		ready = 4;
		prnt_podg(1);
	}
	takt = shvydkist;
	prsc = pryskorennia;
}


void setup_2(int scan)
{
 	if(scan) {
		if(scan == 1) {
			if(vaj < V_LIN - 4) {
				vaj++;
			}
		}
		else if(scan == 3) {
			if(vaj > 0) {
				vaj--;
			}
		}
		else {
			etap = 3;
			ready = 4;
		}
	}
	gen_vaj();
	prnt_podg(1);
}
	
	
void setup_3()	
{
	prnt_podg(1);
	pause = 0;
	etap = 4;
}


int prov_lin()
{
	f_sop = 0;
	int brbr = 0;
	int i, j, ii, jj;
	int ff = 0;
	for(i = 1; i <= V_LIN; i++)
		for(j = 1; j <= H_LIN; j++) {
			sopli[i - 1] = 0;
			if(!mas_rab[i][j]) break;
			if(j == H_LIN) {
				total += V_LIN - j + 1;
				brbr++;
				sopli[i - 1] = 1;
				f_sop = 1;
				for(ii = i; ii > 1; ii--)
					for(jj = 1; jj < (H_LIN + 1); jj++) mas_rab[ii][jj] = mas_rab[ii - 1][jj];
				for(jj = 1; jj < (H_LIN + 1); jj++) mas_rab[1][jj] = 0;
			}
		}
	switch(brbr) {
		case 0:
			break;
		case 1:
			total += 10;
			break;
		case 2:
			total += 20;
			break;
		case 3:
			total += 40;
			break;
		case 4:
			total += 100;
			break;
		default:
			break;
	}
	for(j = 1; j <= H_LIN; j++) {
		ff = 1;
		for(i = V_LIN; i > 1; i--) {
			if(ff && !mas_rab[i][j])
				ff = 0;
			else if(!ff && mas_rab[i][j])
				return 0;
		}
	}
	return 1;
}


int prov_krok(int new_x, int new_y)
{
	int i, j;
	for(i = 0; i < 4; i++)
		for(j = 0; j < 4; j++)
			if(fig_tec[i][j] && mas_rab[new_x + i - 1][new_y + j - 1]) return 0;
	return 1;
}


int prov_rot(int new_fig_p)
{
	int i, j;
	int ii, jj;
	int ff = 0;
	rot(new_fig_p % 4);
	for(i = 0; i < 4; i++)
		for(j = 0; j < 4; j++)
			if(fig_b[i][j] && mas_rab[x + i - 1][y + j - 1]) 
				if(x == 1) {
					x++;
					if(prov_rot(new_fig_p))
						return 1;
					else {
						x--;
						return 0;
					}
				}
				else {
					if(j == 0) {
						for(ii = 0; ii < 4; ii++)
							for(jj = 0; jj < 4; jj++)						
								if(fig_b[ii][jj] && mas_rab[x + ii - 1][y + jj])
									return 0;
						y++;
						for(i = 0; i < 4; i++)
							for(j = 0; j < 4; j++)
								fig_tec[i][j] = fig_b[i][j];
						return 1;
					}
					else if(fig_t == 1 && new_fig_p % 2 == 1) {
						for(ii = 0; ii < 4; ii++)						
							if(fig_b[1][ii] && mas_rab[x][y + ii - 2])
								break;
						for(jj = 0; jj < 4; jj++)
							if(fig_b[1][jj] && mas_rab[x][y + jj - 3])
								break;
						if(ii == 4) {
							y--;
							for(i = 0; i < 4; i++)
								for(j = 0; j < 4; j++)
									fig_tec[i][j] = fig_b[i][j];
							return 1;
						}
						else if(jj == 4) {
							y -= 2;
							for(i = 0; i < 4; i++)
								for(j = 0; j < 4; j++)
									fig_tec[i][j] = fig_b[i][j];
							return 1;
						}
						else 
							return 0;
					}
					else if(j == 2) {
						for(ii = 0; ii < 3; ii++)
							for(jj = 0; jj < 3; jj++)						
								if(fig_b[ii][jj] && mas_rab[x + ii - 1][y + jj - 2])
									return 0;
						y--;
						for(i = 0; i < 4; i++)
							for(j = 0; j < 4; j++)
								fig_tec[i][j] = fig_b[i][j];
						return 1;
					}
					else
						return 0;
					
				}
	for(i = 0; i < 4; i++)
		for(j = 0; j < 4; j++)
			fig_tec[i][j] = fig_b[i][j];
	return 1;
}


void prnt_podg(int ff)
{
	int i, j;
	for(i = 1; i < (V_LIN + 1); i++)
		for(j = 1; j < (H_LIN + 1); j++) {
			mas_pr[i - 1][j - 1] = mas_rab[i][j];
			if(i >= x - 1 && i <= x + 2 && j >= y - 1 && j <= y + 2 && etap >=3 && ff)
				mas_pr[i - 1][j - 1] = fig_tec[i - x + 1][j - y + 1] != 0 ? fig_tec[i - x + 1][j - y + 1] : mas_rab[i][j];
		}
}


int loop(int no_adv, int scan)
{
	switch(scan) {
		case 3:{
			fl_s = 1;
			break;
		}
		case 2:{
			x_old = x;
			y_old = y;
			if(prov_krok(x, y - 1)) {
				y--;
				prnt_podg(1);
				anim = 2;
			}
			break;
		}
		case 4:{
			if(prov_krok(x, y + 1)) {
				y++;
				prnt_podg(1);
			}
			break;
		}
		case 1:{
			if(prov_rot(fig_p + 1)) {
				fig_p = (fig_p + 1) % 4;
				prnt_podg(1);
			}
			break;
		}
		default:{
			break;
		}
	}
	
	if(!scan) {
		int i, j;
		if(prov_krok(x + 1, y)) {
			x++;
			prnt_podg(1);
		}else{
			for(i = 0; i < 4; i++)
				for(j = 0; j < 4; j++)
					mas_rab[x + i - 1][y + j - 1] = fig_tec[i][j] != 0 ? fig_tec[i][j] : mas_rab[x + i - 1][y + j - 1];
			if(prov_lin() && !no_adv) {
				f_sop = 0;
				etap = 1;
				f_sop_ver = 1;
				f_next_level = 1;
				total += vaj_mem_2 * 100;
				return 1;
			}
			gen(1);
			if(!prov_krok(x, y)) {
				prnt_podg(1);
				f_sop_ver = 1;
				if(!no_adv)
					vaj_mem_2 = 1;
				if((no_adv == 1 ? max_total_norm : max_total_adv) < total)
					(no_adv == 1 ? max_total_norm : max_total_adv) = total;
				etap = 0;
				for(i = 0; i < (V_LIN + 3); i++)
					for(j = 0; j < (H_LIN + 3); j++) {
						if(!i || !j || i == (V_LIN + 1) || j == (H_LIN + 1) || i == (V_LIN + 2) || j == (H_LIN + 2)) mas_rab[i][j] = 1;
						else mas_rab[i][j] = 0;
					}
				prnt_podg(1);
				return 0;
			}
			prnt_podg(1);
			if(fl_s) {
				fl_s = 0;
			}
		}
	}
	return 1;
}
