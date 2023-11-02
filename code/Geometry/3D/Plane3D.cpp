struct Plane{
  Vector3D n; //normal n
  double d; //getDot(n,p) = d for any point p on the plane
  Plane() {}
  Plane(Vector3D n, double d) : n(n), d(d) {}
  Plane(Vector3D n, Point3D p) : n(n), d(Vectorial :: getDot(n,p)) {}
  Plane(const Plane &p) : n(p.n), d(p.d) {}
};

namespace Planar{
  using namespace Vectorial;
  Plane getPlane(Point3D a,Point3D b,Point3D c) {return Plane(getCross(b-a,c-a),a);}
  Plane translate(Plane p,Vector3D t)       {return Plane(p.n, p.d+getDot(p.n,t));}
  Plane shiftUp(Plane p,double dist)      {return Plane(p.n, p.d+dist*getLength(p.n));}
  Plane shiftDown(Plane p,double dist)    {return Plane(p.n, p.d-dist*getLength(p.n));}

  double getSide(Plane p,Point3D a)     {return getDot(p.n,a)-p.d;}
  double getDistance(Plane p,Point3D a) {return fabs(getSide(p,a))/getLength(p.n);}
  Point3D projection(Plane p,Point3D a)   {return a-p.n*getSide(p,a)/getPLength(p.n);}
  Point3D reflection(Plane p,Point3D a)   {return a-p.n*getSide(p,a)/getPLength(p.n)*2;}

  bool intersect(Plane p, Line3D l, Point3D& a){
    if(dcmp(getDot(p.n,l.v)) == 0) return false;
    a = l.o - l.v * getSide(p,l.o) / getDot(p.n,l.v);
    return true;
  }

  bool intersect(Plane p,Plane q,Line3D& l){
    l.v = getCross(p.n,q.n);
    if(dcmp(getPLength(l.v)) == 0) return false;
    l.o = getCross(q.n*p.d - p.n*q.d , l.v) / getPLength(l.v);
    return true;
  }

  double getAngle(Plane p,Plane q)      {return getUnsignedAngle(p.n,q.n);}
  bool isParallel(Plane p,Plane q)      {return dcmp(getPLength(getCross(p.n,q.n))) == 0;}
  bool isPerpendicular(Plane p,Plane q) {return dcmp(getDot(p.n,q.n)) == 0;}

  bool getAngle(Plane p,Line3D l)         {return pi/2.0 - getUnsignedAngle(p.n,l.v);}
  bool isParallel(Plane p,Line3D l)       {return dcmp(getDot(p.n,l.v)) == 0;}
  bool isPerpendicular(Plane p,Line3D l)  {return dcmp(getPLength(getCross(p.n,l.v))) == 0;}

  Line3D perpThrough(Plane p,Point3D a)     {return Line3D(p.n,a);}
  Plane perpThrough(Line3D l,Point3D a)     {return Plane(l.v,a);}

  //Modify p.n if necessary with respect to the reference point
  Vector3D rotateCCW90(Plane p,Vector3D d)  {return getCross(p.n,d);}
  Vector3D rotateCW90(Plane p,Vector3D d)   {return getCross(d,p.n);}

  pair<Point3D, Point3D> TwoPointsOnPlane(Plane p){
    Vector3D N = p.n; double D = p.d;

    assert(dcmp(N.x) != 0 || dcmp(N.y) != 0 || dcmp(N.z) != 0);
    if(dcmp(N.x) == 0 && dcmp(N.y) == 0) return {Point3D(1,0,D/N.z), Point3D(0,1,D/N.z)};
    if(dcmp(N.y) == 0 && dcmp(N.z) == 0) return {Point3D(D/N.x,1,0), Point3D(D/N.x,0,1)};
    if(dcmp(N.z) == 0 && dcmp(N.x) == 0) return {Point3D(1,D/N.y,0), Point3D(0,D/N.y,1)};
    if(dcmp(N.x) == 0) return {Point3D(1,D/N.y,0), Point3D(0,0,D/N.z)};
    if(dcmp(N.y) == 0) return {Point3D(0,1,D/N.z), Point3D(D/N.x,0,0)};
    if(dcmp(N.z) == 0) return {Point3D(D/N.x,0,1), Point3D(0,D/N.y,0)};
    if(dcmp(D)!=0) return {Point3D(D/N.x,0,0), Point3D(0,D/N.y,0)};
    return {Point3D(N.y,-N.x,0), Point3D(-N.y,N.x,0)};
  }

  Point From3Dto2D(Plane p, Point3D a){
    assert( dcmp(getSide(p,a)) == 0 );
    auto Pair = TwoPointsOnPlane(p);
    Point3D A = Pair.first;
    Point3D B = Pair.second;

    Vector3D Z = p.n;                 Z = Z / getLength(Z);
    Vector3D X = B - A;               X = X / getLength(X);
    Vector3D Y = getCross(Z,X);

    Vector3D v = a - A;
    assert( dcmp(getDot(v,Z)) == 0);
    return Point(getDot(v,X),getDot(v,Y));
  }

  Point3D From2Dto3D(Plane p, Point a){
    auto Pair = TwoPointsOnPlane(p);
    Point3D A = Pair.first;
    Point3D B = Pair.second;

    Vector3D Z = p.n;                 Z = Z / getLength(Z);
    Vector3D X = B - A;               X = X / getLength(X);
    Vector3D Y = getCross(Z,X);

    return A + X * a.x + Y * a.y;
  }
}