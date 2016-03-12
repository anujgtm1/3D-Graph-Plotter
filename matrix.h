#include<iostream>
#include<cmath>
#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED
class matrix
{
        float a[4][4];
public:
        matrix(void);               //Zero matrix constructor
        matrix(float a[4][4]);      //Matrix from array
        matrix(const matrix&);            //Copy Constructor
        ~matrix();                  //Destructor

        //Matrix Operations
        matrix operator+(const matrix&);  //Addition
        matrix operator-(const matrix&);  //Subtraction
        matrix operator*(const matrix&);  //Matrix multiplication
        void operator=(const matrix&);      //Copy Matrix
        int operator==(const matrix&);      //Logically equating matrices
        void display();                     //Display matrix for debug purposes
        void input();                       //Input values to matrix in traditional manner
        void change(float b[4][4]);                      //Change the values in matrix
        void transpose();

        //matrix operator*(CVector&); //Vector Transformation using matrix

        /*
        view plane position: left,right,top,bottom,front,back
        */
        void Ortho(float,float,float,float,float,float);               //Generate orthographic projection matrix
        void Persp(float,float,float,float,float,float);               //Generate Perspective projection matrix
        /*Screen Resolution: Width,Height(Xmax,Ymax)*/
        void ViewPort(int,int);            //Transform NDC points to device screen points
        CVector operator*(CVector&);
        void rotation(float,CVector&);
        void translation(float,float,float);
        void Scaling(float,float,float);
        void Camera(CVector&,CVector&);


};

#endif // MATRIX_H_INCLUDED

matrix::matrix(void)           //Matrix initialized without parameters is set to zero
{
    int i,j;
    for(i=0;i<=3;i++)
    {
        for(j=0;j<=3;j++)
        {
            a[i][j]=0;
        }
    }
}

matrix::matrix(float b[4][4])     //Matrix from array
{
    int i,j;
    for(i=0;i<=3;i++)
    {
        for(j=0;j<=3;j++)
        {
            a[i][j]=b[i][j];
        }
    }

}

matrix::matrix(const matrix& mat)        //Copy Constructor
{
    int i,j;
    for(i=0;i<=3;i++)
    {
        for(j=0;j<=3;j++)
        {
            a[i][j]=mat.a[i][j];
        }
    }
}

matrix::~matrix(){}                     //Destructor

matrix matrix::operator+(const matrix& mat)           //Matrix Addition
{
    int i,j;
    for(i=0;i<=3;i++)
    {
        for(j=0;j<=3;j++)
        {
            a[i][j]+=mat.a[i][j];
        }
    }
    return matrix(a);
}


matrix matrix::operator-(const matrix& mat)       //Matrix Subtraction
{
    int i,j;
    for(i=0;i<=3;i++)
    {
        for(j=0;j<=3;j++)
        {
            a[i][j]-=mat.a[i][j];
        }
    }
    return matrix(a);
}

matrix matrix::operator*(const matrix& mat)               //Matrix-matrix multiplication
{
    float sum;
    float c[4][4];
    int i,j,k;
    for (i = 0; i <= 3; i++) {
      for (j = 0; j <= 3; j++) {
         sum = 0;
         for (k = 0; k <= 3; k++) {
            sum = sum + a[i][k] * mat.a[k][j];
         }
         c[i][j] = sum;
      }
   }
   return matrix(c);
}

void matrix::operator=(const matrix& m)
{
    int i,j;
    for(i=0;i<=3;i++)
    {
        for(j=0;j<=3;j++)
        {
            a[i][j]=m.a[i][j];
        }
    }
}

int matrix::operator==(const matrix& m)
{
    int i,j;
    for(i=0;i<=3;i++)
    {
        for(j=0;j<=3;j++)
        {
            if(a[i][j]!=m.a[i][j])
            {
                return 0;
            }
        }
    }
    return 1;
}

void matrix::display()
{
    int i,j;
    std::cout<<"\n";
    for (i = 0; i <= 3; i++) {
      for (j = 0; j <= 3; j++) {
         std::cout<<a[i][j];
         std::cout<<"\t";
      }
      std::cout<<"\n";
   }
}

void matrix::input()
{
    int i,j;
    std::cout<<"Enter the matrix";

    for(i=0;i<=3;i++)
    {
        for(j=0;j<=3;j++)
        {
            std::cout<<i<<","<<j;
            std::cin>>a[i][j];
            std::cout<<"\n";
        }
    }
}

void matrix::change(float b[4][4])
{
    int i,j;
    for(i=0;i<=3;i++)
    {
        for(j=0;j<=3;j++)
        {
            a[i][j]=b[i][j];
        }
    }
}

void matrix::transpose()
{
    int i,j;
    float b[4][4];
    for(i=0;i<=3;i++)
    {
        for(j=0;j<=3;j++)
        {
            b[i][j]=a[j][i];
        }
    }
    for(i=0;i<=3;i++)
    {
        for(j=0;j<=3;j++)
        {
            a[i][j]=b[i][j];
        }
    }
}

/*
    Viewplane position in the z-axis
    left<=x<=right
    top<=y<=bottom
    front<=z<=back
    front and back are negative because the camera quintessentially
    focuses towards the negative z-axis. so back>front and
    abs(back)<abs(front)
*/
void matrix::Ortho(float right,float left,float top,float bottom,float Zmin,float Zmax )
{
    //Initialization
    int i,j;
    for(i=0;i<=3;i++)
    {
        for(j=0;j<=3;j++)
        {
            a[i][j]=0;
        }
    }
    //Writing values
    a[0][0]=2/(right-left);
    a[0][3]=(right+left)/(right-left)*(-1);
    a[1][1]=2/(top-bottom);
    a[1][3]=(top+bottom)/(top-bottom)*(-1);
    a[2][2]=2/(Zmin-Zmax);
    a[2][3]=(Zmin+Zmax)/(Zmin-Zmax)*(-1);
    a[3][3]=1;
}

void matrix::Persp(float right,float left,float top,float bottom,float Zmin,float Zmax)
{
    //Initialization
    int i,j;
    for(i=0;i<=3;i++)
    {
        for(j=0;j<=3;j++)
        {
            a[i][j]=0;
        }
    }

    a[0][0]=2*Zmin/(right-left);
    a[1][1]=2*Zmin/(top-bottom);
    a[2][2]=(Zmin+Zmax)/(Zmin-Zmax);
    a[2][3]=(-2)*Zmin*Zmax/(Zmin-Zmax);
    a[3][2]=-1;
}

void matrix::ViewPort(int width,int height)     //Generation of ViewPort Matrix
{
    //Initialization
    int i,j;
    for(i=0;i<=3;i++)
    {
        for(j=0;j<=3;j++)
        {
            a[i][j]=0;
        }
    }

    a[0][0]=width/2;
    a[0][3]=(width-1)/2;
    a[1][1]=height/2;
    a[1][3]=(height-1)/2;
    a[2][2]=1;
    a[3][3]=1;
}

CVector matrix::operator*(CVector& v)     //Transformation using a matrix
{
    int i,j;
    float sum;
    float b[4],c[4];
    b[0]=v.x;
    b[1]=v.y;
    b[2]=v.z;
    b[3]=v.w;

    for(i=0;i<=3;i++)
    {
        sum=0;
        for(j=0;j<=3;j++)
        {
            sum+=a[i][j]*b[j];
        }
        c[i]=sum;
    }
    CVector v1;
    v1.x=c[0];
    v1.y=c[1];
    v1.z=c[2];
    v1.w=c[3];
    return v1;
}

void matrix::rotation(float theta,CVector& v)
{
    float thet=theta*3.14/180;
    float c=cos(thet);
    float s=sin(thet);
    float t=1-c;
    v.normalize();

    a[0][0]=t*v.x*v.x+c;        a[0][1]=t*v.x*v.y-s*v.z;    a[0][2]=t*v.x*v.z+s*v.y;    a[0][3]=0;
    a[1][0]=t*v.x*v.y+s*v.z;    a[1][1]=t*v.y*v.y+c;        a[1][2]=t*v.y*v.z-s*v.x;    a[1][3]=0;
    a[2][0]=t*v.x*v.z-s*v.y;    a[2][1]=t*v.y*v.z+s*v.x;    a[2][2]=t*v.z*v.z+c;        a[2][3]=0;
    a[3][0]=0;                  a[3][1]=0;                  a[3][2]=0;                  a[3][3]=1;
}

void matrix::translation(float x,float y,float z)
{
    a[0][0]=1;          a[0][1]=0;          a[0][2]=0;          a[0][3]=x;
    a[1][0]=0;          a[1][1]=1;          a[1][2]=0;          a[1][3]=y;
    a[2][0]=0;          a[2][1]=0;          a[2][2]=1;          a[2][3]=z;
    a[3][0]=0;          a[3][1]=0;          a[3][2]=0;          a[3][3]=1;
}

void matrix::Scaling(float Sx,float Sy,float Sz)
{
    a[0][0]=Sx;          a[0][1]=0;          a[0][2]=0;          a[0][3]=0;
    a[1][0]=0;           a[1][1]=Sy;         a[1][2]=0;          a[1][3]=0;
    a[2][0]=0;           a[2][1]=0;          a[2][2]=Sz;         a[2][3]=0;
    a[3][0]=0;           a[3][1]=0;          a[3][2]=0;          a[3][3]=1;
}

void matrix::Camera(CVector& Origin,CVector& Up)
{
    CVector u,v,w;
    CVector O(0,0,0);
    Up.normalize();
    v=Up;
    w=O-Origin;
    w.normalize();
    u=v*w;
    u.normalize();
    v=w*u;
    v.normalize();
    a[0][0]=u.x;        a[0][1]=u.y;        a[0][2]=u.z;        a[0][3]=0;
    a[1][0]=v.x;        a[1][1]=v.y;        a[1][2]=v.z;        a[1][3]=0;
    a[2][0]=w.x;        a[2][1]=w.y;        a[2][2]=w.z;        a[2][3]=0;
    a[3][0]=0;          a[3][1]=0;          a[3][2]=0;          a[3][3]=1;

}

