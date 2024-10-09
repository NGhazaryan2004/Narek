#include <iostream> 
#include <vector> 
#include "Complex.h" 
#include "Sort.h" 
 
int main()  
{ 
    std::vector<Complex> complexNumbers =  
    { 
	Complex(1, 2),
	Complex(3, -1),
	Complex(-4, 0),
	Complex(2, 3),
	Complex(-5, -2) 
    }; 
    for (auto& num : complexNumbers)  
    { 
     std::cout << num <<std:: endl; 
    } 
 
    bubbleSort(complexNumbers); 
    for (auto& num : complexNumbers)  
    { 
     std::cout << num <<std:: endl; 
    } 
 
    return 0; 
}
