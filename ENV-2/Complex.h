#ifndef COMPLEX_H 
#define COMPLEX_H 
#include <iostream> 
#include <cmath> 
 
class Complex  
{ 
public: 
    Complex(double a, double b); 
 
    double getReal() const; 
    double getImag() const; 
 
    Complex operator+(const Complex& other) const; 
    Complex operator-(const Complex& other) const; 
    Complex operator*(double scalar) const; 
    double abs() const; 
 
    friend std::ostream& operator<<(std::ostream& os, const Complex& c); 
 
private: 
    double a =0.0; 
    double b = 0.0; 
}; 
 
#endif
