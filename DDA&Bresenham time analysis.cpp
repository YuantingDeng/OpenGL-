#include <GL/gl.h>
#include <GL/glut.h>
#include<stdlib.h>
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<time.h>
#define random(a,b) (rand()%(b-a+1)+a)
#include<windows.h>
using namespace std;

void myinit()
{
    glClearColor(1.0,1.0,1.0,0.0);
    glColor3f(0.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 100.0,0.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void swap(int &a, int &b){
    a = a + b;
    b = a - b;
    a = a - b;
}

void DDA(int x1, int y1, int x2, int y2){
    double k = double(y2-y1)/double(x2-x1);
    double b = y1-k*x1;
    //cout<<"y="<<k<<"x+"<<b<<endl;
    glColor3f(0.0,0.0,0.0);
    if(k>1||k<-1){
        if(y1>y2){
            swap(x1,x2);swap(y1,y2);
        }
        double xi = x1;
        for(int i=y1;i<=y2;i++){
            glVertex2i(int(xi+0.5),i);
            xi+=1/k;
        }
    }
    else{
        if(x1>x2){
            swap(x1,x2);swap(y1,y2);
        }
        double yi = y1;
        for(int i=x1;i<=x2;i++){
            glVertex2i(i,int(yi+0.5));
            yi+=k;
        }
    }
}

void Bresenham(int x1, int y1, int x2, int y2){//该算法要求x1<x2
    if(x1>x2){
        swap(x1,x2);
        swap(y1,y2);
    }
    double k = double(y2-y1)/double(x2-x1);
    double b = y1-k*x1;
    //cout<<"y="<<k<<"x+"<<b<<endl;
    glColor3f(0.0,0.0,0.0);

    double e;
    double k_;
    if(0<=k&&k<=1){

        e = -1;
        int yi = y1;
        for(int i=x1;i<=x2;i++){
            if(e>0){
                yi++;
                e-=2;
            }
            glVertex2i(i,yi);
            e+=k+k;
        }
    }
    if(-1<=k&&k<0){

        e = 1;
        int yi = y1;
        for(int i=x1;i<=x2;i++){
            if(e<=0){
                yi--;
                e+=2;
            }
            glVertex2i(i,yi);
            e+=k+k;
        }
    }
    if(1<k){
        e = -1;
        k_ = 1/k;
        int xi = x1;
        for(int i=y1;i<=y2;i++){
            if(e>0){
                xi++;
                e-=2;
            }
            glVertex2i(xi,i);
            e+=k_+k_;
        }
    }
    if(k<-1){
        e = -1;
        k_ = -1/k;
        int xi = x1;
        for(int i=y1;i>=y2;i--){
            if(e>0){
                xi++;
                e-=2;
            }
            glVertex2i(xi,i);
            e+=k_+k_;
        }
    }

}

int * rand_int_generator(int n, int min, int max){
    int *list = new int[n];
    srand((unsigned)time(NULL));
    for(int i=0;i<n;i++){
        list[i] = random(min,max);
    }
    return list;
}

void display()
{

    glClear(GL_COLOR_BUFFER_BIT);

    double DDA_time = 0;
    double Bresenham_time = 0;
    int n = 1000000;
    int min = 1;
    int max = 1000;
    int *x1_list = rand_int_generator(n, min, max);
    Sleep(1000);
    int *y1_list = rand_int_generator(n, min, max);
    Sleep(1000);
    int *x2_list = rand_int_generator(n, min, max);
    Sleep(1000);
    int *y2_list = rand_int_generator(n, min, max);
    int x1,y1,x2,y2;

    for(int i=0;i<n;i++){
        x1 = x1_list[i];
        y1 = y1_list[i];
        x2 = x2_list[i];
        y2 = y2_list[i];

        if(x1==x2&&y1==y2)
            continue;

        glColor3f(1.0,0.0,0.0);
        glPointSize(1.0f);
        glBegin(GL_POINTS);

            clock_t start,finish;
            double totaltime;
            start = clock();
            DDA(x1,y1,x2,y2);//DDA Algorithm
            finish = clock();
            DDA_time += double(finish-start)/CLOCKS_PER_SEC;

            start = clock();
            Bresenham(x1,y1,x2,y2);
            finish = clock();
            Bresenham_time += double(finish-start)/CLOCKS_PER_SEC;

        glEnd();

        //glFlush();

    }
    cout<<"The average time of DDA is "<<DDA_time<<"μs and "
        <<"that of Bresenham is "<<Bresenham_time<<"μs"<<endl;
    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);

    glutInitWindowSize(1000,500);
    glutInitWindowPosition(0,0);
    glutCreateWindow("DDA and Bresenham");
    glutDisplayFunc(display);

    myinit();
    glutMainLoop();
    return 0;
}



