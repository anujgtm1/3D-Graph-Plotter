#include <iostream>
#include "Disp.h"
#include "CVECTOR.h"
#include "matrix.h"
#include<cmath>
#include "atmsp.h"
#include <string>
#include <stdio.h>

char UserEqun[255]="(4*exp(-x*x/10-z*z/10)*cos(x*x+z*z))";

float zoom=0;
float panx=0,pany=0;


matrix trans,roty,rotx,rotz,modelview,project,viewport,camera,scale;
CVector Yaxis(0,1,0),Zaxis(0,0,1),Xaxis(1,0,0);

float xLimit=10,zLimit=10,resolution=0.1,resolution1=resolution;
float emissive=0.1,diffuse=1;
int xn=0,zn=0;

float a[600][600][6];
int xAngle=0,yAngle=0,zAngle=0;
bool bool_wireframe=true;
bool bool_solidfill=false;

void Axes();
void wireframe();
void solidfill();


void directionKeyPress(int key,int x,int y)
{
    switch(key)
    {
    case GLUT_KEY_RIGHT:
        yAngle+=5;
        //cout<<"xAngle="<<xAngle<<"yAngle="<<yAngle<<"zAngle="<<zAngle<<endl;
        if(yAngle>=360)
        {
            yAngle=0;
        }
    break;

    case GLUT_KEY_LEFT:
        yAngle-=5;
        if(yAngle<=0)
        {
            yAngle=360;
        }
    break;
    case GLUT_KEY_UP:
        xAngle+=5;
        if(xAngle>=360)
        {
            xAngle=0;
        }
    break;
    case GLUT_KEY_DOWN:
        xAngle-=5;
        if(xAngle<=0)
        {
            xAngle=360;
        }
        break;
    case GLUT_KEY_F1:
        bool_wireframe=true;
        bool_solidfill=false;
        break;
    case GLUT_KEY_F2:
        bool_wireframe=false;
        bool_solidfill=true;
        break;

    default:
        break;

}
glutPostRedisplay();
}
void normalKeyPress(unsigned char key,int x,int y)
{
    switch(key)
    {
    case 27:
       exit(0);
    break;
    case 'e':
       std::cout<<"Enter your equation:"<<std::endl;
       gets(UserEqun);
    break;
    case '-':
        zoom=zoom+0.5;
        break;
    case '=':
        zoom=zoom-0.5;
        break;
    case 'a':
        panx=panx+0.5;
        break;
    case 'd':
        panx=panx-0.5;
        break;
    case 's':
        pany=pany+0.5;
        break;
    case 'w':
        pany=pany-0.5;
        break;
    case 'r':
        xAngle=0;
        yAngle=0;
        zAngle=0;
        zoom=0;
        panx=0;
        pany=0;
        break;



    default:
         break;

    }
    glutPostRedisplay();
}

/*float func(float x,float z)
{
    float y=cos(x*x+z*z)*exp(-x*x/10-z*z/10);
    return y;
}*/
float ParserResult(char* Equation,float Xvalue,float Zvalue)
{
      ATMSP<double> parser;
    ATMSB<double> byteCode;



    // Parse your expression with a variables list AFTER constant declarations
    // Both the expression and the variables list are case sensitive and may contain blanks
    size_t err = parser.parse(byteCode, Equation, "x,z");

    if(err)
    {
       // std::cout << "Parsing failed with: " << parser.errMessage(err) << std::endl;
        return 0;

    }
    // Set variable values BEFORE final bytecode execution. Same principle for more variables

    byteCode.var[0] = Xvalue;
    byteCode.var[1] = Zvalue;   // x is 1st in the above variables list, so it has index 0
    // z is 2nd in the above variables list, so it has index 1

    // And execute the bytecode with the variable/constant values set above
    float y = byteCode.run();


    // In need to check float errors like division by zero or negative roots e.g?
    if ( byteCode.fltErr )
    {
      // std::cerr << "Faced a NaN/inf error" <<  std::endl;
    }
        return y;

}

void calcMatrix()
{
    trans.translation(-2,-2,-3);
    roty.rotation(yAngle,Yaxis);
    rotz.rotation(zAngle,Zaxis);
    rotx.rotation(xAngle,Xaxis);
    matrix m=roty*rotx*rotz;
    modelview=trans*m;
    project.Ortho(5+zoom+panx,-5-zoom+panx,5+zoom+pany,-5-zoom+pany,1,10);
    viewport.ViewPort(480,360);
    Axes();
}

void wireframe()
{
    if(bool_wireframe)
    {
    float x,y,z;
    float r=0,g=0,b=1;
   // float ymax=0,ymin=0;
    int i,j;
    CVector A;
    if(resolution!=0.15)
    {
        resolution=0.15;
    }
    //int xn=0,zn=0;
    xn=0;
    for(x=-xLimit/2;x<=xLimit/2;x=x+resolution)
    {
        zn=0;
        for(z=-zLimit/2;z<=zLimit/2;z=z+resolution)
        {
            y=ParserResult(UserEqun,x,z);
            a[xn][zn][0]=x;
            a[xn][zn][1]=y;
            a[xn][zn][2]=z;
           // if(y>ymax){ymax=y;};
            //if(y<ymin){ymin=y;};
            zn++;
        }
    xn++;
    }
    /*for(i=0;i<xn;i++)
    {
        for(j=0;j<zn;j++)
        {
            y=a[i][j][1];
            r=(y-ymin)/(ymax-ymin);
            g=0;
            b=1-r;
            a[i][j][3]=r;
            a[i][j][4]=g;
            a[i][j][5]=b;
        }
    }*/
    for(i=0;i<xn;i++)
    {
        for(j=0;j<zn;j++)
        {
            A.x=a[i][j][0];
            A.y=a[i][j][1];
            A.z=a[i][j][2];
            A=modelview*A;
            A=camera*A;
            A=project*A;
            A.NDC();
            A=viewport*A;
            a[i][j][0]=A.x;
            a[i][j][1]=A.y;
            a[i][j][2]=A.z;
            //pix(A.x,A.y,A.z,1,1);
            //Line(a[0][0],a[0][1],a[i][0],a[i][1],1,1,1);


        }


    }
    for(i=1;i<xn;i++)
        {
            for(j=0;j<zn;j++)
            {
                //if(i>0)
                {
                    Line(a[i][j][0],a[i][j][1],a[i-1][j][0],a[i-1][j][1],r,g,b);
                  //  if(j>0)
                    {
                        Line(a[j][i][0],a[j][i][1],a[j][i-1][0],a[j][i-1][1],r,g,b);
                       //Line(a[i][j][0],a[i][j][1],a[i-1][j-1][0],a[i-1][j-1][1],0,0,1);
                    }
                } //else {
                    //if(j>0)
                    {
                       // Line(a[j][i][0],a[j][i][1],a[j][i-1][0],a[j][i-1][1],r,g,b);

                    }
                }
            }
    }
}

void solidfill()
{
    if(bool_solidfill)
    {
    float x,y,z;
    float r,g,b;
    float ymax=0,ymin=0;
    int i,j;
    CVector A;
    resolution=resolution1;
    //int xn=0,zn=0;
    xn=0;
    for(x=-xLimit/2;x<=xLimit/2;x=x+resolution)
    {
        zn=0;
        for(z=-zLimit/2;z<=zLimit/2;z=z+resolution)
        {
            y=ParserResult(UserEqun,x,z);
            a[xn][zn][0]=x;
            a[xn][zn][1]=y;
            a[xn][zn][2]=z;
            if(y>ymax){ymax=y;};
            if(y<ymin){ymin=y;};
            zn++;
        }
    xn++;
    }
    for(i=0;i<xn;i++)
    {
        for(j=0;j<zn;j++)
        {
            y=a[i][j][1];
            r=(y-ymin)/(ymax-ymin);
            g=0;
            b=1-r;
            a[i][j][3]=r;
            a[i][j][4]=g;
            a[i][j][5]=b;
        }
    }
    for(i=0;i<xn;i++)
    {
        for(j=0;j<zn;j++)
        {
            A.x=a[i][j][0];
            A.y=a[i][j][1];
            A.z=a[i][j][2];
            A=modelview*A;
            A=camera*A;
            A=project*A;
            A.NDC();
            A=viewport*A;
            a[i][j][0]=A.x+250;
            a[i][j][1]=A.y+200;
            a[i][j][2]=A.z;



        }


    }

    for(int i=0;i<xn-1;i++)
    {
        for(int j=0;j<zn-1;j++)
        {

            //(i,j),(i,j+1),(i+1,j+1) & (i,j),(i+1,j),(i+1,j+1);
            float r,g,b;
            float an,bn,cn;
            float d;
            float x1=a[i][j][0] ,     y1=a[i][j][1],        z1=a[i][j][2];
            float x2=a[i][j+1][0],    y2=a[i][j+1][1],      z2=a[i][j+1][2];
            float x3=a[i+1][j+1][0],    y3=a[i+1][j+1][1],      z3=a[i+1][j+1][2];
            CVector V1(x2-x1,y2-y1,z2-z1),V2(x3-x1,y3-y1,z3-z1);
            float x=(x1+x2+x3)/3,   y=(y1+y2+y3)/3,     z=(z1+z2+z3)/3;
            CVector lightPos(1,1,1);
            CVector normal=V1*V2;
            r=(a[i][j][3]+a[i][j+1][3]+a[i+1][j+1][3])/3;
            g=(a[i][j][4]+a[i][j+1][4]+a[i+1][j+1][4])/3;
            b=(a[i][j][5]+a[i][j+1][5]+a[i+1][j+1][5])/3;
            an=normal.x;   // a of the plane
            bn=normal.y;   //b of the plane
            cn=normal.z;   //c of the plane
            CVector E1(x2,y2,z2);
            //cout<<normal.x<<" "<<normal.y<<" "<<normal.z<<endl;
            //cout<<E2.x<<" "<<E2.y<<" "<<E2.z<<endl;
            d=-(normal^E1);  //d of the plane
            //cout<<d<<endl;
            CVector facePos(x,y,z);
            CVector lightDir=lightPos-facePos;
            lightDir.normalize();
            float cosine=lightDir^normal;
            //if(cosine<=0){cosine=0;};
            r+=cosine*diffuse;
            g+=cosine*diffuse;
            b+=cosine*diffuse;

            fillTriangle(an,bn,cn,d,x1,y1,x2,y2,x3,y3,r,g,b);

            x2=a[i+1][j][0],     y2=a[i+1][j][1],     z2=a[i+1][j][2];
            x=(x1+x2+x3)/3,   y=(y1+y2+y3)/3,     z=(z1+z2+z3)/3;
            V1.x=x2-x1,     V1.y=y2-y1,         V1.z=z2-z1;
            V2.x=x3-x1,     V2.y=y3-y1,         V2.z=z3-z1;
            r=(a[i][j][3]+a[i][j+1][3]+a[i+1][j+1][3])/3;
            g=(a[i][j][4]+a[i][j+1][4]+a[i+1][j+1][4])/3;
            b=(a[i][j][5]+a[i][j+1][5]+a[i+1][j+1][5])/3;
            normal=V2*V1;
            an=normal.x;
            bn=normal.y;
            cn=normal.z;
            CVector E2(x2,y2,z2);
            d=-(normal^E2);
            facePos.x=x,        facePos.y=y,        facePos.z=z;
            lightDir=lightPos-facePos;
            lightDir.normalize();
            cosine=lightDir^normal;
            //if(cosine<=0){cosine=0;};
            r+=cosine*diffuse;
            g+=cosine*diffuse;
            b+=cosine*diffuse;
            fillTriangle(an,bn,cn,d,x1,y1,x2,y2,x3,y3,r,g,b);

        }
        }
//WireFrame();
}
}
void Axes()
{
    //Transferring points from 3d to 800x600 screen;
    //Position Vectors of Origin and X-axis,Y-axis,Z-axis upto 5 divisions;
//Modeling to world co-ordinate
    CVector O(0,0,0),X=Xaxis*15,Y=Yaxis*15,Z=Zaxis*15;
            //X-Y plane centred at Z-axis.
                                            //further translated 5 units in -Z direction for visibility
    //*m;
    O=modelview*O;
    X=modelview*X;
    Y=modelview*Y;
    Z=modelview*Z;
//Local to World Co-ordinate transformation Over
    camera.Camera(O,Yaxis);
    //camera.display();
    O=camera*O;
    X=camera*X;
    Y=camera*Y;
    Z=camera*Z;
//Projection

    O=project*O;
    X=project*X;
    Y=project*Y;
    Z=project*Z;

//Projection Over

//Scaling to NDC
    O.NDC();
    X.NDC();
    Y.NDC();
    Z.NDC();
//Scaling over

//Clippings happen here if (x*x>1 or y*y>1 or z*z>1) then point occurs outside the scene
//Here illumination happens

//Changing from NDC to Screen;
    O=viewport*O;
    X=viewport*X;
    Y=viewport*Y;
    Z=viewport*Z;

//Viewport transformation(to screen co-ordinate) over

//Actually drawing the axes
//Projection maps st line to st line
    //Line(0,0,0,800,1,1,1);
    //Line(0,0,800,0,1,1,1);
    Line(O.x,O.y,X.x,X.y,1,0,0);
    Line(O.x,O.y,Y.x,Y.y,0,1,0);
    Line(O.x,O.y,Z.x,Z.y,0,0,1);
    solidfill();
    wireframe();

}


void display(void)
 {
     glClear (GL_COLOR_BUFFER_BIT);
     calcMatrix();
     clear_Zbuffer();
     glFlush();

}

int main(int argc ,char**argv){
     std::cout<<"Press E to enter Equation:"<<std::endl;
     cout<<"Use arrow keys for rotation..F1 for wireframe model..F2 for solidfill."<<endl;
     cout<<"+ to zoom in..- to zoom out.. w,a,s,d to pan the view"<<endl;

     glutInit(&argc, argv);
     window(width,height,100,00,"GRAPH 3D");


}

