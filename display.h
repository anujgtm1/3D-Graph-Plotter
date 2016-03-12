#ifndef _display_h
#define _display_h
#include<GL/glut.h>
#include <GL/gl.h>
class window
{
private:
    int width;
    int height;
    int screenpos_x;
    int screenpos_y;
    char name[10];
public:
    window();
    window(int a , int b ,int c ,int d,char  s[10]);
    void plotpixel(int x_pos ,int y_pos,int r, int g ,int b );
   // void changesize(int width ,int height);

};
#endif // _display_h
