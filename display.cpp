#include"display.h"
#include<math.h>
#include<iostream>
using namespace std;
window w;
void init()
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_FLAT);
}
void changeSize(int w, int h)
{

   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluOrtho2D (0, (GLdouble) w/2,-(GLdouble) h/2 , (GLdouble) h/2);
}
void display(void)
 {
     glClear (GL_COLOR_BUFFER_BIT);
     for(int i = 100; i<=200;i++)
     w.plotpixel(i,i, 1.0,1.0,0.0);
     glFlush();


}
window::window()
{

}
window::window(int a , int b ,int c ,int d,char s[10])
    {
        width = a ;
        height = b;
        screenpos_x = c;
        screenpos_y = d;
       // name = s;

        glutInitDisplayMode (GLUT_SINGLE | GLUT_RGBA);
        glutInitWindowPosition( screenpos_x, screenpos_y);
        glutInitWindowSize(width ,height );
        glutCreateWindow(" kal ");
        init();
        glutDisplayFunc(display); // Tell GLUT to use the method "display" for rendering
        glutReshapeFunc(changeSize);
        glutMainLoop();

}
void window:: plotpixel(int x_pos ,int y_pos,int r ,int g ,int b )
{
    glColor3f(r,g,b);
    glBegin(GL_POINTS);
    glVertex2i(x_pos,y_pos);
    glEnd();
}
