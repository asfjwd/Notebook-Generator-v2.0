namespace Poly{
  using namespace Vectorial;
  Sphere SmallestEnclosingSphere(Polyhedron p){
    int n = p.size();
    Point3D C(0,0,0);
    for(int i=0; i<n; i++) C = C + p[i];
    C = C / n;

    double P = 0.1;
    int pos = 0;
    int Accuracy = 70000;
    for (int i = 0; i < Accuracy; i++) {
      pos = 0;
      for (int j = 1; j < n; j++){
        if(getPLength(C - p[j]) > getPLength(C - p[pos])) pos = j;
      }
      C = C + (p[pos] - C)*P;
      P *= 0.998;
    }
    return Sphere(C, getPLength(C - p[pos]));
  }
}

struct Pyramid{
  int n;     //number of side of the pyramid
  double l;  //length of each side
  double ang;

  Pyramid(int n, double l) {this->n=n; this->l=l; ang=pi/n;}
  double getBaseArea() {return l * l * n / (4* tan(ang));}
  double getHeight() {return l * sqrt(1 - 1 / (4*sin(ang)*sin(ang)) );}
  double getVolume() {return getBaseArea() * getHeight() / 3;}
};