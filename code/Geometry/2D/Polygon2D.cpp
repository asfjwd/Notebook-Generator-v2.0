typedef vector<Point> Polygon;
namespace Polygonal {
  using namespace Vectorial;
  using namespace Linear;
  using namespace Triangular;

  double getSignedArea (Point* p, int n) {
    double ret = 0;
    for (int i = 0; i < n-1; i++)
      ret += (p[i]-p[0]) * (p[i+1]-p[0]);
    return ret/2;
  }

  int isPointInPolygon (Point o, Point* p, int n) {
    int wn = 0;
    for (int i = 0; i < n; i++) {
      int j = (i + 1) % n;
      if (onSegment(o, p[i], p[j]) || o == p[i]) return 0;
      int k = dcmp(getCross(p[j] - p[i], o-p[i]));
      int d1 = dcmp(p[i].y - o.y);
      int d2 = dcmp(p[j].y - o.y);
      if (k > 0 && d1 <= 0 && d2 > 0) wn++;
      if (k < 0 && d2 <= 0 && d1 > 0) wn--;
    }
    return wn ? -1 : 1;
  }

  void rotatingCalipers(Point *p, int n, vector<Segment>& sol) {
    sol.clear();
    int j = 1; p[n] = p[0];
    for (int i = 0; i < n; i++) {
      while (getCross(p[j+1]-p[i+1], p[i]-p[i+1]) > getCross(p[j]-p[i+1], p[i]-p[i+1]))
        j = (j+1) % n;
      sol.push_back(Segment(p[i],p[j]));
      sol.push_back(Segment(p[i + 1],p[j + 1]));
    }
  }

  void rotatingCalipersGetRectangle (Point *p, int n, double& area, double& perimeter) {
    p[n] = p[0];
    int l = 1, r = 1, j = 1;
    area = perimeter = 1e20;

    for (int i = 0; i < n; i++) {
      Vector v = (p[i+1]-p[i]) / getLength(p[i+1]-p[i]);
      while (dcmp(getDot(v, p[r%n]-p[i]) - getDot(v, p[(r+1)%n]-p[i])) < 0) r++;
      while (j < r || dcmp(getCross(v, p[j%n]-p[i]) - getCross(v,p[(j+1)%n]-p[i])) < 0) j++;
      while (l < j || dcmp(getDot(v, p[l%n]-p[i]) - getDot(v, p[(l+1)%n]-p[i])) > 0) l++;
      double w = getDot(v, p[r%n]-p[i])-getDot(v, p[l%n]-p[i]);
      double h = getDistanceToLine (p[j%n], p[i], p[i+1]);
      area = min(area, w * h);
      perimeter = min(perimeter, 2 * w + 2 * h);
    }
  }

  Polygon cutPolygon (Polygon u, Point a, Point b) {
    Polygon ret;
    int n = u.size();
    for (int i = 0; i < n; i++) {
      Point c = u[i], d = u[(i+1)%n];
      if (dcmp((b-a)*(c-a)) >= 0) ret.push_back(c);
      if (dcmp((b-a)*(d-c)) != 0) {
        Point t;
        getIntersection(a, b-a, c, d-c, t);
        if (onSegment(t, c, d))
          ret.push_back(t);
      }
    }
    return ret;
  }

  int halfPlaneIntersection(DirLine* li, int n, Point* poly) {
    sort(li, li + n);

    int first, last;
    Point* p = new Point[n];
    DirLine* q = new DirLine[n];
    q[first=last=0] = li[0];

    for (int i = 1; i < n; i++) {
      while (first < last && !onLeft(li[i], p[last-1])) last--;
      while (first < last && !onLeft(li[i], p[first])) first++;
      q[++last] = li[i];

      if (dcmp(q[last].v * q[last-1].v) == 0) {
        last--;
        if (onLeft(q[last], li[i].p)) q[last] = li[i];
      }

      if (first < last)
        getIntersection(q[last-1].p, q[last-1].v, q[last].p, q[last].v, p[last-1]);
    }

    while (first < last && !onLeft(q[first], p[last-1])) last--;
    if (last - first <= 1) { delete [] p; delete [] q; return 0; }
    getIntersection(q[last].p, q[last].v, q[first].p, q[first].v, p[last]);

    int m = 0;
    for (int i = first; i <= last; i++) poly[m++] = p[i];
    delete [] p; delete [] q;
    return m;
  }

  Polygon simplify (const Polygon& poly) {
    Polygon ret;
    int n = poly.size();
    for (int i = 0; i < n; i++) {
      Point a = poly[i];
      Point b = poly[(i+1)%n];
      Point c = poly[(i+2)%n];
      if (dcmp((b-a)*(c-b)) != 0 && (ret.size() == 0 || b != ret[ret.size()-1]))
        ret.push_back(b);
    }
    return ret;
  }

  Point ComputeCentroid( Point* p,int n){
    Point c(0,0);
    double scale = 6.0 * getSignedArea(p,n);
    for (int i = 0; i < n; i++){
      int j = (i+1) % n;
      c = c + (p[i]+p[j])*(p[i].x*p[j].y - p[j].x*p[i].y);
    }
    return c / scale;
  }

  // Tested : https://www.spoj.com/problems/INOROUT
  // pt must be in ccw order with no three collinear points
  // returns inside = 1, on = 0, outside = -1
  int pointInConvexPolygon(Point* pt, int n, Point p){
    assert(n >= 3);
    int lo = 1 , hi = n - 1 ;
    while(hi - lo > 1){
      int mid = (lo + hi) / 2;
      if(getCross(pt[mid] - pt[0], p - pt[0]) > 0) lo = mid;
      else hi = mid;
    }

    bool in = pointInTriangle(pt[0], pt[lo], pt[hi], p);
    if(!in) return -1;

    
    if(getCross(pt[lo] - pt[lo-1], p - pt[lo-1]) == 0) return 0;
    if(getCross(pt[hi] - pt[lo], p - pt[lo]) == 0) return 0;
    if(getCross(pt[hi] - pt[(hi+1)%n], p - pt[(hi+1)%n]) == 0) return 0;

   
    return 1;
  }
  
  // Tested : https://toph.co/p/cover-the-points
  // Calculate [ACW, CW] tangent pair from an external point
  #define CW 		-1
  #define ACW	 	 1
  int direction(Point st, Point ed, Point q)       {return dcmp(getCross(ed - st, q - ed));}
  bool isGood(Point u, Point v, Point Q, int dir)  {return direction(Q, u, v) != -dir;}
  Point better(Point u, Point v, Point Q, int dir) {return direction(Q, u, v) == dir ? u : v;}

  Point tangents(Point* pt, Point Q, int dir, int lo, int hi){
    while(hi - lo > 1){
      int mid = (lo + hi)/2;
      bool pvs = isGood(pt[mid], pt[mid - 1], Q, dir);
      bool nxt = isGood(pt[mid], pt[mid + 1], Q, dir);

      if(pvs && nxt) return pt[mid];
      if(!(pvs || nxt)){
        Point p1 = tangents(pt, Q, dir, mid+1, hi);
        Point p2 = tangents(pt, Q, dir, lo, mid - 1);
        return better(p1, p2, Q, dir);
      }

      if(!pvs){
        if(direction(Q, pt[mid], pt[lo]) == dir)  hi = mid - 1;
        else if(better(pt[lo], pt[hi], Q, dir) == pt[lo]) hi = mid - 1;
        else lo = mid + 1;
      }
      if(!nxt){
        if(direction(Q, pt[mid], pt[lo]) == dir)  lo = mid + 1;
        else if(better(pt[lo], pt[hi], Q, dir) == pt[lo]) hi = mid - 1;
        else lo = mid + 1;
      }
    }

    Point ret = pt[lo];
    for(int i = lo + 1; i <= hi; i++) ret = better(ret, pt[i], Q, dir);
    return ret;
  }

  // [ACW, CW] Tangent
  pair<Point, Point> get_tangents(Point* pt, int n, Point Q){
    Point acw_tan = tangents(pt, Q, ACW, 0, n - 1);
    Point cw_tan = tangents(pt, Q, CW, 0, n - 1);
    return make_pair(acw_tan, cw_tan);
  }
};