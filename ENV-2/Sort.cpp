#include "Sort.h" 
using namespace std; 
 
bool compareAbs(const Complex& a, const Complex& b)  
{ 
    return a.abs() > b.abs(); 
} 
 
void bubbleSort(vector<Complex>& arr)  
{ 
    size_t n = arr.size(); 
 
    for (size_t i = 0; i < n - 1; ++i)  
    { 
        for (size_t j = 0; j < n - i - 1; ++j)  
        { 
            if (compareAbs(arr[j], arr[j + 1]))  
            { 
                swap(arr[j], arr[j + 1]); 
            } 
        } 
    } 
}
