// Vector.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Vector.h"

using namespace std;

void vector_init(Vector_s& v, int s)
{
  v.elem = new double[s];
  v.sz = s;
}


double read_and_sum_struct(int s)
{
  Vector_s v;
  vector_init(v, s);
  cout << "Provide " << s << " input values: " << endl;
  for (int i = 0; i != s; ++i)
  {
    cin >> v.elem[i];
  }

  double sum = 0;
  for (int i = 0; i != s; ++i)
    sum += v.elem[i];

  return sum;
}


double read_and_sum_class(int s)
{
  Vector v(s);
  cout << "Provide " << s << " input values: " << endl;
  for (int i = 0; i != s; ++i)
    cin >> v[i];

  double sum = 0;
  for (int i = 0; i != s; ++i)
    sum += v[i];

  return sum;

}


Vector::Vector(int s)
{
  if (s < 0) // enforcing invariant that Vector supports size [0:size())
    throw length_error{ "Vector::Vector()" };
  elem = new double[s];
  sz = s;
  for (int i = 0; i != s; ++i)
    elem[i] = 0;  // possible due to return by reference "double& operator[](int i); "
}

Vector::~Vector()
{

  cout << "Vector Destructor" << endl;
  delete[] elem;
}


double& Vector::operator[](int i)
{
  if (i < 0 || size() <= i) //enforcing invariant and assumption about the class. 
    throw out_of_range{ "Vector::operator[]" };

  return elem[i]; 
}


//add new element at the back of Vector
// - create new vector with size() + 1
// - copy contents of elem to new vector
// - add new element
// - delete elem
// - new on elem with correct size
// - copy contents of temp vector back to elem
// increment size by 1
// O(2n) time
// O(n) space
void Vector::push_back(double d)
{
  Vector v(size() + 1);
  for (int i = 0; i != size() + 1; ++i)
    v[i] = this->elem[i];

  v[size()] = d;

  delete[] elem;

  elem = new double[size() + 1];

  for (int i = 0; i < v.size(); ++i)
    elem[i] = v[i];

  sz++;
}


int out_of_range_test(Vector& v)
{
  try {
    v[v.size()] = v.size()+1;
  }
  catch (out_of_range)
  {
    cout << "ERROR :: OUT_OF_RANGE :: Tried to access Vector beyond the max size" << endl;
  }
  return 0;
}

void length_error_test(int s)
{
  try{
    Vector v(s);
  }
  catch (length_error)
  {
    cout << "ERROR :: LENGTH_ERROR :: Trying to create a vector element with < 0 size = " << s  << endl;
    throw; // rethrow to be caught at another higher level if needed. 

  }
  catch (std::bad_alloc)
  {
    cout << "ERROR :: BAD_ALLOC :: Cannot allocate memory " << endl;
    terminate(); // will abruptly call abort on the program
  }
}


Vector read(istream& is)
{
  Vector v;
  for (double d; is >> d;)
    v.push_back(d);
  return v;
}

int _tmain(int argc, _TCHAR* argv[])
{
  double sum = read_and_sum_struct(2);
  cout << "Sum of inputs: " << sum << endl;

  const int n = 6;
  Vector v(n);

  sum = read_and_sum_class(2);
  cout << "Sum of inputs: " << sum << endl;

  out_of_range_test(v);
  try
  {
    length_error_test(-27);
  }
  catch (...) // catch all possible exceptions
  {
    cout << "ERROR :: LENGTH_ERROR_TEST :: rethrow succeeded" << endl;
  } 

  //descrutor test
  {
    Vector v2(2 * n);
    out_of_range_test(v2);
  }     //v2 gets destroyed here

  out_of_range_test(v);


  cout << "Vector push_back test" << endl;
  cout << "Vector v size = " << v.size() << endl;
  cout << "Vector v last elem = " << v[v.size() - 1] << endl;
  v.push_back(1.2);

  cout << "Vector v new size = " << v.size() << endl;
  cout << "Vector v last elem = " << v[v.size() - 1] << endl;


  cout << "Vector istream read and push_back test" << endl;
  istream is; // ?? TODO: read from file or command line?? 
  read(is);

  cout << "Hit any key to finish" << endl;

  char key;
  cin >> key;
	return 0;
} // v gets destroyed here

