namespace Triangular {
  using namespace Vectorial;

  double getAngle (double a, double b, double c) { return acos((a*a+b*b-c*c) / (2*a*b)); }
  double getArea (double a, double b, double c) { double s =(a+b+c)/2; return sqrt(s*(s-a)*(s-b)*(s-c)); }
  double getArea (double a, double h) { return a * h / 2; }
  double getArea (Point a, Point b, Point c) { return fabs(getCross(b - a, c - a)) / 2; }
  double getDirArea (Point a, Point b, Point c) { return getCross(b - a, c - a) / 2;}

  //ma/mb/mc = length of median from side a/b/c
  double getArea_(double ma,double mb,double mc) {double s=(ma+mb+mc)/2; return 4/3.0 * sqrt(s*(s-ma)*(s-mb)*(s-mc));}

  //ha/hb/hc = length of perpendicular from side a/b/c
  double get_Area(double ha,double hb,double hc){
    double H=(1/ha+1/hb+1/hc)/2; double _A_ = 4 * sqrt(H * (H-1/ha)*(H-1/hb)*(H-1/hc)); return 1.0/_A_;
  }

  bool pointInTriangle(Point a, Point b, Point c, Point p){
    double s1 = getArea(a,b,c);
    double s2 = getArea(p,b,c) + getArea(p,a,b) + getArea(p,c,a);
    return dcmp(s1 - s2) == 0;
  }
};