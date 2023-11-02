struct Sphere{
  Point3D c;
  double r;
  Sphere() {}
  Sphere(Point3D c, double r) : c(c), r(r) {}

  //Spherical cap with polar angle theta
  double Height(double alpha)      {return r*(1-cos(alpha));}
  double BaseRadius(double alpha)  {return r*sin(alpha);}
  double Volume(double alpha)      {double h = Height(alpha); return pi*h*h*(3*r-h)/3.0;}
  double SurfaceArea(double alpha) {double h = Height(alpha); return 2*pi*r*h;}
};

namespace Spherical{
  using namespace Vectorial;
  using namespace Planar;
  using namespace Linear;

  Sphere CircumscribedSphere(Point3D a,Point3D b,Point3D c,Point3D d){
    assert( dcmp(getSide(getPlane(a,b,c), d)) != 0);

    Plane U = Plane(a-b, (a+b)/2);
    Plane V = Plane(b-c, (b+c)/2);
    Plane W = Plane(c-d, (c+d)/2);

    Line3D l1,l2;
    bool ret1 = intersect(U,V,l1);
    bool ret2 = intersect(V,W,l2);
    assert(ret1 == true && ret2 == true);
    assert( dcmp(getDist(l1,l2)) == 0);

    Point3D C = getClosestPointOnLine1(l1,l2);
    return Sphere(C, getLength(C-a));
  }

  pair<double,double> SphereSphereIntersection(Sphere s1,Sphere s2){
    double d = getLength(s1.c-s2.c);
    if(dcmp(d - s1.r -s2.r) >= 0) return {0,0};

    double R1 = max(s1.r,s2.r); double R2 = min(s1.r,s2.r);
    double y = R1 + R2 - d;
    double x = (R1*R1 - R2*R2 + d*d) / (2*d);
    double h1 = R1 - x;
    double h2 = y - h1;

    double Volume      = pi*h1*h1*(3*R1-h1)/3.0 + pi*h2*h2*(3*R2-h2)/3.0;
    double SurfaceArea = 2*pi*R1*h1 + 2*pi*R2*h2;
    return make_pair(SurfaceArea,Volume);
  }

  Point3D getPointOnSurface(double r,double Lat,double Lon){
    Lat = torad(Lat);  //North-South
    Lon = torad(Lon);  //East-West
    return Point3D(r*cos(Lat)*cos(Lon), r*cos(Lat)*sin(Lon), r*sin(Lat));
  }

  int intersect(Sphere s,Line3D l, vector<Point3D>& ret){
    double h2 = s.r*s.r - getDistSq(l,s.c);
    if(dcmp(h2)<0) return 0;

    Point3D p = projection(l,s.c);
    if(dcmp(h2) == 0) {ret.push_back(p); return 1;}

    Vector3D h = l.v * sqrt(h2) / getLength(l.v);
    ret.push_back(p-h); ret.push_back(p+h); return 2;
  }

  double GreatCircleDistance(Sphere s,Point3D a,Point3D b){
    return s.r * getUnsignedAngle(a-s.c, b-s.c);
  }
}