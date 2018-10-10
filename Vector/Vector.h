#include <iostream>

struct Vector_s
{
  int sz; 
  double* elem;
};

class Vector
{
public:
  Vector() {}
  Vector(int s); //:  elem{ new double[s] }, sz{ s } {}
  ~Vector();
  double& operator[] (int i); // return by ref instead of pointer allows funciton to be use at LHS of =
  int size() { return sz;  }

  void push_back(double d);
private:
  int sz;
  double* elem;

};