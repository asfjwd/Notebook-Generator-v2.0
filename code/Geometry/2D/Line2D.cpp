typedef Point Vector;
struct Line {
  double a, b, c;
  Line (double a = 0, double b = 0, double c = 0): a(a), b(b), c(c) {}
};

struct Segment{
  Point a, b;
  Segment(){}
  Segment(Point aa,Point bb) {a=aa,b=bb;}
};

struct DirLine {
  Point p;
  Vector v;
  double ang;
  DirLine () {}
  DirLine (Point p, Vector v): p(p), v(v) { ang = atan2(v.y, v.x); }
  bool operator < (const DirLine& u) const { return ang < u.ang; }
};

namespace Vectorial {
  double getDot (Vector a, Vector b) { return a.x * b.x + a.y * b.y; }
  double getCross (Vector a, Vector b) { return a.x * b.y - a.y * b.x; }
  double getLength (Vector a) { return sqrt(getDot(a, a)); }
  double getPLength (Vector a) { return getDot(a, a); }
  double getAngle (Vector u) { return atan2(u.y, u.x); }
  double getSignedAngle (Vector a, Vector b) {return getAngle(b)-getAngle(a);}
  Vector rotate (Vector a, double rad) { return Vector(a.x*cos(rad)-a.y*sin(rad), a.x*sin(rad)+a.y*cos(rad)); }
  Vector ccw(Vector a, double co, double si) {return Vector(a.x*co-a.y*si, a.y*co+a.x*si);}
  Vector cw (Vector a, double co, double si) {return Vector(a.x*co+a.y*si, a.y*co-a.x*si);}
  Vector scale(Vector a, double s = 1.0) {return a / getLength(a) * s;}
  Vector getNormal (Vector a) { double l = getLength(a); return Vector(-a.y/l, a.x/l); }
};

namespace Linear {
  using namespace Vectorial;

  Line getLine (double x1, double y1, double x2, double y2) { return Line(y2-y1, x1-x2, y1*x2-x1*y2); }
  Line getLine (double a, double b, Point u) { return Line(a, -b, u.y * b - u.x * a); }

  bool getIntersection (Line p, Line q, Point& o) {
    if (fabs(p.a * q.b - q.a * p.b) < eps)
      return false;
    o.x = (q.c * p.b - p.c * q.b) / (p.a * q.b - q.a * p.b);
    o.y = (q.c * p.a - p.c * q.a) / (p.b * q.a - q.b * p.a);
    return true;
  }

  bool getIntersection (Point p, Vector v, Point q, Vector w, Point& o) {
    if (dcmp(getCross(v, w)) == 0) return false;
    Vector u = p - q;
    double k = getCross(w, u) / getCross(v, w);
    o = p + v * k;
    return true;
  }

  double getDistanceToLine (Point p, Point a, Point b) { return fabs(getCross(b-a, p-a) / getLength(b-a)); }
  double getDistanceToSegment (Point p, Point a, Point b) {
    if (a == b) return getLength(p-a);
    Vector v1 = b - a, v2 = p - a, v3 = p - b;
    if (dcmp(getDot(v1, v2)) < 0) return getLength(v2);
    else if (dcmp(getDot(v1, v3)) > 0) return getLength(v3);
    else return fabs(getCross(v1, v2) / getLength(v1));
  }
  
  double getDistanceSegToSeg (Point a,Point b,Point c,Point d){
    double Ans=INT_MAX;
    Ans=min(Ans,getDistanceToSegment(a,c,d));
    Ans=min(Ans,getDistanceToSegment(b,c,d));
    Ans=min(Ans,getDistanceToSegment(c,a,b));
    Ans=min(Ans,getDistanceToSegment(d,a,b));
    return Ans;
  }

  Point getPointToLine (Point p, Point a, Point b) { Vector v = b-a; return a+v*(getDot(v, p-a) / getDot(v,v)); }
  bool onSegment (Point p, Point a, Point b) { return dcmp(getCross(a-p, b-p)) == 0 && dcmp(getDot(a-p, b-p)) <= 0; }

  bool haveIntersection (Point a1, Point a2, Point b1, Point b2) {
    if(onSegment(a1,b1,b2)) return true;
    if(onSegment(a2,b1,b2)) return true;
    if(onSegment(b1,a1,a2)) return true;
    if(onSegment(b2,a1,a2)) return true;  //Case of touch

    double c1=getCross(a2-a1, b1-a1), c2=getCross(a2-a1, b2-a1), c3=getCross(b2-b1, a1-b1), c4=getCross(b2-b1,a2-b1);
    return dcmp(c1)*dcmp(c2) < 0 && dcmp(c3)*dcmp(c4) < 0;
  }
  bool onLeft(DirLine l, Point p) { return dcmp(l.v * (p-l.p)) >= 0; }
}