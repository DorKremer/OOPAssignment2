#pragma once
#include "Polynomial.h"
class Rational
{
public:
	Rational();
	Rational(const Polynomial& nom, const Polynomial& denom);
	Polynomial& getNom();
	Polynomial& getDenom();
	void print() const;
	void operator=(const Rational& rational);
	friend ostream& operator<<(ostream& output, const Rational& rational);
	Rational& operator+(const Rational& rational);
	Rational& operator-(const Rational& rational);
	Rational& operator*(const Rational& rational);
	
private:
	Polynomial num, denom;
};

