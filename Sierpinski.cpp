#include <GL/gl.h>
#include <GL/glut.h>
#include<stdlib.h>
int IterNum = 50000, Width=50, Height = 50;
void myinit()
{
    // attributes
    glClearColor(1.0,1.0,1.0,1.0);//背景色
    glColor3f(0.0,1.0,0.0);//绘制颜色为红色

    // set up viewing
    glMatrixMode(GL_PROJECTION);//即将对投影进行相关操作
    glLoadIdentity();//把当前矩阵设置为单位矩阵
    gluOrtho2D(0.0, 100.0,0.0, 100.0);//窗口的左右上下
    glMatrixMode(GL_MODELVIEW);//设置当前矩阵为模型视图矩阵
}

void display()
{
    glPointSize(3.0);//让点粗一点，可更好地看到实现过程

    GLfloat vertices[3][3] = {{0.0,0.0,0.0}, {25.0, 50.0,0.0}, {50.0,0.0,0.0}};
    // an arbitrary triangle in the plane z = 0;
    GLfloat p[3] = {100.0, 100.0, 0.0};//这个点在三角形外面
    // or set any desired initial point which is inside the triangle;
    int  j,k;
    int  rand();
    glBegin(GL_POINTS);//定义一个OpenGL图元
    for (k = 0; k < IterNum; k++)
    {
        /* pick a random vertex from 0, 1, 2*/
        j = rand()%3;
        // compute new location;
        p[0] = (p[0]+vertices[j][0])/2;
        p[1] = (p[1]+vertices[j][1])/2;
        // display new point

        glVertex3fv(p);//画出了5000个点
    }
    glEnd();
    glFlush();//清缓冲
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);//初始化GLUT库
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    //初始化窗口 单缓冲区,深度缓冲区RGB

    glutInitWindowSize(500,500);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Sierpinski gasket");
    glutDisplayFunc(display);
    //登记回调函数 画图时需要使用

    myinit();
    glutMainLoop();//使程序无限循环直到窗口关闭
    return 0;
}


