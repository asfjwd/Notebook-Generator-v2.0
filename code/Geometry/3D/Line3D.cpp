typedef Point3D Vector3D;
typedef vector<Point> Polygon;
typedef vector<Point3D> Polyhedron;

namespace Vectorial{
  double getDot (Vector3D a, Vector3D b)  {return a.x*b.x+a.y*b.y+a.z*b.z;}
  Vector3D getCross(Vector3D a, Vector3D b) {return Point3D(a.y*b.z-a.z*b.y, a.z*b.x-a.x*b.z, a.x*b.y-a.y*b.x);}
  double getLength (Vector3D a)         {return sqrt(getDot(a, a)); }
  double getPLength (Vector3D a)        {return getDot(a, a); }
  Vector3D unitVector(Vector3D v)         {return v/getLength(v);}

  double getUnsignedAngle(Vector3D u,Vector3D v){
    double cosTheta = getDot(u,v)/getLength(u)/getLength(v);
    cosTheta = max(-1.0,min(1.0,cosTheta));
    return acos(cosTheta);
  }

  Vector3D rotate(Vector3D v,Vector3D a,double rad){
    a = unitVector(a);
    return v * cos(rad) + a * (1 - cos(rad)) * getDot(a,v) + getCross(a,v) * sin(rad);
  }
}

struct Line3D{
  Vector3D v; Point3D o;
  Line3D() {};
  Line3D(Vector3D v,Point3D o):v(v),o(o){}
  Point3D getPoint(double t) {return o + v*t;}
};

namespace Linear{
  using namespace Vectorial;
  double getDistSq(Line3D l, Point3D p)          {return getPLength(getCross(l.v,p-l.o))/getPLength(l.v);}
  double getDistLinePoint(Line3D l, Point3D p)   {return sqrt(getDistSq(l,p));}
  bool cmp(Line3D l,Point3D p, Point3D q)          {return getDot(l.v,p) < getDot(l.v,q);}
  Point3D projection(Line3D l,Point3D p)           {return l.o + l.v * getDot(l.v,p-l.o)/getPLength(l.v);}
  Point3D reflection(Line3D l,Point3D p)           {return projection(l,p)+projection(l,p)-p;}

  double getAngle(Line3D l,Line3D m)             {return getUnsignedAngle(l.v,m.v);}
  bool isParallel(Line3D p,Line3D q)             {return dcmp(getPLength(getCross(p.v,q.v))) == 0;}
  bool isPerpendicular(Line3D p,Line3D q)        {return dcmp(getDot(p.v,q.v)) == 0;}

  double getDist(Line3D l, Line3D m){
    Vector3D n = getCross(l.v, m.v);
    if(getPLength(n) == 0) return getDistLinePoint(l,m.o);
    else return fabs(getDot(m.o-l.o , n)) / getLength(n);
  }

  Point3D getClosestPointOnLine1(Line3D l,Line3D m){
    Vector3D n = getCross(l.v, m.v);
    Vector3D n2 = getCross(m.v, n);
    return l.o + l.v * getDot(m.o-l.o, n2) / getDot(l.v, n2);
  }
}