// Inaara Ahmed-Fazal   20821562
// Kayla Jetha          20822795
// Meghan LaCoste       20845775

#ifndef LAB1_POLYNOMIAL
#define LAB1_POLYNOMIAL

#include <vector>
#include <iostream>
#include <random>
#include <time.h>
#include <fstream>

using namespace std;

class Polynomial {
	vector<int> data;
	
public:
	//constructors
	Polynomial();
	Polynomial(int A[], int size);
	Polynomial(string fileName);
	
	//service methods
	bool operator==(const Polynomial& target) const; // performs *this == target
	void print(); // prints the polynomial (e.g., 2x^3 + 1x^0)
	
	Polynomial operator+(const Polynomial& target); // performs *this + target
	Polynomial operator-(const Polynomial& target); // performs *this - target
	Polynomial operator*(const Polynomial& target); // performs *this * target
	
	Polynomial derivative(); //computes the derivative d/dx of *this
	
	~Polynomial();
	friend class PolynomialTest;
};
#endif
