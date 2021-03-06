#include <ncurses.h>
#include <unistd.h>
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

//�������!!!

//����������
struct Pos{
	int x;
	int y;
};
	
//���������� �����
void draw(int x, int y, int color){
	move(y,2*x);
	attron(COLOR_PAIR(color));
	addch(' ');
	addch(' ');
	refresh();
}

//�������� �����
void Clear(int x, int y){
	move(y,2*x);
	attron(COLOR_PAIR(2));
	addch(' ');
	addch(' ');
	refresh();
}

//��������� ���������� ������
struct Pos step(struct Pos p,  int dx, int dy, int color){
	Clear(p.x, p.y);		
	p.x=dx;
	p.y=dy;
	draw(p.x, p.y, color);
	return p;
}

//��������� ���������
bool comp(struct Pos A, struct Pos B){
	return A.x==B.x && A.y==B.y;
}

//���������� ����
void draw_all(struct Pos *B,struct Pos *W,struct Pos *D,int lB, int lW, int lD, struct Pos p){
	
	
	for (int i=0;i<lW;i++){
		draw(W[i].x,W[i].y,8);	
	}	
	for (int i=0;i<lD;i++){
		draw(D[i].x,D[i].y,9);		
	}
	for (int i=0;i<lB;i++){
		draw(B[i].x,B[i].y,1);	
	}	
	draw(p.x,p.y,4);
}


int main(){

	initscr();
	int count_on_point = 0;
	int count_obj = 0;
	start_color();
	setlocale(LC_CTYPE,"");
	curs_set(0);
	noecho();
	//������������� �������� ��� (���� ������ � ����)
	init_pair(1, COLOR_GREEN, COLOR_GREEN );
	init_pair(2, COLOR_BLACK, COLOR_BLACK );
	init_pair(3, COLOR_BLUE, COLOR_BLUE );
    init_pair(4,  COLOR_YELLOW,  COLOR_YELLOW);
    init_pair(5,  COLOR_BLUE,    COLOR_BLUE);
    init_pair(6,  COLOR_MAGENTA, COLOR_MAGENTA);
    init_pair(7,  COLOR_CYAN,    COLOR_CYAN);
    init_pair(8,  COLOR_BLUE,    COLOR_BLUE);
    init_pair(9,  COLOR_WHITE,   COLOR_WHITE);
	init_pair(10, COLOR_WHITE, COLOR_BLACK );
	init_pair(11, COLOR_RED, COLOR_BLACK );
	attron(COLOR_PAIR(10));
	struct Pos p;
	struct Pos b[10];
	struct Pos d[10];
	struct Pos w[1000];

	int curbox = 0;
	int curdest = 0;
	int curwall = 0;
	char c;
	
	FILE *in;
	//��������� ����� ������
	while(in = fopen("level0.txt","rb")){
		int i = 0;
		int j = 0;
		int mx = 0;
		curbox = 0;
		curdest = 0;
		curwall = 0;
		mx = 0;
		count_on_point = 0;
		count_obj = 0;
		while (fscanf(in,"%c", &c) == 1){
			
			if (c == '@'){ //�����
				p.x=i;
				p.y = j;			
			}
			if (c == '#'){ //����
				b[curbox].x= i;
				b[curbox].y = j;
				curbox++;		
			}
			if (c == '0'){ //����� ��� ����
				d[curdest].x = i;
				d[curdest].y = j;
				curdest++;
				count_obj++;			
			}
			if (c == '1'){ //���� �� �����
				b[curbox].x= i;
				b[curbox].y = j;
				curbox++;
				d[curdest].x = i;
				d[curdest].y = j;
				curdest++;
				count_obj++;		
			}
			if (c == '2'){ //����� �� �����
				p.x=i;
				p.y = j;
				d[curdest].x = i;
				d[curdest].y = j;
				curdest++;
				count_obj++;					
			}
			if (c == '*'){ //�����
				
				w[curwall].x = i;
				w[curwall].y = j;
				curwall++;				
			}

			if (c == '\n'){
				j++;
				i = 0;		
			}else{
				i++;		
				if (i>mx) mx = i;	
			}	
		}
		fclose(in);
		draw_all(b,w,d,curbox,curwall,curdest,p);
			
		refresh();
		int dir = -1;
		int dx[] = { 0, 0, 1, -1};
		int dy[] = { -1, 1, 0, 0};
		attron(COLOR_PAIR(10));
		move(2,mx*2+5);
		refresh();
		while(count_on_point!=count_obj){
			char ch = getch();
			//WASD - ��������
			switch (ch){
				case 'w': dir = 0; break;
				case 's': dir = 1; break;
				case 'd': dir = 2; break;
				case 'a': dir = 3; break;
				default: dir =-1; break;		
			}
			intptr_t obj;
			int col;
			struct Pos nextp = p;
			nextp.x = p.x + dx[dir];
			nextp.y = p.y + dy[dir];
			p = step(p,p.x+dx[dir],p.y+dy[dir],4);
			
			draw_all(b,w,d,curbox,curwall,curdest,p);
			
			attron(COLOR_PAIR(10));
			move(2,mx*2+5);
			refresh();
			
		}
	}
	endwin(); 
	return 0;
}
