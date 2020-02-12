// Inaara Ahmed-Fazal   20821562
// Kayla Jetha          20822795
// Meghan LaCoste       20845775

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <cassert>
#include "lab1_polynomial.h"

using namespace std;

Polynomial :: Polynomial(int A[], int size) {
	if(size == 0) {
		data.resize(1);
	}
	else {
		data.resize(size);
		for(int index = 0; index < size; index++) {
			data[index] = A[index];
		}
	}
	
}

Polynomial :: Polynomial() {
	srand(time(0));
	
	int size = rand() % 1001;
	
	data.resize(size);
	for(int index = 0; index < size; index++) {
		data[index] = (rand() % 2001) - 1000;
	}
}

Polynomial :: Polynomial(string fileName) {
	ifstream my_ifstream; // create ifstream instance
	
	my_ifstream.open(fileName); // open the input file
	
	int size;
	my_ifstream >> size;
	data.resize(size);
	
	for(int index = 0; !my_ifstream.fail(); index++) {
		my_ifstream >> data [index];
	}
	
	my_ifstream.close();
}

bool Polynomial :: operator==(const Polynomial& target) const {
	bool are_equal = true;
	if(data.size() != target.data.size()) {
		are_equal = false;
	}
	else {
		for(int index = 0; index < data.size(); index++) {
			if(data[index] != target.data[index]) are_equal = false;
		}
	}
	
	return are_equal;
}

void Polynomial :: print() {

	cout << data[data.size()-1] << "x^" << data.size()-1;
	
	for(int index = data.size()-2; index >= 0; index--) {
		if(data[index] >= 0) {
			cout << " + " << data[index] << "x^" << index;
		} else {
			cout << " + " << "(" << data[index] << ")"<< "x^" << index;
		}
	
	}
}

Polynomial Polynomial :: operator+(const Polynomial& target) {
	for(int index = 0; index < target.data.size(); index++) {
		if(index < data.size()) data[index] += target.data[index];
		else data.push_back(target.data[index]);
	}
	return *this;
}

Polynomial Polynomial :: operator-(const Polynomial& target) {
	for(int index = 0; index < target.data.size(); index++) {
		if(index < data.size()) data[index] -= target.data[index];
		else data.push_back(-target.data[index]);
	}
	return *this;
}

Polynomial Polynomial :: operator*(const Polynomial& target) {
	int new_size = data.size() + target.data.size()-1;
	int coefficients [new_size];

	for(int index = 0; index < new_size; index++) {
		int coefficient = 0;
		for(int n = index; n >= 0; n--) {
			if(n < data.size() && index-n < target.data.size())
				coefficient += data[n] * target.data[index-n];
		}
		coefficients[index] = coefficient;
	}
	data.resize(new_size);
	for(int index = 0; index < new_size; index++) {
		data[index] = coefficients[index];
	}
	return *this;
}

Polynomial Polynomial :: derivative() {
	for(int index = 0; index < data.size()-1; index++)
		data[index] = (index + 1) * data[index + 1];
	data[data.size()-1] = 0;	
	return *this;
}

Polynomial :: ~Polynomial () {
	// we did not use any pointers but if we did
	// we would delete them here and then set them to NULL 
	// so they would be invalid if called on again
	//cout << "deconstructor would work here" << endl;
}

class PolynomialTest {
	
	void test_operator_equals() {
		
		int equal_1[] = {1,2,3,4};
		Polynomial a = Polynomial("equal_2.txt");
		Polynomial b = Polynomial(equal_1, 4);
		
		//Test two arrays that are equal (one read from a file and one generated in this class)
		assert(a == b);
		cout << "Test 1.1 for operator== passed" << endl;
		
		int equal_3[] = {3,1,4,2};
		Polynomial c = Polynomial(equal_3, 4);
		
		//Test two arrays that have the same coefficients but are in different orders
		assert(!(a == c));
		cout << "Test 1.2 for operator== passed" << endl;
		
		int equal_4[] = {0};
		int equal_5[0];
		Polynomial d = Polynomial(equal_4, 1);
		Polynomial e = Polynomial(equal_5, 0);
		
		//Test two zero arrays: one initiated with a value of zero and the other empty
		assert(d == e);
		cout << "Test 1.3 for operator== passed" << endl;
		
	}
	
	void test_operator_add() {
		
		int add_1[] = {1,2,3,4};
		int actual_sum1[] = {2,4,6,8};
		int add_3[] = {4,5,7,-1,-3,8};
		int actual_sum2[] = {5,7,10,3,-3,8};
		int add_4[] = {1,2,3,4};
		int add_5[] = {0,5,0,0};
		int actual_sum3[] = {1,7,3,4};
		
		//test that two arrays of the same size add correctly
		Polynomial a = Polynomial("equal_2.txt");
		Polynomial b = Polynomial(add_1, 4);
		Polynomial sum = Polynomial(actual_sum1, 4);
		assert( ( a + b ) == sum );
		cout << "Test 1 for operator + passed" << endl;
		
		// test that two arrays of different size add correctly when second array larger & when first array larger
		Polynomial c = Polynomial(add_3, 6);
		Polynomial d = Polynomial(add_4,4);
		Polynomial sum2 = Polynomial (actual_sum2, 6);
		assert( ( b + c ) == sum2 );
		cout << "Test 2 for operator + passed" << endl;
		assert( ( c + d ) == sum2 );
		cout << "Test 3 for operator + passed" << endl;
		
		// test that two arrays are added properly when some elements have zeros 
		Polynomial e = Polynomial(add_5,4);
		Polynomial sum3 = Polynomial(actual_sum3,4);
		assert((e + d) == sum3);
		cout << "Test 4 for operator + passed" << endl;
		
	}
	
	void test_operator_subtract() {
		//Test two polynomials of the same size 
		int poly_1[] = {-9,4,5,2,2};
		Polynomial sb1 = Polynomial(poly_1,5);
		int poly_2[] = {4,6,-5,1,1};
		Polynomial sb2 = Polynomial(poly_2,5);
		int difference1[] = {-13,-2,10,1,1};
		Polynomial d1 = Polynomial(difference1,5);
	
		assert((sb1 - sb2) == d1);
		cout << "Test 3.1 for operator- passed" << endl;
	
		//Test subtracting, with one empty polynomial
		int poly_3[] = {1,2,3,4,5,6};
		Polynomial sb3 = Polynomial(poly_3,6);
		int poly_4[] = {0,0,0,0,0,0};
		Polynomial sb4 = Polynomial(poly_4,6);
		int difference2[] = {1,2,3,4,5,6};
		Polynomial d2 = Polynomial(difference2,6);
	
		assert((sb3 - sb4) == d2);
		cout << "Test 3.2 for operator- passed" <<endl;

		//Test subtracting polynomials for polynomials of different size, first one is a bigger size
		int poly_5[] = {9,0,-4,7,2};
		Polynomial sb5 = Polynomial(poly_5,5);
		int poly_6[] = {6,3,2};
		Polynomial sb6 = Polynomial(poly_6,3);
		int difference3[] = {3,-3,-6,7,2};
		Polynomial d3 = Polynomial(difference3,5);
	
		assert((sb5 - sb6) == d3);
		cout << "Test 3.3 for operator- passed" << endl;
	
		//Test subtracting polynomials for polynomials of different size, second one is a bigger size
		int poly_7[] = {0,7,-5,2,-5,3};
		Polynomial sb7 = Polynomial(poly_7,6);
		int poly_8[] = {9,5,-6,2,-7,8,2,1};
		Polynomial sb8 = Polynomial(poly_8,8);
		int difference4[] = {-9,2,1,0,2,-5,-2,-1};
		Polynomial d4 = Polynomial(difference4,8);
	
		assert((sb7 - sb8) == d4);
		cout << "Test 3.4 for operator- passed" << endl;
	}
	
	void test_operator_multiply() {
		int m1 [] = {-88, -9, 3, 1};
		int m2 [] = {4, 2};
		int prod1 [] = {-352, -212, -6, 10, 2};
		Polynomial mp1 = Polynomial(m1, 4);
		Polynomial mp2 = Polynomial(m2, 2);
		Polynomial prod_mp1 = Polynomial(prod1, 5);
		
		// Tests a larger polynomial multiplied by a smaller one
		assert((mp1*mp2) == prod_mp1);
		cout << "Test 4.1 for operator* passed" << endl;
		
		int m3 [] = {0};
		int prod2 [] = {0,0,0,0};
		Polynomial mp3 = Polynomial(m1, 4);
		Polynomial mp4 = Polynomial(m3, 1);
		Polynomial prod_mp2 = Polynomial(prod2, 4);
		
		// Tests a polynomial multiplied by a zero polynomial
		assert((mp3 * mp4) == prod_mp2);
		cout << "Test 4.2 for operator* passed" << endl;
		
		Polynomial mp5 = Polynomial(m1, 4);
		
		//Tests a smaller polynomial multiplied by a larger one
		assert((mp2*mp5) == prod_mp1);
		cout << "Test 4.3 for operator* passed" << endl;
	}
	
	void test_derivative() {
		//Test for a normal polynomial derivative
		int poly_1[] = {2,5,-3,6};
		Polynomial p1 = Polynomial(poly_1,4);
		int deriv_1[] = {5,-6,18,0};
		Polynomial d1 = Polynomial(deriv_1,4);
		
		assert( p1.derivative() == d1);
		cout << "Test 5.1 for derivative() passed" << endl;
		
		//Test for a polynomial with a zero term
		int poly_2[] = {3,6,7,0,3,1,2};
		Polynomial p2 = Polynomial(poly_2,7);
		int deriv_2[] = {6,14,0,12,5,12,0};
		Polynomial d2 = Polynomial(deriv_2,7);
		
		assert( p2.derivative() == d2);
		cout << "Test 5.2 for derivative() passed" << endl;
		
		//Test a polynomial with just a constant
		int poly_3[] = {2};
		Polynomial p3 = Polynomial(poly_3,1);
		int deriv_3[] = {0};
		Polynomial d3 = Polynomial(deriv_3,1);
		
		assert( p3.derivative() == d3);
		cout << "Test 5.3 for derivative() passed" << endl;
		
	}
	
	//This driver method tests the print() method and 3 constructors using visual inspection
	void test_print_and_constructors() {
		//Tests the array and size constructor
		int test[] = {1,5,-3,4};
		Polynomial test_print = Polynomial(test, 4);
		cout << "Polynomial generated with array {1, 5, -3, 4} and size 4:" << endl;
		test_print.print();
		cout << endl;
		cout << endl;
		
		//Tests the random constructor		
		Polynomial test_print2 = Polynomial();
		cout << "Polynomial generated with randomizing constructor:" << endl;
		test_print2.print();
		cout << endl;
		cout << endl;
		
		//Tests the file constructor	
		Polynomial test_print3 = Polynomial("equal_2.txt");
		cout << "Polynomial generated with text file equal_2.txt:" << endl;
		test_print3.print();
		cout << endl;
	}
	
public: 
	void run() {
		
		test_operator_equals();
		cout << endl;
		
		test_operator_add();
		cout << endl;
		
		test_operator_subtract();
		cout << endl;
		
		test_operator_multiply();
		cout << endl;
		
		test_derivative();
		cout << endl;
		
		test_print_and_constructors();
	}
};

int main() {
	PolynomialTest p1;
	p1.run();
	return 0;
}
