#include <GL/gl.h>
#include <GL/glut.h>
#include<stdlib.h>
int IterNum = 50000, Width=50, Height = 50;
void myinit()
{
    // attributes
    glClearColor(1.0,1.0,1.0,1.0);//����ɫ
    glColor3f(0.0,1.0,0.0);//������ɫΪ��ɫ

    // set up viewing
    glMatrixMode(GL_PROJECTION);//������ͶӰ������ز���
    glLoadIdentity();//�ѵ�ǰ��������Ϊ��λ����
    gluOrtho2D(0.0, 100.0,0.0, 100.0);//���ڵ���������
    glMatrixMode(GL_MODELVIEW);//���õ�ǰ����Ϊģ����ͼ����
}

void display()
{
    glPointSize(3.0);//�õ��һ�㣬�ɸ��õؿ���ʵ�ֹ���

    GLfloat vertices[3][3] = {{0.0,0.0,0.0}, {25.0, 50.0,0.0}, {50.0,0.0,0.0}};
    // an arbitrary triangle in the plane z = 0;
    GLfloat p[3] = {100.0, 100.0, 0.0};//�����������������
    // or set any desired initial point which is inside the triangle;
    int  j,k;
    int  rand();
    glBegin(GL_POINTS);//����һ��OpenGLͼԪ
    for (k = 0; k < IterNum; k++)
    {
        /* pick a random vertex from 0, 1, 2*/
        j = rand()%3;
        // compute new location;
        p[0] = (p[0]+vertices[j][0])/2;
        p[1] = (p[1]+vertices[j][1])/2;
        // display new point

        glVertex3fv(p);//������5000����
    }
    glEnd();
    glFlush();//�建��
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);//��ʼ��GLUT��
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    //��ʼ������ ��������,��Ȼ�����RGB

    glutInitWindowSize(500,500);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Sierpinski gasket");
    glutDisplayFunc(display);
    //�Ǽǻص����� ��ͼʱ��Ҫʹ��

    myinit();
    glutMainLoop();//ʹ��������ѭ��ֱ�����ڹر�
    return 0;
}


