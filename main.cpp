#include<stdio.h>
#include<string.h>
#include<time.h>
#include<graphics.h>
//使用EGE图形库，哈哈，终于用上图形库了
//敌机数量、我方子弹的数量、敌方子弹的数量 
#define NUM_ENEMY 12 
#define NUM_MY_BUL 50 
#define NUM_ENEMY_BUL 5
//导入背景图片，美观一点哈 
PIMAGE img_back;
//另外两个页面的背景图片 
PIMAGE img1,img2;
//我方战机 
PIMAGE img3,img4;
//敌方战机
PIMAGE img5,img6; 
//炮弹 
PIMAGE img7,img8,img9;
//增强道具 
PIMAGE img10;
//游戏胜利以及游戏失败的图片 
PIMAGE img11,img12;
//导入音乐，有趣一些 
MUSIC music;
//初始化设计游戏界面 
void design(); 
//点击开始游戏，进入真正的游戏界面 
void play();
//初始化各战力单位 
void initPlayer();
//通过键盘操作飞机移动 
void move();
//产生子弹 
void bulletcreate(); 
//子弹移动 
void bulletmove();
//敌机的产生 
void enemycreate();
//敌机的移动 
void enemymove();
//子弹击中敌机 
void hitenemy();
//产生boss 
void bosscreate();
//boss的移动 
void bossmove();
//没有对抗有啥意思，boss发射子弹 
void bossaction();
//boss子弹移动 
void bossbulletmove();
//击中我方飞机 
void hitme();
//游戏buff产生 
void buffcreate();  
//游戏buff的移动 
void buffmove();
//游戏buff获得以及产生作用 
void buffget();
//游戏失败 
void losegame();
//游戏胜利 
void wingame();
//循环进行 
void mainloop();
//游戏没有声音太无聊？ 
void music_haha();
//一些游戏相关的信息 
void information(); 
// 游戏结束
int end();
//切换页面时，鼠标检测发生变化，用一个judge判断当前所处页面（好像没想出来什么好的解决方法） 
//0表示主页面，1表示开始游戏界面，2表示游戏说明界面 ，3表示游戏失败退出游戏界面，4表示游戏胜利退出游戏界面 
int judge = 0;
//定义一个分数，用来控制boss的出现 
int score = 0; 
//定义一个boss的移动方向 
int dx = 1;
// 利用结构体封装我方飞机各种属性 
typedef struct plane{
//	x、y是对坐标的描述 
	int x;
	int y;
//	blood是剩余的血量 
	int blood;
//	飞机的宽度和高度 
	int width;
	int height;
//	飞机的状态 
	bool is_or_no;
} Plane;
//定义一个Plane类型的变量myplane，作为玩家操控的战机 
Plane myplane;
//定义多个Plane类型的变量，作为出现的敌机 
Plane enemyplane[NUM_ENEMY]; 
//创建一个boss 
Plane bossplane;
//buff基本行为与敌机类似，直接套用一个Plane类型 
Plane mybuff;
//再次利用结构体封装子弹属性 
typedef struct bullet{
//	x、y表示子弹的坐标 
	int x;
	int y;
//	表示子弹的状态 
	bool is_or_no;
} Bullet;
//我方子弹 
Bullet mybullet[NUM_MY_BUL];
//敌方子弹 
Bullet enemybullet[NUM_ENEMY_BUL];

//主函数入口 
int main(){
//	调用初始化，开始界面 
	design();
//	添加音乐注入灵魂 
	music_haha();
//游戏的循环主体部分
	mainloop(); 
//	游戏结束 
	end();
} 



void design(){
//	设计窗口的大小，适应我选择的背景图片的1/2 
	initgraph(400, 711, 0);
	img_back = newimage();
	getimage(img_back, "./实验图片.jpeg", 0, 0);
//	设置游戏标题为“飞机大战（夏日清凉版）” 
	setcaption("飞机大战（夏日清凉版o(*￣︶￣*)o）"); 
//	背景图片太大了，缩小1/2，还不错，不愧是我的审美，哈哈 
	putimage(0, 0, 400, 711, img_back, 0, 0, 800, 1422);
}

void play(){
//	拼接了两张一样的图片，形成一个滚动前进的视觉效果，这里初始化两张图片的y坐标 
	int img2_y = 0;
	int img2_yy = -711;
	initPlayer(); //调用初始化函数，初始化游戏的各项参数
//	获得所需的图片 
	getimage(img2, "./图2.jpeg", 0, 0);
	getimage(img3, "./我的战机.png", 0, 0);
	getimage(img4, "./我的战机zero.png", 0, 0);
	getimage(img5, "./敌机.png", 0, 0);
	getimage(img6, "./敌机boss.png", 0, 0);
	getimage(img7, "./子弹1.png", 0, 0);
	getimage(img8, "./子弹2.png", 0, 0);
	getimage(img9, "./子弹3.png", 0, 0);
	getimage(img10, "./buff.png", 0, 0);

	for ( ; is_run(); delay_fps(60) )
	{
		cleardevice();
//		背景重复 
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
//		buff加持时间，否则一直加持 
		static DWORD t5, t6;
		if(myplane.is_or_no && t6 - t5 > 8000){
			myplane.is_or_no = false;
			t5 = t6;
		}
		t6 = clock();
//		根据我方飞机状态贴相对应的图 
		if(!myplane.is_or_no){
			putimage_withalpha(NULL, img3, myplane.x, myplane.y);
		}else{
			putimage_withalpha(NULL, img4, myplane.x, myplane.y);
		}
//		putimage_withalpha(NULL, img3, myplane.x, myplane.y);
//		根据子弹以及我方飞机状态贴对应的图 
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
//		根据普通敌机状态贴图 
		for(int i = 0; i < NUM_ENEMY; i++){
			if(enemyplane[i].is_or_no){
				putimage_withalpha(NULL, img5, enemyplane[i].x, enemyplane[i].y);
			}
		}
//		背景滚动，利用y坐标的增加 
		img2_y += 1;
		img2_yy += 1;
//		调用move()函数，控制飞机的运动 
		move();
//		调用函数，子弹的子弹运动 
		bulletmove();
//		控制敌机产生的速度 
		static DWORD t3, t4;
		if(t4 - t3 > 1000){
			enemycreate();
			t3 = t4;
		}
		t4 = clock();
		enemymove(); //敌机的移动
//		达到条件，创建boss 
		if(score >= 400 && !bossplane.is_or_no){
			bosscreate();
		}
//		boss的移动 
		bossmove();
		static DWORD t7, t8;
		if(t8 - t7 > 8000){
			bossaction();
			t7 = t8;
		}
		t8 = clock();
		bossbulletmove();
//		调用函数，创建buff 
		buffcreate();
//		buff图标的移动 
		buffmove();
//		获取到buff 
		buffget();
//		贴图，boss和buff 
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
//		调用函数，击中敌机 
		hitenemy();
		hitme();
		setcolor(EGERGB(0x0, 0xFF, 0x0));
		setfont(12, 0, "宋体");
		setbkmode(TRANSPARENT);
		char s[6];
		char t[6];
		char m[6];
		sprintf(s, "%d", score);
		sprintf(t, "%d", myplane.blood);
		sprintf(m, "%d", bossplane.blood);
		outtextxy(0, 0, "得分"); 
		outtextxy(30, 0, s);
		outtextxy(0, 15, "血量"); 
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
//		调用函数，游戏失败 
		losegame();
//		调用函数，游戏成功 
		wingame();
//		保证音乐的循环播放，但是似乎会产生一些延迟 
		if(music.GetPlayStatus() == MUSIC_MODE_STOP){
			music.Play(0);
		}
//		判断游戏失败或者胜利并跳出游戏循环 
		if(judge == 3 || judge == 4){
			break;
		}
	}
} 

void initPlayer(){
//	初始化的各个参数 
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
//	键盘交互，利用用户按键控制飞行以及炮弹的发射 
//	上移 
	if(GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W')){
		if(myplane.y > 0){
			myplane.y -= 8;
		}
	}
//	下移 
	if(GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S')){
		if(myplane.y + 129 < 711){
			myplane.y += 8;			
		}
	}
//	左移 
	if(GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A')){
		if(myplane.x > -30){
			myplane.x -= 8;
		}
	}
//	右移 
	if(GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D')){
		if(myplane.x < 350){
			myplane.x += 8;
		}
	}
//	发射子弹 
	static DWORD t1 = 0, t2 = 0;
	if(GetAsyncKeyState(VK_SPACE) && t2 - t1 > 200){
		bulletcreate();
		t1 = t2;
	}
	t2 = GetTickCount();
} 

void bulletcreate(){
	for(int i = 0; i < NUM_MY_BUL; i++){
//		普通模式，一次发射一发子弹 
		if(!mybullet[i].is_or_no && !myplane.is_or_no) {
			mybullet[i].x = myplane.x + 20;
			mybullet[i].y = myplane.y;
			mybullet[i].is_or_no = true;
			break; 
		}
//		进化模式，一次发射两发子弹 
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
//	子弹的移动 
	for(int i = 0; i < NUM_MY_BUL; i++){
		if(mybullet[i].is_or_no){
			mybullet[i].y -= 5;
			if(mybullet[i].y < 0){
				mybullet[i].is_or_no = false;
//				过界后回收 
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
//				过界后回收 
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
//		敌机被击毁，参数重置以保证产生新的敌机
		if(enemyplane[i].blood <= 0){ 
//		每击毁一架敌机分数增长20 
			score += 20;
			enemyplane[i].is_or_no = false;
			enemyplane[i].blood = 200;
		}
	} 
//	对于boss造成伤害 
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
//		控制其左右运动 
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
//		撞机或者血量小于等于0，游戏判负 
		if(myplane.blood <= 0 || 
		(myplane.x + 30 < enemyplane[i].x + enemyplane[i].width 
		&& myplane.x + myplane.width > enemyplane[i].x + 30 
		&& enemyplane[i].y + enemyplane[i].height < myplane.y + myplane.height 
		&& enemyplane[i].y + enemyplane[i].height > myplane.y
		&& enemyplane[i].is_or_no)){
			judge = 3; // 将judge设置为3，跳出循环 
		}
	}
} 

void wingame(){
//	消灭boss，游戏胜利 
	if(bossplane.blood <= 0){
		judge = 4;  //将judge设置为4，跳出循环 
	} 
} 

void mainloop(){
	for( ; is_run(); delay_fps(60)){
		while(judge == 0 && mousemsg()){ // 一开始的欢迎界面 
			mouse_msg msg = getmouse();
//			可以开始时调用一下ege自带的鼠标信息相关的函数，获取一些按钮的位置，接下来就可以根据按钮所占位置模拟按钮的效果了 
			if(msg.is_left() && msg.is_down() && msg.x > 140 && msg.x < 260 && msg.y > 157 && msg.y < 210){
				judge = 1;
				play(); // 点击按钮，开始游戏 
			}
			else if(msg.is_left() && msg.is_down() && msg.x > 140 && msg.x < 260 && msg.y > 241 && msg.y < 294){
				judge = 2; // 不利用judge的话，原本欢迎界面中存在的按键部位仍会发挥作用 
				information(); // 点击按钮，游戏说明 
			}
			else if(msg.is_left() && msg.is_down() && msg.x > 140 && msg.x < 260 && msg.y > 320 && msg.y < 372){
				end();  // 点击按钮，退出游戏 
			}
		} 
//		while(judge == 1){
////			游戏失败 
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
//					getimage(img11, "./失败.jpeg", 0, 0);
//					putimage(0, 0, 400, 711, img11, 0, 0, 400, 711);
//					judge = 0;
//					getch();
//					cleardevice();
//					putimage(0, 0, 400, 711, img_back, 0, 0, 800, 1422);
//				}
//			} 
//		}
//		游戏信息页面退出功能实现 
		while(judge == 2 && mousemsg()){
			mouse_msg msg = getmouse();
			if(msg.is_left() && msg.is_down() && msg.x > 24 && msg.x < 67 && msg.y > 23 && msg.y < 35){
				cleardevice();
				putimage(0, 0, 400, 711, img_back, 0, 0, 800, 1422);
				judge = 0;
			}
		}
//		过关失败 
		while(judge == 3 && mousemsg()){
			mouse_msg msg = getmouse();
			img11 = newimage();
			getimage(img11, "./失败.jpeg", 0, 0);
			putimage(0, 0, 400, 711, img11, 0, 0, 400, 711);
			if(msg.is_left() && msg.is_down()){
				cleardevice();
				putimage(0, 0, 400, 711, img_back, 0, 0, 800, 1422);
				judge = 0;	
			}
		}
//		过关成功 
		while(judge == 4 && mousemsg()){
			mouse_msg msg = getmouse();
			img12 = newimage();
			getimage(img12, "./胜利.jpeg", 0, 0);
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
//	选取了一首轻快的纯音乐，与炎炎夏日还是挺搭配的 
	music.OpenFile("./music1.mp3");
	music.Play();
} 

void information(){
//	清屏，贴上信息图 
	cleardevice(); 
	img1 = newimage();
	getimage(img1, "./图1.jpeg", 0, 0);
	putimage(0, 0, 400, 711, img1, 0, 0, 400, 711);
} 

int end(){
//	关闭音乐，销毁图片，关闭窗口 
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
//	加上这句话后才能结束进程，这个bug可能导致多次编译运行后Makefile.win报错 
//	单单return 0不知道为什么应用程序关闭了但进程没有 
	exit(0);
	return 0;
}
