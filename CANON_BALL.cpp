#include "graphics.h"
#include <iostream>
#include <math.h>
#include <stdlib.h> 
#include <ctype.h>
#include<vector>
#include <random>
using namespace std;




float scale = 1.5;
class Ball {


    int color;
    float radius =15;
    double x, y;
    double vx, vy; 
    
public:
    void init( double x0, double vx0) {
        
        
        color =  rand() % (15);
        x = x0;
        y =0;
        vx = vx0;
        vy = 0;
       
    }
    int getBound_left() {
        return x-radius;
    }
    int getBound_right() {
        return x + radius;
    }
    int getBound_top() {
        return y - radius;
    }
    int getBound_bottom() {
        return y + radius;
    }
    void setVX(double vx0) {
        vx = vx0;
        
    }
    void setVY( double vy0) {
        vy = vy0;
    }
    void increaseRadius() {
        radius +=0.1;
    }
    float getRadious() {
        return radius;
    }
    int getx() {

        return x;
    }
    int gety() {

        return y;
    }
    void update() {
        double ax = 0; 
        double ay = 0.1 ;
        vx += ax ; 
        vy += ay; 
        x += vx ; 
        y += vy ;

        
        
    }
    void draw() {
        setlinestyle(0, 0, 0);
        setfillstyle(SOLID_FILL, color);
        fillellipse(x, y, radius, radius);
    }
};

class Bullet {

    int x, y;
    int radius = 4;
    int velocity = 20;
public:


   

    int getx() {

        return x;
    }
    int gety() {

        return y;
    }
    void init(int x,int y, float scale) {
        this->x = x;
        this->y = (y  - scale * 50);
    }
    void update() {
         y += -velocity;

        
    }


   
    void draw() {
        circle(x, y, radius);
    }

};



class Canon {


    int x, y = 100;
    
    
    float angle = 0;
    int r = 8;
    int points[10] = {0 ,0  ,        0 , 0   ,      0, 0 ,     0  ,0       ,0 ,0  };

    
public:

    
    int getBound_left() {
        return points[6];
    }
    int getBound_right() {
        return points[4];
    }
    int getBound_top(int maxy) {
        return points[1];
    }
    
    void update( int maxy,  int x, int y) {

        points[0] = x- scale * 5;
        points[1] = (maxy - scale * 40) - scale * 15;

        points[2] =x + scale * 5;
        points[3] = (maxy - scale * 40) - scale * 15;

        points[4] = x+ scale * 10;
        points[5] = (maxy - scale * 40) + scale * 15;

        points[6] = x- scale * 10;
        points[7] = (maxy - scale * 40) + scale * 15;

        points[8] = x- scale * 5;
        points[9] = (maxy - scale * 40) - scale * 15;


        
        
        
    }
    void draw() {
        setlinestyle(0, 0, 0);
        setfillstyle(SOLID_FILL, BLACK);
        fillpoly(5, points);

       


        setfillstyle(SOLID_FILL, LIGHTGRAY);
        fillellipse(points[4], points[5], scale * r, scale * r);
        fillellipse(points[6], points[7], scale * r, scale * r);
        setcolor(BLACK);
        setlinestyle(0, 0, 3);
        angle = points[4] / (2 * 3.14 * r);
        for (int i = 0; i < 3; i += 2) {
            for (int j = 0; j < 3; j++) {

                line(points[i + 4], points[i + 5], points[i + 4] + scale * (r)*cos(angle + j * 90), points[i + 5] + scale * (r)*sin(angle + j * 90));


            }
        }
    }

    
};
void lose(int score , int maxx ,int maxy) {
    char str[3];
    cleardevice();
    settextstyle(0,0,5);
    bar3d(maxx / 2 - 170, maxy / 2 - 10, maxx / 2 + 170, maxy / 2 + 80 ,10 ,7);
    
    outtextxy(maxx / 2-160, maxy / 2, "YOU LOSE");
    settextstyle(0, 0, 3);
    
    outtextxy(maxx / 2 - 160, maxy / 2+50, "YOUR SCORE:");
    sprintf(str, "%d", score);
    
    outtextxy(maxx / 2 + 130, maxy / 2+50, str);
    setfillstyle(0, WHITE);

   
}
int main() {

    
    
    vector < Bullet* > bullets;
    vector < Ball* > balls;

    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    int maxx = getmaxx(); //screen width
    int maxy = getmaxy(); //screen height
    
    Canon canon;

    int score = 0;
    char str[3];
    
    setbkcolor(CYAN);
    int t = 0;
    
    Ball* ball = new Ball();

    ball->init(rand() % (maxx), 1+ rand() % (1));

    balls.push_back(ball);
    bool losed = false;
    while (!losed) {
        
        cleardevice();
        
        sprintf(str, "%d" , score);
        outtextxy(0, 0, "SCORE:");
        outtextxy(70,0,str);
        if (t == 300) {
            Ball* ball = new Ball();

            ball->init(rand() % (maxx),2+rand() % (2));

            balls.push_back(ball);
        }

       if (t % 10 == 0  ) {
            Bullet* bullet = new Bullet();

            bullet->init(mousex(), maxy, scale);

            bullets.push_back(bullet);
        }


        for (int i = 0; i < bullets.size(); i++) {
            
            Bullet* bullet = bullets[i];
            
            bullet->update();
            
            if (bullet->gety() < 0) {
                bullets.erase(bullets.begin() + i);
                delete(bullet);
            }
            
        }

        for (int i = 0; i < bullets.size(); i++) {

            Bullet* bullet = bullets[i];
            int bullet_X = bullet->getx();
            int bullet_Y = bullet->gety();
            for (int i = 0; i < balls.size(); i++) {

                Ball* ball = balls[i];

                if (bullet_X >= ball->getBound_left() && bullet_X <= ball->getBound_right()&&   bullet_Y <= ball->getBound_bottom()) {
                
                    ball->increaseRadius();

                    
                }
                if (ball->getRadious() > 30) {
                    balls.erase(balls.begin() + i);
                    delete(ball);

                    score++;
                }
            }

        }


        for (int i = 0; i < balls.size(); i++) {
            
            Ball* ball = balls[i];

            ball->update();
           
            if ( ball->getBound_right() >= canon.getBound_left()  && ball->getBound_left() <= canon.getBound_right()&& ball->getBound_bottom() >=canon.getBound_top(maxy)) {
            
                lose(score ,maxx,maxy);
                losed = true;
                
                
            }
            
            if (ball->getx() >= maxx) {

                ball->setVX(-2);
                
            }
            if (ball->getx() <= 0) {

                ball->setVX(2);

            }
            if (ball->gety() >= maxy - 40) {

                ball->setVY(-9);
                
            }

            

            
           
        }


        canon.update(maxy, mousex(), mousey());
        
        
        
        for (int i = 0; i < bullets.size(); i++) {

            Bullet* bullet = bullets[i];
            bullet->draw();
            for (int i = 0; i < balls.size(); i++) {

                Ball* ball = balls[i];

                ball->draw();
                canon.draw();
                
                
                
            }

            setfillstyle(1, GREEN);
            line(0, maxy - 26, maxx, maxy - 26);
            floodfill(1, maxy - 1, 0);
            
        }
        
        if (t == 300) {
            t = 0;
        }
         t ++;

        delay(1);
    }

    getch();
    //closegraph();
    return 0;
}