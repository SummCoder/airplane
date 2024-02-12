#include<stdio.h>
#include<string.h>
#include<time.h>
#include<graphics.h>
//ʹ��EGEͼ�ο⣬��������������ͼ�ο���
//�л��������ҷ��ӵ����������з��ӵ������� 
#define NUM_ENEMY 12 
#define NUM_MY_BUL 50 
#define NUM_ENEMY_BUL 5
//���뱳��ͼƬ������һ��� 
PIMAGE img_back;
//��������ҳ��ı���ͼƬ 
PIMAGE img1,img2;
//�ҷ�ս�� 
PIMAGE img3,img4;
//�з�ս��
PIMAGE img5,img6; 
//�ڵ� 
PIMAGE img7,img8,img9;
//��ǿ���� 
PIMAGE img10;
//��Ϸʤ���Լ���Ϸʧ�ܵ�ͼƬ 
PIMAGE img11,img12;
//�������֣���ȤһЩ 
MUSIC music;
//��ʼ�������Ϸ���� 
void design(); 
//�����ʼ��Ϸ��������������Ϸ���� 
void play();
//��ʼ����ս����λ 
void initPlayer();
//ͨ�����̲����ɻ��ƶ� 
void move();
//�����ӵ� 
void bulletcreate(); 
//�ӵ��ƶ� 
void bulletmove();
//�л��Ĳ��� 
void enemycreate();
//�л����ƶ� 
void enemymove();
//�ӵ����ел� 
void hitenemy();
//����boss 
void bosscreate();
//boss���ƶ� 
void bossmove();
//û�жԿ���ɶ��˼��boss�����ӵ� 
void bossaction();
//boss�ӵ��ƶ� 
void bossbulletmove();
//�����ҷ��ɻ� 
void hitme();
//��Ϸbuff���� 
void buffcreate();  
//��Ϸbuff���ƶ� 
void buffmove();
//��Ϸbuff����Լ��������� 
void buffget();
//��Ϸʧ�� 
void losegame();
//��Ϸʤ�� 
void wingame();
//ѭ������ 
void mainloop();
//��Ϸû������̫���ģ� 
void music_haha();
//һЩ��Ϸ��ص���Ϣ 
void information(); 
// ��Ϸ����
int end();
//�л�ҳ��ʱ������ⷢ���仯����һ��judge�жϵ�ǰ����ҳ�棨����û�����ʲô�õĽ�������� 
//0��ʾ��ҳ�棬1��ʾ��ʼ��Ϸ���棬2��ʾ��Ϸ˵������ ��3��ʾ��Ϸʧ���˳���Ϸ���棬4��ʾ��Ϸʤ���˳���Ϸ���� 
int judge = 0;
//����һ����������������boss�ĳ��� 
int score = 0; 
//����һ��boss���ƶ����� 
int dx = 1;
// ���ýṹ���װ�ҷ��ɻ��������� 
typedef struct plane{
//	x��y�Ƕ���������� 
	int x;
	int y;
//	blood��ʣ���Ѫ�� 
	int blood;
//	�ɻ��Ŀ�Ⱥ͸߶� 
	int width;
	int height;
//	�ɻ���״̬ 
	bool is_or_no;
} Plane;
//����һ��Plane���͵ı���myplane����Ϊ��Ҳٿص�ս�� 
Plane myplane;
//������Plane���͵ı�������Ϊ���ֵĵл� 
Plane enemyplane[NUM_ENEMY]; 
//����һ��boss 
Plane bossplane;
//buff������Ϊ��л����ƣ�ֱ������һ��Plane���� 
Plane mybuff;
//�ٴ����ýṹ���װ�ӵ����� 
typedef struct bullet{
//	x��y��ʾ�ӵ������� 
	int x;
	int y;
//	��ʾ�ӵ���״̬ 
	bool is_or_no;
} Bullet;
//�ҷ��ӵ� 
Bullet mybullet[NUM_MY_BUL];
//�з��ӵ� 
Bullet enemybullet[NUM_ENEMY_BUL];

//��������� 
int main(){
//	���ó�ʼ������ʼ���� 
	design();
//	�������ע����� 
	music_haha();
//��Ϸ��ѭ�����岿��
	mainloop(); 
//	��Ϸ���� 
	end();
} 



void design(){
//	��ƴ��ڵĴ�С����Ӧ��ѡ��ı���ͼƬ��1/2 
	initgraph(400, 711, 0);
	img_back = newimage();
	getimage(img_back, "./ʵ��ͼƬ.jpeg", 0, 0);
//	������Ϸ����Ϊ���ɻ���ս�����������棩�� 
	setcaption("�ɻ���ս������������o(*�����*)o��"); 
//	����ͼƬ̫���ˣ���С1/2���������������ҵ����������� 
	putimage(0, 0, 400, 711, img_back, 0, 0, 800, 1422);
}

void play(){
//	ƴ��������һ����ͼƬ���γ�һ������ǰ�����Ӿ�Ч���������ʼ������ͼƬ��y���� 
	int img2_y = 0;
	int img2_yy = -711;
	initPlayer(); //���ó�ʼ����������ʼ����Ϸ�ĸ������
//	��������ͼƬ 
	getimage(img2, "./ͼ2.jpeg", 0, 0);
	getimage(img3, "./�ҵ�ս��.png", 0, 0);
	getimage(img4, "./�ҵ�ս��zero.png", 0, 0);
	getimage(img5, "./�л�.png", 0, 0);
	getimage(img6, "./�л�boss.png", 0, 0);
	getimage(img7, "./�ӵ�1.png", 0, 0);
	getimage(img8, "./�ӵ�2.png", 0, 0);
	getimage(img9, "./�ӵ�3.png", 0, 0);
	getimage(img10, "./buff.png", 0, 0);

	for ( ; is_run(); delay_fps(60) )
	{
		cleardevice();
//		�����ظ� 
		if(img2_y == 711){
			img2_y = -711;
		}
		if(img2_yy == 711){
			img2_yy = -711;
		}
//		for(int i = 0; i < NUM_MY_BUL; i++){
//			if(mybullet[i].y == (-80) * i){
//				mybullet[i].y = myplane.y;
//				mybullet[i].x = myplane.x;
//			}		
//		}
		putimage(0, img2_y, 400, 711, img2, 0, 0, 400, 711);
		putimage(0, img2_yy, 400, 711, img2, 0, 0, 400, 711);
//		buff�ӳ�ʱ�䣬����һֱ�ӳ� 
		static DWORD t5, t6;
		if(myplane.is_or_no && t6 - t5 > 8000){
			myplane.is_or_no = false;
			t5 = t6;
		}
		t6 = clock();
//		�����ҷ��ɻ�״̬�����Ӧ��ͼ 
		if(!myplane.is_or_no){
			putimage_withalpha(NULL, img3, myplane.x, myplane.y);
		}else{
			putimage_withalpha(NULL, img4, myplane.x, myplane.y);
		}
//		putimage_withalpha(NULL, img3, myplane.x, myplane.y);
//		�����ӵ��Լ��ҷ��ɻ�״̬����Ӧ��ͼ 
		for(int i = 0; i < NUM_MY_BUL; i++){
			if(mybullet[i].is_or_no && !myplane.is_or_no){
				putimage_withalpha(NULL, img7, mybullet[i].x, mybullet[i].y);
			}
			if(mybullet[i].is_or_no && myplane.is_or_no){
				putimage_withalpha(NULL, img8, mybullet[i].x, mybullet[i].y);
			}
		}
//		for(int i = 0; i < NUM_MY_BUL; i++){
//			mybullet[i].y -= 6;		
//		}
//		������ͨ�л�״̬��ͼ 
		for(int i = 0; i < NUM_ENEMY; i++){
			if(enemyplane[i].is_or_no){
				putimage_withalpha(NULL, img5, enemyplane[i].x, enemyplane[i].y);
			}
		}
//		��������������y��������� 
		img2_y += 1;
		img2_yy += 1;
//		����move()���������Ʒɻ����˶� 
		move();
//		���ú������ӵ����ӵ��˶� 
		bulletmove();
//		���Ƶл��������ٶ� 
		static DWORD t3, t4;
		if(t4 - t3 > 1000){
			enemycreate();
			t3 = t4;
		}
		t4 = clock();
		enemymove(); //�л����ƶ�
//		�ﵽ����������boss 
		if(score >= 400 && !bossplane.is_or_no){
			bosscreate();
		}
//		boss���ƶ� 
		bossmove();
		static DWORD t7, t8;
		if(t8 - t7 > 8000){
			bossaction();
			t7 = t8;
		}
		t8 = clock();
		bossbulletmove();
//		���ú���������buff 
		buffcreate();
//		buffͼ����ƶ� 
		buffmove();
//		��ȡ��buff 
		buffget();
//		��ͼ��boss��buff 
		if(bossplane.is_or_no){
			putimage_withalpha(NULL, img6, bossplane.x, bossplane.y);
		}
		if(mybuff.is_or_no){
			putimage_withalpha(NULL, img10, mybuff.x, mybuff.y);
		}
		for(int i = 0; i < NUM_ENEMY_BUL; i++){
			if(enemybullet[i].is_or_no){
				putimage_withalpha(NULL, img9, enemybullet[i].x, enemybullet[i].y);
			}
		}
//		���ú��������ел� 
		hitenemy();
		hitme();
		setcolor(EGERGB(0x0, 0xFF, 0x0));
		setfont(12, 0, "����");
		setbkmode(TRANSPARENT);
		char s[6];
		char t[6];
		char m[6];
		sprintf(s, "%d", score);
		sprintf(t, "%d", myplane.blood);
		sprintf(m, "%d", bossplane.blood);
		outtextxy(0, 0, "�÷�"); 
		outtextxy(30, 0, s);
		outtextxy(0, 15, "Ѫ��"); 
		outtextxy(30, 15, t);
		outtextxy(0, 30, "boss");
		outtextxy(30, 30, m);
//		if(mybuff.is_or_no){
//			outtextxy(0, 45, "yes");
//		}
//		else{
//			outtextxy(0, 45, "no");
//		}
//		if(myplane.is_or_no){
//			outtextxy(0, 60, "yes");
//		}
//		else{
//			outtextxy(0, 60, "no");
//		}
//		���ú�������Ϸʧ�� 
		losegame();
//		���ú�������Ϸ�ɹ� 
		wingame();
//		��֤���ֵ�ѭ�����ţ������ƺ������һЩ�ӳ� 
		if(music.GetPlayStatus() == MUSIC_MODE_STOP){
			music.Play(0);
		}
//		�ж���Ϸʧ�ܻ���ʤ����������Ϸѭ�� 
		if(judge == 3 || judge == 4){
			break;
		}
	}
} 

void initPlayer(){
//	��ʼ���ĸ������� 
	judge = 0;
	dx = 1;
	score = 0; 
	myplane.x = 150;
	myplane.y = 540;
	myplane.blood = 2000;
	myplane.width = 80;
	myplane.height = 129;
	myplane.is_or_no = false;
	for(int i = 0; i < NUM_MY_BUL; i++){
		mybullet[i].x = -60;
		mybullet[i].y = -60;
		mybullet[i].is_or_no = false;
	}
	for(int i = 0; i < NUM_ENEMY; i++){
		enemyplane[i].is_or_no = false;
		enemyplane[i].blood = 200;
		enemyplane[i].width = 50;
		enemyplane[i].height = 89;
	} 
	for(int i = 0; i < NUM_ENEMY_BUL; i++){
		enemybullet[i].is_or_no = false;
	}
	bossplane.is_or_no = false;
	bossplane.blood = 20000;
	bossplane.width = 240;
	bossplane.height = 199; 
	mybuff.is_or_no = false;
	mybuff.width = 36;
	mybuff.height = 42; 
	img2 = newimage();
	img3 = newimage();
	img4 = newimage();
	img5 = newimage();
	img6 = newimage();
	img7 = newimage();
	img8 = newimage();
	img9 = newimage();
	img10 = newimage();
}

void move(){
//	���̽����������û��������Ʒ����Լ��ڵ��ķ��� 
//	���� 
	if(GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W')){
		if(myplane.y > 0){
			myplane.y -= 8;
		}
	}
//	���� 
	if(GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S')){
		if(myplane.y + 129 < 711){
			myplane.y += 8;			
		}
	}
//	���� 
	if(GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A')){
		if(myplane.x > -30){
			myplane.x -= 8;
		}
	}
//	���� 
	if(GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D')){
		if(myplane.x < 350){
			myplane.x += 8;
		}
	}
//	�����ӵ� 
	static DWORD t1 = 0, t2 = 0;
	if(GetAsyncKeyState(VK_SPACE) && t2 - t1 > 200){
		bulletcreate();
		t1 = t2;
	}
	t2 = GetTickCount();
} 

void bulletcreate(){
	for(int i = 0; i < NUM_MY_BUL; i++){
//		��ͨģʽ��һ�η���һ���ӵ� 
		if(!mybullet[i].is_or_no && !myplane.is_or_no) {
			mybullet[i].x = myplane.x + 20;
			mybullet[i].y = myplane.y;
			mybullet[i].is_or_no = true;
			break; 
		}
//		����ģʽ��һ�η��������ӵ� 
		if(!mybullet[i].is_or_no && !mybullet[NUM_MY_BUL - 1 - i].is_or_no && myplane.is_or_no){
			mybullet[i].x = myplane.x + 10;
			mybullet[i].y = myplane.y;
			mybullet[i].is_or_no = true;
			mybullet[NUM_MY_BUL - 1 - i].x = myplane.x + 70;
			mybullet[NUM_MY_BUL - 1 - i].y = myplane.y;
			mybullet[NUM_MY_BUL - 1 - i].is_or_no = true;
			break;
		}
	}
} 

void bulletmove(){
//	�ӵ����ƶ� 
	for(int i = 0; i < NUM_MY_BUL; i++){
		if(mybullet[i].is_or_no){
			mybullet[i].y -= 5;
			if(mybullet[i].y < 0){
				mybullet[i].is_or_no = false;
//				�������� 
			}
		}
	} 
} 

void enemycreate(){
	for(int i = 0; i < NUM_ENEMY; i++){
		if(!enemyplane[i].is_or_no){
			enemyplane[i].is_or_no = true;
			enemyplane[i].x = rand()%(340);
			enemyplane[i].y = -10;
			break;
		}
	} 
} 

void enemymove(){
	for(int i = 0; i < NUM_ENEMY; i++){
		if(enemyplane[i].is_or_no){
			enemyplane[i].y += 1;
			if(enemyplane[i].y > 711){
				enemyplane[i].is_or_no = false;
//				�������� 
			}
		}
	} 
} 

void hitenemy(){
	for(int i = 0; i < NUM_ENEMY; i++){
		if(!enemyplane[i].is_or_no){
			continue;
		}
		for(int j = 0; j < NUM_MY_BUL; j++){
			if(!mybullet[j].is_or_no){
				continue;
			}
			if(mybullet[j].x + 25 > enemyplane[i].x && (mybullet[j].x + 40) < (enemyplane[i].x + enemyplane[i].width + 25)
			&& mybullet[j].y > enemyplane[i].y && mybullet[j].y < enemyplane[i].y + enemyplane[i].height){
				mybullet[j].is_or_no = false;
				enemyplane[i].blood -= 100; 
			}
		}
//		�л������٣����������Ա�֤�����µĵл�
		if(enemyplane[i].blood <= 0){ 
//		ÿ����һ�ܵл���������20 
			score += 20;
			enemyplane[i].is_or_no = false;
			enemyplane[i].blood = 200;
		}
	} 
//	����boss����˺� 
	if(bossplane.blood >= 0  && bossplane.is_or_no){
		for(int j = 0; j < NUM_MY_BUL; j++){
			if(!mybullet[j].is_or_no){
				continue;
			}
			if(mybullet[j].x + 25 > bossplane.x && (mybullet[j].x + 40) < (bossplane.x + bossplane.width + 25)
			&& mybullet[j].y > bossplane.y && mybullet[j].y < bossplane.y + bossplane.height){
				mybullet[j].is_or_no = false;
				bossplane.blood -= 100; 
			}
		}
	} 
} 

void bosscreate(){
	bossplane.x = rand()%(280);
	bossplane.y = -200;
	bossplane.is_or_no = true;
} 

void bossmove(){
	if(bossplane.is_or_no){
		if(bossplane.y <= 0){
			bossplane.y += 1;
		}
//		�����������˶� 
		bossplane.x += dx;
		if(bossplane.x < -120){
			dx = 1;
		}
		if(bossplane.x >= 280){
			dx = -1;
		}
	}
}

void bossaction(){
	if(bossplane.is_or_no){
		for(int i = 0; i < NUM_ENEMY_BUL; i++){
			if(!enemybullet[i].is_or_no){
					enemybullet[i].is_or_no = true;
					enemybullet[i].x = 90 * i;
					enemybullet[i].y = 200;
			}
		}
	}
} 

void bossbulletmove(){
	for(int i = 0; i < NUM_ENEMY_BUL; i++){
		if(enemybullet[i].is_or_no){
			enemybullet[i].y += 5;
			if(enemybullet[i].y > 711){
				enemybullet[i].is_or_no = false;
			}
		}
	}
} 

void hitme(){
	for(int i = 0; i < NUM_ENEMY_BUL; i++){
		if(!enemybullet[0].is_or_no){
			continue;
		}
		if(enemybullet[i].x + 16 > myplane.x && (enemybullet[i].x + 36) < (myplane.x + myplane.width + 16)
		&& enemybullet[i].y > myplane.y && enemybullet[i].y < myplane.y + myplane.height){
			myplane.blood -= 200;
			for(int j = 0; j < NUM_ENEMY_BUL; j++){
				enemybullet[j].is_or_no = false;
			}
		}
	}
} 

void buffcreate(){
	if(!mybuff.is_or_no){
		if(score % 500 == 0 && score > 0){
			mybuff.x = rand()%(370);
			mybuff.y = -40;
			mybuff.is_or_no = true;
		} 
	}
} 

void buffmove(){
	if(mybuff.is_or_no){
		mybuff.y += 1;
		if(mybuff.y > 711){
			mybuff.is_or_no = false;
		}
	}
}

void buffget(){
	if(myplane.x + 30 < mybuff.x + mybuff.width 
		&& myplane.x + myplane.width > mybuff.x + 30 
		&& mybuff.y + mybuff.height < myplane.y + myplane.height 
		&& mybuff.y + mybuff.height > myplane.y ){
			mybuff.is_or_no = false;
			myplane.is_or_no = true;
	}	
} 

void losegame(){
	for(int i = 0; i < NUM_ENEMY; i++){
		if(!enemyplane[i].is_or_no){
			continue;
		}
//		ײ������Ѫ��С�ڵ���0����Ϸ�и� 
		if(myplane.blood <= 0 || 
		(myplane.x + 30 < enemyplane[i].x + enemyplane[i].width 
		&& myplane.x + myplane.width > enemyplane[i].x + 30 
		&& enemyplane[i].y + enemyplane[i].height < myplane.y + myplane.height 
		&& enemyplane[i].y + enemyplane[i].height > myplane.y
		&& enemyplane[i].is_or_no)){
			judge = 3; // ��judge����Ϊ3������ѭ�� 
		}
	}
} 

void wingame(){
//	����boss����Ϸʤ�� 
	if(bossplane.blood <= 0){
		judge = 4;  //��judge����Ϊ4������ѭ�� 
	} 
} 

void mainloop(){
	for( ; is_run(); delay_fps(60)){
		while(judge == 0 && mousemsg()){ // һ��ʼ�Ļ�ӭ���� 
			mouse_msg msg = getmouse();
//			���Կ�ʼʱ����һ��ege�Դ��������Ϣ��صĺ�������ȡһЩ��ť��λ�ã��������Ϳ��Ը��ݰ�ť��ռλ��ģ�ⰴť��Ч���� 
			if(msg.is_left() && msg.is_down() && msg.x > 140 && msg.x < 260 && msg.y > 157 && msg.y < 210){
				judge = 1;
				play(); // �����ť����ʼ��Ϸ 
			}
			else if(msg.is_left() && msg.is_down() && msg.x > 140 && msg.x < 260 && msg.y > 241 && msg.y < 294){
				judge = 2; // ������judge�Ļ���ԭ����ӭ�����д��ڵİ�����λ�Իᷢ������ 
				information(); // �����ť����Ϸ˵�� 
			}
			else if(msg.is_left() && msg.is_down() && msg.x > 140 && msg.x < 260 && msg.y > 320 && msg.y < 372){
				end();  // �����ť���˳���Ϸ 
			}
		} 
//		while(judge == 1){
////			��Ϸʧ�� 
//			for(int i = 0; i < NUM_ENEMY; i++){
//				if(!enemyplane[i].is_or_no){
//					continue;
//				}
//				if(myplane.blood <= 0 || 
//				(myplane.x + 30 < enemyplane[i].x + enemyplane[i].width 
//				&& myplane.x + myplane.width > enemyplane[i].x + 30 
//				&& enemyplane[i].y + enemyplane[i].height < myplane.y + myplane.height 
//				&& enemyplane[i].y + enemyplane[i].height > myplane.y)){
//					img11 = newimage();
//					getimage(img11, "./ʧ��.jpeg", 0, 0);
//					putimage(0, 0, 400, 711, img11, 0, 0, 400, 711);
//					judge = 0;
//					getch();
//					cleardevice();
//					putimage(0, 0, 400, 711, img_back, 0, 0, 800, 1422);
//				}
//			} 
//		}
//		��Ϸ��Ϣҳ���˳�����ʵ�� 
		while(judge == 2 && mousemsg()){
			mouse_msg msg = getmouse();
			if(msg.is_left() && msg.is_down() && msg.x > 24 && msg.x < 67 && msg.y > 23 && msg.y < 35){
				cleardevice();
				putimage(0, 0, 400, 711, img_back, 0, 0, 800, 1422);
				judge = 0;
			}
		}
//		����ʧ�� 
		while(judge == 3 && mousemsg()){
			mouse_msg msg = getmouse();
			img11 = newimage();
			getimage(img11, "./ʧ��.jpeg", 0, 0);
			putimage(0, 0, 400, 711, img11, 0, 0, 400, 711);
			if(msg.is_left() && msg.is_down()){
				cleardevice();
				putimage(0, 0, 400, 711, img_back, 0, 0, 800, 1422);
				judge = 0;	
			}
		}
//		���سɹ� 
		while(judge == 4 && mousemsg()){
			mouse_msg msg = getmouse();
			img12 = newimage();
			getimage(img12, "./ʤ��.jpeg", 0, 0);
			putimage(0, 0, 400, 711, img12, 0, 0, 400, 711);
			if(msg.is_left() && msg.is_down()){
				cleardevice();
				putimage(0, 0, 400, 711, img_back, 0, 0, 800, 1422);
				judge = 0;	
			}
		}
		if(music.GetPlayStatus() == MUSIC_MODE_STOP){
			music.Play(0);
		}
	}
}

void music_haha(){
//	ѡȡ��һ�����Ĵ����֣����������ջ���ͦ����� 
	music.OpenFile("./music1.mp3");
	music.Play();
} 

void information(){
//	������������Ϣͼ 
	cleardevice(); 
	img1 = newimage();
	getimage(img1, "./ͼ1.jpeg", 0, 0);
	putimage(0, 0, 400, 711, img1, 0, 0, 400, 711);
} 

int end(){
//	�ر����֣�����ͼƬ���رմ��� 
	music.Close(); 
	delimage(img1);
	delimage(img2); 
	delimage(img3);
	delimage(img4); 
	delimage(img5);
	delimage(img6); 
	delimage(img7);
	delimage(img8);
	delimage(img9);
	delimage(img10); 
	delimage(img11);
	delimage(img12); 
	delimage(img_back);
	closegraph();
//	������仰����ܽ������̣����bug���ܵ��¶�α������к�Makefile.win���� 
//	����return 0��֪��ΪʲôӦ�ó���ر��˵�����û�� 
	exit(0);
	return 0;
}
