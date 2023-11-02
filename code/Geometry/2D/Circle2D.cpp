struct Circle {
  Point o;
  double r;
  Circle () {}
  Circle (Point o, double r = 0): o(o), r(r) {}
  void read () { o.read(), scanf("%lf", &r); }
  Point point(double rad) { return Point(o.x + cos(rad)*r, o.y + sin(rad)*r); }
  double getArea (double rad) { return rad * r * r / 2; }
  //area of the circular sector cut by a chord with central angle alpha
  double sector(double alpha) {return r * r * 0.5 * (alpha - sin(alpha));}
};

namespace Circular {
  using namespace Linear;
  using namespace Vectorial;
  using namespace Triangular;

  int getLineCircleIntersection (Point p, Point q, Circle O, double& t1, double& t2, vector<Point>& sol) {
    Vector v = q - p;
    //sol.clear();
    double a = v.x, b = p.x - O.o.x, c = v.y, d = p.y - O.o.y;
    double e = a*a+c*c, f = 2*(a*b+c*d), g = b*b+d*d-O.r*O.r;
    double delta = f*f - 4*e*g;
    if (dcmp(delta) < 0) return 0;
    if (dcmp(delta) == 0) {
      t1 = t2 = -f / (2 * e);
      sol.push_back(p + v * t1);
      return 1;
    }

    t1 = (-f - sqrt(delta)) / (2 * e); sol.push_back(p + v * t1);
    t2 = (-f + sqrt(delta)) / (2 * e); sol.push_back(p + v * t2);
    return 2;
  }

  // signed area of intersection of circle(c.o, c.r) and
  // triangle(c.o, s.a, s.b) [cross(a-o, b-o)/2]
  double areaCircleTriIntersection(Circle c, Segment s){
    using namespace Linear;
    double OA = getLength(c.o - s.a);
    double OB = getLength(c.o - s.b);

    // sector
    if (dcmp(getDistanceToSegment(c.o, s.a, s.b) - c.r) >= 0)
      return fix_acute(getSignedAngle(s.a - c.o, s.b - c.o)) * (c.r*c.r) / 2.0;

    // triangle
    if (dcmp(OA - c.r) <= 0 && dcmp(OB - c.r) <= 0)
      return getCross(c.o-s.b,s.a-s.b) / 2.0;

    // three part: (A, a) (a, b) (b, B)
    vector<Point>Sect; double t1,t2;
    getLineCircleIntersection(s.a, s.b, c, t1, t2, Sect);
    return areaCircleTriIntersection(c, Segment(s.a, Sect[0]))
      + areaCircleTriIntersection(c, Segment(Sect[0], Sect[1]))
      + areaCircleTriIntersection(c, Segment(Sect[1], s.b));
  }

  // area of intersecion of circle(c.o, c.r) and simple polyson(p[])
  // Tested : ZOJ 2675 - Little Mammoth
  double areaCirclePolygon(Circle c, Polygon p){
    double res = .0;
    int n = p.size();
    for (int i = 0; i < n; ++ i)
      res += areaCircleTriIntersection(c, Segment(p[i], p[(i+1)%n]));
    return fabs(res);
  }

  // interior          (d < R - r)         ----> -2
  // interior tangents (d = R - r)         ----> -1
  // concentric        (d = 0)
  // secants           (R - r < d < R + r) ---->  0
  // exterior tangents (d = R + r)         ---->  1
  // exterior          (d > R + r)         ---->  2
  int getPos(Circle o1, Circle o2) {
    using namespace Vectorial;
    double d = getLength(o1.o - o2.o);
    int in = dcmp(d - fabs(o1.r - o2.r)), ex = dcmp(d - (o1.r + o2.r));
    return in<0 ? -2 : in==0? -1 : ex==0 ? 1 : ex>0? 2 : 0;
  }

  int getCircleCircleIntersection (Circle o1, Circle o2, vector<Point>& sol) {
    double d = getLength(o1.o - o2.o);
    if (dcmp(d) == 0) {
      if (dcmp(o1.r - o2.r) == 0) return -1;
      return 0;
    }
    if (dcmp(o1.r + o2.r - d) < 0) return 0;
    if (dcmp(fabs(o1.r-o2.r) - d) > 0) return 0;

    Vector v = o2.o - o1.o;
    double co = (o1.r*o1.r + getPLength(v) - o2.r*o2.r) / (2 * o1.r * getLength(v));
    double si = sqrt(fabs(1.0 - co*co));
    Point p1 = scale(cw(v,co, si), o1.r) + o1.o;
    Point p2 = scale(ccw(v,co, si), o1.r) + o1.o;

    sol.push_back(p1);
    if (p1 == p2) return 1;
    sol.push_back(p2);
    return 2;
  }

  double areaCircleCircle(Circle o1, Circle o2){
    Vector AB = o2.o - o1.o;
    double d = getLength(AB);
    if(d >= o1.r + o2.r) return 0;
    if(d + o1.r <= o2.r) return pi * o1.r * o1.r;
    if(d + o2.r <= o1.r) return pi * o2.r * o2.r;

    double alpha1 = acos((o1.r * o1.r + d * d - o2.r * o2.r) / (2.0 * o1.r * d));
    double alpha2 = acos((o2.r * o2.r + d * d - o1.r * o1.r) / (2.0 * o2.r * d));
    return o1.sector(2*alpha1) + o2.sector(2*alpha2);
  }

  int getTangents (Point p, Circle o, Vector* v) {
    Vector u = o.o - p;
    double d = getLength(u);
    if (d < o.r) return 0;
    else if (dcmp(d - o.r) == 0) {
      v[0] = rotate(u, pi / 2);
      return 1;
    } else {
      double ang = asin(o.r / d);
      v[0] = rotate(u, -ang);
      v[1] = rotate(u, ang);
      return 2;
    }
  }
  int getTangentPoints (Point p, Circle o, vector<Point>& v) {
    Vector u = p - o.o ;
    double d = getLength(u);
    if (d < o.r) return 0;
    else if (dcmp(d - o.r) == 0) {
      v.push_back(o.o+u);
      return 1;
    } else {
      double ang = acos(o.r / d);
      u = u / getLength(u) * o.r;
      v.push_back(o.o+rotate(u, -ang));
      v.push_back(o.o+rotate(u, ang));
      return 2;
    }
  }

  int getTangents (Circle o1, Circle o2, Point* a, Point* b) {
    int cnt = 0;
    if (dcmp(o1.r-o2.r) < 0) { swap(o1, o2); swap(a, b); }
    double d2 = getPLength(o1.o - o2.o);
    double rdif = o1.r - o2.r, rsum = o1.r + o2.r;
    if (dcmp(d2 - rdif * rdif) < 0) return 0;
    if (dcmp(d2) == 0 && dcmp(o1.r - o2.r) == 0) return -1;

    double base = getAngle(o2.o - o1.o);
    if (dcmp(d2 - rdif * rdif) == 0) {
      a[cnt] = o1.point(base); b[cnt] = o2.point(base); cnt++;
      return cnt;
    }

    double ang = acos( (o1.r - o2.r) / sqrt(d2) );
    a[cnt] = o1.point(base+ang); b[cnt] = o2.point(base+ang); cnt++;
    a[cnt] = o1.point(base-ang); b[cnt] = o2.point(base-ang); cnt++;

    if (dcmp(d2 - rsum * rsum) == 0) {
      a[cnt] = o1.point(base); b[cnt] = o2.point(pi+base); cnt++;
    }
    else if (dcmp(d2 - rsum * rsum) > 0) {
      double ang = acos( (o1.r + o2.r) / sqrt(d2) );
      a[cnt] = o1.point(base+ang); b[cnt] = o2.point(pi+base+ang); cnt++;
      a[cnt] = o1.point(base-ang); b[cnt] = o2.point(pi+base-ang); cnt++;
    }
    return cnt;
  }

  Circle CircumscribedCircle(Point p1, Point p2, Point p3) {
    double Bx = p2.x - p1.x, By = p2.y - p1.y;
    double Cx = p3.x - p1.x, Cy = p3.y - p1.y;
    double D = 2 * (Bx * Cy - By * Cx);
    double cx = (Cy * (Bx * Bx + By * By) - By * (Cx * Cx + Cy * Cy)) / D + p1.x;
    double cy = (Bx * (Cx * Cx + Cy * Cy) - Cx * (Bx * Bx + By * By)) / D + p1.y;
    Point p = Point(cx, cy);
    return Circle(p, getLength(p1 - p));
  }

  Circle InscribedCircle(Point p1, Point p2, Point p3) {
    double a = getLength(p2 - p3);
    double b = getLength(p3 - p1);
    double c = getLength(p1 - p2);
    Point p = (p1 * a + p2 * b + p3 * c) / (a + b + c);
    return Circle(p, getDistanceToLine(p, p1, p2));
  }
  
  //distance From P : distance from Q =  rp : rq
  Circle getApolloniusCircle(const Point& P,const Point& Q, double rp, double rq ){
    rq *= rq ;
    rp *= rp ;
    double a = rq - rp ;
    assert(dcmp(a));
    double g = rq * P.x - rp * Q.x ; g /= a ;
    double h = rq * P.y - rp * Q.y ; h /= a ;
    double c = rq*P.x*P.x-rp*Q.x*Q.x+rq*P.y*P.y-rp*Q.y*Q.y ;
    c /= a ;
    Point o(g,h);
    double R = g*g +h*h - c ;
    R = sqrt(R);
    return Circle(o,R);
  }
};