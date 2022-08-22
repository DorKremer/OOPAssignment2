#pragma once
#include <iostream>

using namespace std;
class Polynomial
{
public:
	Polynomial();
	Polynomial(int degree);
	Polynomial(double* coefficients, int degree);
	~Polynomial();
	void setCoeff(int position, double coefficient);
	int getDegree(bool flag) const;
	static int getMaxDegree();
	double getCoeff(int position) const;
	void print() const;
	void operator=(const Polynomial& polynomial);
	Polynomial& operator+(const Polynomial& polynomial) const;
	Polynomial& operator-(const Polynomial& polynomial) const;
	Polynomial& operator*(const Polynomial& polynomial) const;
	void operator+=(const Polynomial& polynomial);
	void operator-=(const Polynomial& polynomial);
	void operator*=(const Polynomial& polynomial);
	double& operator[](int index);
	double& operator[](int index) const;
	friend Polynomial& operator*(const double& num, const Polynomial& polynomial);
	friend ostream& operator<<(ostream& output, const Polynomial& polynomial);

private:
	int potentialDegree, actualDegree;
	double* coefficients;
	static int maxDegree;
};
