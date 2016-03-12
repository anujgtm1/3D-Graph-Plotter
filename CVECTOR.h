#include<cmath>
#include<iostream>
#ifndef CVECTOR_H_INCLUDED
#define CVECTOR_H_INCLUDED
#define PI 3.14
#define ZEROVECTOR CVector()
class  CVector
{
public:
        float x,y,z,w; // Order list of 4 elements |x|y|z|w|
        //Basic Vector Algebra
        CVector (void);      // zero Vector Constructor
        CVector (float,float,float);   // Constructor
        CVector (const CVector&);            // Copy Vector Constructor
        ~CVector();                    // Destructor

        //Vector Operations
        CVector  operator+(const CVector&);  // Addition
        CVector  operator-(const CVector&);  // Subtraction
        float operator ^(const CVector&);     //Dot Product
        void  operator=(const CVector&);     // Copy Vector
        int  operator==(const CVector&);     // Comparison Vector
        CVector  operator*(const CVector&);  // Cross Product
        CVector  operator*(float);     // Scalar Multiplication
        float magnitude();                // Magnitude
        void normalize();
        void display();
        void NDC();                     //Transfer to NDC

        //Transformations for 3d vector
        void trans(float,float,float);      //Translate by (tx,ty,tz)
        //void rotX(float);                   //Rotate around x-axis
        //void rotY(float);                   //around Y=axis
        //void rotZ(float);                   //around Z-axis
};
#endif // CVECTOR_H_INCLUDED



CVector::CVector (float xi,float yi,float zi)  // Constructor
{
    x=xi;
    y=yi;
    z=zi;
    w=1.0f; // normalize the vector
}

CVector::CVector (const CVector& a)   // Copy Vector Constructor
{
    x=a.x;
    y=a.y;
    z=a.z;
    w=a.w;
}

CVector::~CVector(){}    // Destructor

CVector  CVector::operator+(const CVector& a)  // Addition
{
    return CVector(x +a.x,y +a.y,z +a.z);
}

CVector  CVector::operator-(const CVector& a)  // Subtraction
{
    return CVector(x -a.x,y -a.y,z -a.z);
}

float    CVector::operator ^(const CVector& a) //Dot Product
{
    return x*a.x+y*a.y+z*a.z;
}

int  CVector::operator==(const CVector& a)  // Comparison Vector
{
    return (x==a.x && y==a.y && z==a.z);
}

CVector::CVector (void)
{
    x=0.0f;
    y=0.0f;
    z=0.0f;
    w=1.0f;
}

void CVector::operator=(const CVector& a)  // Copy Vector
{
    x=a.x;
    y=a.y;
    z=a.z;
    w=a.w;
}

CVector  CVector::operator*(const CVector& a)  // Cross Product
{
    return CVector(y*a.z-z*a.y,z*a.x-x*a.z,x*a.y-a.x*y);
}

CVector CVector::operator*(float a)  // Scalar Multiplication
{
    return CVector(x*a,y*a,z*a);
}

 float CVector::magnitude()   // Magnitude
 {
    return sqrt(x*x+y*y+z*z);
 }

 void CVector::normalize()
 {
    float len = magnitude();
    x = x/len;
    y = y/len;
    z = z/len;
    w=1.0f;
 }

 void CVector::display()
 {
     std::cout<<"\n"<<x<<"\t"<<y<<"\t"<<z<<"\t"<<w<<"\n";
 }

 void CVector::NDC()
{
    x=x/w;
    y=y/w;
    z=z/w;
    w=1.0;
}

 void CVector::trans(float tx,float ty,float tz)
 {
    x+=tx;
    y+=ty;
    z+=tz;
 }
/*
void CVector::rotX(float theta)
{
    theta=theta*PI/180;
    float a=sin(theta);
    float b=cos(theta);
        x=x;
        y=y*b-z*a;
        z=y*a+z*b;
}

void CVector::rotY(float theta)
{
    theta=theta*PI/180;
    float a=sin(theta);
    float b=cos(theta);
        x=x*b+z*a;
        y=y;
        z=z*b-x*a;
}

void CVector::rotZ(float theta)
{
    theta=theta*PI/180;
    float a=sin(theta);
    float b=cos(theta);
        x=x*b-y*a;
        y=x*a+y*b;
        z=z;
}
*/

