#include "Complex.h"
    Complex::Complex(double a, double b) : a(a), b(b) {}
    Complex Complex::operator+(const Complex& other) const   
    {
   	 return Complex(a + other.a, b + other.b);   
    }
    Complex Complex::operator-(const Complex& other) const
    {      
	 return Complex(a - other.a, b - other.b);
    }
    Complex Complex::operator*(double scalar) const   
    {
         return Complex(a * scalar, b * scalar);   
    }
    double Complex::abs() const
    {
    	 return sqrt(a * a + b * b);
    }
    std::ostream& operator<<(std::ostream& os, const Complex& c)
    {
 	  os << "(" << c.a << " + " << c.b << "b)";       
          return os;
    }
