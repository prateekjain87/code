#include<iostream>
using namespace std;
#define pi 3.14
class volume
{
  public:
  int vol(int x)
  {
    return x*x*x;
  }
  int vol(float r)
  {
    return (4*pi*r*r*r)/3);
  }
  int vol(int h,float r)
  {
    return (pi*r*r*h);
  }
};
int main()
{
 int ch;
 int  side,height;
 float radius;
 volume v1;
 cout<<"Enter the body whose volume is to be calculated:";
 cout<<endl<<"1.Cube"<<endl<<"2.Cylinder"<<endl<<"3.Sphere"<<endl;
 cin ch;
 if(ch==1)
 {
 cout<<"Volume Of Cube is:"<<v1.vol();
 }
}

