#include<bits/stdc++.h>
using namespace std;

const double pi = 4 * atan(1);
const double eps = 1e-10;
inline int dcmp (double x) { if (fabs(x) < eps) return 0; else return x < 0 ? -1 : 1; }
inline double torad(double deg) { return deg / 180 * pi; }

struct Point{
  double x, y;
  Point (double x = 0, double y = 0): x(x), y(y) {}

  Point operator + (const Point& u) { return Point(x + u.x, y + u.y); }
  Point operator - (const Point& u) { return Point(x - u.x, y - u.y); }
  Point operator * (const double u) { return Point(x * u, y * u); }
  Point operator / (const double u) { return Point(x / u, y / u); }
  double operator * (const Point& u) { return x*u.y - y*u.x; }
};

struct Point3D{
  double x, y, z;
  Point3D() {}
  void read () {cin>>x>>y>>z;}
  void write () {cout<<x<<" --- "<<y<<" --- "<<z<<"\n";}

  Point3D(double x, double y, double z) : x(x), y(y), z(z) {}
  Point3D(const Point3D &p) : x(p.x), y(p.y), z(p.z) {}
  Point3D operator +(Point3D b)  {return Point3D(x+b.x,y+b.y, z+b.z);}
  Point3D operator -(Point3D b)  {return Point3D(x-b.x,y-b.y, z-b.z);}
  Point3D operator *(double b) {return Point3D(x*b,y*b, z*b);}
  Point3D operator /(double b) {return Point3D(x/b,y/b, z/b);}
  bool operator  <(Point3D b)  {return make_pair(make_pair(x,y),z) < make_pair(make_pair(b.x,b.y),b.z);}
  bool operator ==(Point3D b)  {return dcmp(x-b.x)==0 && dcmp(y-b.y) == 0 && dcmp(z-b.z) == 0;}
};
