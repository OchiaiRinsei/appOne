#define _SORT
#ifdef _SORT
#include"libOne.h"
void gmain() {
	window(1100, 1000);
	const int num = 20;
	int score[num];
	int r, c;
	for (int i = 0; i < num; i++) {
		score[i] = random() % 1001;
	}
	while (notQuit) {
		clear(60);
		if (isTrigger(KEY_A)) {
			for (int i = 0; i < num; i++) {
				score[i] = random() % 1001;
			}
		}

		if (isTrigger(KEY_D)) {
			//r(一番大きい)とc(比較対象)
			for (r = 0; r < num - 1; r++) {
				for (c = r + 1; c < num; c++) {
					//rとcでcがおおきかったら交換する
					if (score[r] < score[c]) {
						//2つの変数を一気に交換はできないのでwをはさむ
						int w = score[r];
						score[r] = score[c];
						score[c] = w;
					}
				}
			}
		}

		for (int i = 0; i < num; i++) {
			print(score[i]);
			rect(100, 50 * i, score[i], 40);
		}
	}

}
#endif
#ifdef _SHOOT
#include"libOne.h"
void gmain() {
	window(1920, 1080, full);
	//
	angleMode(DEGREES);
	struct PLAYER {
		float px, py, w, h, vx,ofsY;
	};
	struct BULLET {
		//
		float px, py, w, h,vx, vy,deg;
		int hp = 0;
	};
	struct PLAYER p;
	p.px = width / 2;
	p.py = height - 150;
	p.w = 100;
	p.h = 200;
	p.vx = 10;
	p.ofsY = -110;
	const int numBullets = 10;
	struct BULLET b[numBullets];
	for (int i = 0; i < numBullets; i++) {
		b[i].px = p.px;
		b[i].py = p.py;
		b[i].w = 20;
		b[i].h = 40;
		//
		b[i].deg = random() % 181;
		b[i].vx = cos(b[i].deg)*5;
		b[i].vy = -10;
	}

	while (notQuit) {
		if (isPress(KEY_A)) { p.px += -p.vx; }
		if (isPress(KEY_D)) { p.px += p.vx; }

		if (isTrigger(KEY_SPACE)) {
			for (int i = 0; i < numBullets; i++) {
				if (b[i].hp == 0) {
					b[i].hp = 1;
					b[i].px = p.px;
					b[i].py = p.py + p.ofsY;
					i = numBullets;
				}
			}
		}
		for (int i = 0; i < numBullets; i++) {
			if (b[i].hp > 0) {
				//
				b[i].px += b[i].vx;
				b[i].py += b[i].vy;
				//ウィンドウの外に出た
				if (b[i].py < -b[i].h) {
					b[i].hp = 0;
				}
			}
		}

		clear();
		rectMode(CENTER);
		rect(p.px, p.py, p.w, p.h);
		for (int i = 0; i < numBullets; i++) {
			if (b[i].hp > 0) {
				rect(b[i].px, b[i].py, b[i].w, b[i].h);
			}
		}
	}
}

#endif
#ifdef _FACE
#include"libOne.h"
#include"face.h"
void gmain() {
	window(1920, 1080, full);
	float px = width / 2;
	float py = height / 2;
	float angle = 0;
	int sw = 1;
	float ofsX = 100;
	float ofsY = 100;


	while (notQuit) {
		ofsX = width / 2 - mouseX;
		ofsY = height / 2 - mouseY;
		if (isTrigger(KEY_SPACE)) { sw = 1 - sw; }
		angle += 0.01f;
		clear(60, 120, 240);
		strokeWeight(10);
		for (int i = -5; i <= 5; i++) {
			if (sw == 1) {
				roundFace(px + ofsX * i, py + ofsY*i);
			}
			else {
				squareFace(px + ofsX * i, py + ofsY*i, angle);
			}
		}
	}
}
#endif
#ifdef  _HPGAUGE
#include"libOne.h"
void gmain() {
	window(1920, 1080, full);
	//DATA
	struct COLOR green = { 0,255,0 };
	struct COLOR yellow = { 255,255,0 };
	struct COLOR red = { 255,0,0 };
	struct COLOR color = green;

	int hpMax = 500;
	int hp = hpMax;
	int hpWarning = hpMax * 0.3f;
	int hpDanger = hpMax * 0.1f;
	float px = 700;
	float py = 200;
	float h = 60;
	while (notQuit) {
		if (hp == 0 && isTrigger(KEY_SPACE)) { hp = hpMax; }
		if (hp > 0) { hp -= 2; }

		if (hp > hpWarning) { color = green; }
		else if (hp > hpDanger) { color = yellow; }
		else { color = red; }

		clear(74, 84, 89);
		fill(128);
		rect(px, py, hpMax, h);
		fill(color);
		rect(px, py, hp, h);
		if (hp <= 0) {
			textSize(100);
			fill(255, 0, 0);
			text("Game Over", 700, 400);
		}
	}
}
#endif
#ifdef  _LIFE
#include"libOne.h"
void gmain() {
	window(1920, 1080, full);
	//データ
	int life = 5;
	float px = 700;
	float py = 200;
	float radius = 50;
	float space = 100;
	while (notQuit) {
		//データ更新
		if (isTrigger(KEY_A)) { life--; }
		if (isTrigger(KEY_D)) { life++; }
		//描画
		clear(74, 84, 89);
		fill(255, 255, 0);
		print((let)"life=" +life);

		strokeWeight(20);
		stroke(255);
		//while バージョン
		int i = 0;
		fill(255, 200, 200);
		while (i < life) {
			float offsetX = space * i;
			circle(px + offsetX, py, radius * 2);
			i++;
		}
		//for バージョン
		fill(160, 200, 200);
		for (int i = 0; i < life; i++) {
			float offsetX = space * i;
			float offsetY = space * 2;
			circle(px + offsetX, py + offsetY, radius * 2);
		}
	}
}
#endif
#ifdef _MOVE
#include"libOne.h"
void gmain(){
	window(1920,1080,full);
	float px = 1920 / 2;
	float py = 1080 / 2;
	float radius = 150;
	float vx = 10;
	float len = radius / 1.4142f * 2;
	float sw = radius / 8;
	float angle = 0;
	float angleSpeed = 0.03f;
	int R = 150;
	int G = 150;
	int B = 150;
	int RChenge = 50;
	int GChenge = -50;
	int BChenge = 50;



	while (notQuit) {
		px += vx; 
		angle += angleSpeed;
		if(px > 1920 || px < 0) { 
		   vx = -vx; 
		   angleSpeed = -angleSpeed;
		   RChenge = -RChenge;
		   GChenge = -GChenge;
		   BChenge = -BChenge;

		}
		clear(60);
		strokeWeight(sw);
		stroke(R+RChenge, G+GChenge, B+BChenge);
		circle(px, py, radius * 2);
		rectMode(CENTER);
		rect(px, py, len, len, angle);
		strokeWeight(sw * 4);
		point(px, py);
		strokeWeight(sw);
		line(1920 / 2, 0, px, py);


	}
}
#endif