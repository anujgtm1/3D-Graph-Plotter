#ifndef DISP_H_INCLUDED
#define DISP_H_INCLUDED

#endif // DISP_H_INCLUDED
#include <GL/glut.h>
#include <GL/gl.h>
#include <string.h>
#include<iostream>
#include<cmath>
const int width=960;
const int height=720;
using namespace std;
float Zbuffer[width][height];

//Initialize all the pixels in Zbuffer with max. depth value
void clear_Zbuffer()
{
    for(int i=0;i<width;i++)
    {
        for(int j=0;j<height;j++)
        {
            Zbuffer[i][j]=10;
        }
    }
}
void Line(float x1,float y1,float x2,float y2,float r,float g,float b)
{
    glColor3f(r,g,b);
    glBegin(GL_LINES);
    glVertex2f(x1+250,y1+200);
    glVertex2f(x2+250,y2+200);
    glEnd();
}
//returns the Z component of the cross product of 2 vectors
float crossZ(float x1,float y1,float x2,float y2)
{
    return x1*y2-y1*x2;
}
/*void fillTriangle(int x1, int y1,int x2,int y2,int x3,int y3,float r,float g,float b)
{
    glColor3f (r,g,b);
    glBegin (GL_TRIANGLES);
    glVertex2i (x1+50,y1-200);
    glVertex2i (x2+50,y2-200);
    glVertex2i (x3+50,y3-200);
    glEnd ();
}*/
 /*int floorceil(float x)
     {

     if(x-int(x)<0.5)
     {
         x=floor(x);
     }
     else
        x=ceil(x);
        return x;
}*/
//float counter=0;
void fillTriangle(float an,float bn,float cn,float d,float x1,float y1,float x2,float y2,float x3,float y3,float r,float g,float b)
{
    int xmax,xmin,ymax,ymin;
    float x,y,z;
    //finding the smallest bounding rectangle that bounds the triangle with vertices x1 y1 x2 y2 x3 y3
    xmax=max(x1,max(x2,x3));   //finds max of x1 x2 x3
    xmin=min(x1,min(x2,x3));   //finds min of x1 x2 x3
    ymax=max(y1,max(y2,y3));
    ymin=min(y1,min(y2,y3));
    glColor3f(r,g,b);
    for(int j=ymin;j<=ymax;j++)
    {
        if(j<0) continue;  //Caution so that the index for zbuffer array doesnt become negative
        if(j>=height) break;
        for(int i=max(xmin,0);i<=xmax;i++)
        {
            if(i>=width) break;
            x=crossZ(i-x1,j-y1,x2-x1,y2-y1);
            y=crossZ(i-x2,j-y2,x3-x2,y3-y2);
            z=crossZ(i-x3,j-y3,x1-x3,y1-y3);
           if((x >= 0 && y >=0 && z >= 0)||(x<0 && y<0 && z<0)) //Condition to check whether the point lies inside the triangle or not
           {
               float depth_value=(-an*i-bn*j-d)/cn;    //Plane Equation: ax+by+cz+d=0; so z=(-a*x-b*y-d)/c
               if(depth_value<Zbuffer[i][j])
               {
                   Zbuffer[i][j]=depth_value;       /*If depth value of the pixel is less than the value for pixel in the array */
                   glBegin(GL_POINTS);              /*Update the array with the current depth value and plot the pixel*/
                   glVertex2i(i,j);
                   glEnd();
               }
           }


        }
    }


}
/*void fillTriangle(float x1,float y1,float x2,float y2, float x3,float y3,float r,float g,float b)
{
    glColor3f(r,g,b);
   if(y2 >y1)
    {
        float tempx,tempy;
        tempx = x1;
        tempy = y1;
        x1 = x2 ;
        y1 = y2 ;
        x2 = tempx;
        y2 = tempy;

    }
    if(y3 > y1)
    {
        float tempx,tempy;
        tempx = x1;
        tempy = y1;
        x1 = x3 ;
        y1 = y3 ;
        x3 = tempx;
        y3 = tempy;
    }
    if(y3>y2)
    {
        float tempx,tempy;
        tempx = x2;
        tempy = y2;
        x2 = x3 ;
        y2 = y3 ;
        x3 = tempx;
        y3 = tempy;
    }
    float x4,y4;
    int x,y;
    float m1,m2;
    float cx1=x1;
    float cx2=x1;
    x4=x1+((y2-y1)/(y3-y1))*(x3-x1);
    if(x4>x2)
        {
            m1=(x2-x1)/(y2-y1);
            m2=(x3-x1)/(y3-y1);
        }
        else
        {
            m2=(x2-x1)/(y2-y1);
            m1=(x3-x1)/(y3-y1);
        }
    for(y=y1;y>=y2;y--)
    {
        for(x=cx1;x<=cx2;x++)
        {
            glBegin(GL_POINTS);
            glVertex2f(x,y);
            glEnd();
        }
        cx1-=m1;
        cx2-=m2;
    }

    cx1=x3;
    cx2=x3;
    //cout<<cx1<<endl;
    if(x4>x2)
    {
        m1=(x1-x3)/(y1-y3);
        m2=(x2-x3)/(y2-y3);
    }
    else
    {
        m2=(x1-x3)/(y1-y3);
        m1=(x2-x3)/(y2-y3);
    }
    //cout<<m1<<endl<<m2<<endl;
    for(y=y3;y<y2;y++)
    {
        for(x=cx1;x<=cx2;x++)
        {
            glBegin(GL_POINTS);
            glVertex2f(x,y);
            glEnd();
        }
        cx1+=m2;
        cx2+=m1;
    }


}*/

void pix(int x_pos ,int y_pos,float r ,float g ,float b )
{

            glColor3f(r,g,b);
            glBegin(GL_POINTS);
            glVertex2i(x_pos+50,y_pos-200);
            glEnd();
}

void init()
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_FLAT);
}
void changeSize(int w, int h)
{
   glViewport (0, 0, (GLsizei) width, (GLsizei) height);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluOrtho2D (0, (GLdouble) width,0 , (GLdouble) height);
}
void display();
void directionKeyPress(int,int,int);
void normalKeyPress(unsigned char,int,int);
//void directionKeyRelease(int,int,int);
void window(int width , int height ,int screenpos_x ,int screenpos_y,char s[20])
    {

        glutInitDisplayMode (GLUT_SINGLE | GLUT_RGBA);
        glutInitWindowPosition( screenpos_x, screenpos_y);
        glutInitWindowSize(width ,height );
        glutCreateWindow(s);
        init();
        glutDisplayFunc(display); // Tell GLUT to use the method "display" for rendering
        glutReshapeFunc(changeSize);
        glutSpecialFunc(directionKeyPress);
        glutKeyboardFunc(normalKeyPress);
        //glutSpecialUpFunc(directionKeyRelease);
        glutMainLoop();

}
