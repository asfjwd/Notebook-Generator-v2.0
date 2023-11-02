struct Star{
  int n;    // number of side of the star
  double r; // radius of the circum-circle
  Star(int n,double r) {this->n=n; this->r=r;}

  double getArea(){
    double theta=pi/n;
    double s=2*r*sin(theta);
    double R=0.5*s/tan(theta);
    double a=0.5*n*s*R;
    double a2=0.25*s*s/tan(1.5*theta);
    return a-n*a2;
  }
};