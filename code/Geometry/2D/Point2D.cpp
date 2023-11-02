const double pi = 4 * atan(1);
const double eps = 1e-6;

inline int dcmp (double x) { if (fabs(x) < eps) return 0; else return x < 0 ? -1 : 1; }
double fix_acute(double th) {return th<-pi ? (th+2*pi): th>pi ? (th-2*pi) : th;}

inline double getDistance (double x, double y) { return sqrt(x * x + y * y); }
inline double torad(double deg) { return deg / 180 * pi; }

struct Point {
  double x, y;
  Point (double x = 0, double y = 0): x(x), y(y) {}
  void read () { scanf("%lf%lf", &x, &y); }
  void write () { printf("%lf %lf", x, y); }

  bool operator == (const Point& u) const { return dcmp(x - u.x) == 0 && dcmp(y - u.y) == 0; }
  bool operator != (const Point& u) const { return !(*this == u); }
  bool operator < (const Point& u) const { return dcmp(x - u.x) < 0 || (dcmp(x-u.x)==0 && dcmp(y-u.y) < 0); }
  bool operator > (const Point& u) const { return u < *this; }
  bool operator <= (const Point& u) const { return *this < u || *this == u; }
  bool operator >= (const Point& u) const { return *this > u || *this == u; }
  Point operator + (const Point& u) { return Point(x + u.x, y + u.y); }
  Point operator - (const Point& u) { return Point(x - u.x, y - u.y); }
  Point operator * (const double u) { return Point(x * u, y * u); }
  Point operator / (const double u) { return Point(x / u, y / u); }
  double operator * (const Point& u) { return x*u.y - y*u.x; }
};

inline double getDistance (Point a, Point b) { double x=a.x-b.x, y=a.y-b.y; return sqrt(x*x + y*y); }
