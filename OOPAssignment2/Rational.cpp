#include "Rational.h"

Rational::Rational()
{
    this->denom.setCoeff(0,1);
}

Rational::Rational(const Polynomial& nom, const Polynomial& denom)
{
    this->num = nom;
    this->denom = denom;
}

Polynomial& Rational::getNom()
{
    return this->num;
}

Polynomial& Rational::getDenom()
{
    return this->denom;
}

void Rational::print() const
{
    num.print();
    cout << "--------------------------\n";
    denom.print();
}

void Rational::operator=(const Rational& rational)
{
    num = rational.num;
    denom = rational.denom;
}

Rational& Rational::operator+(const Rational& rational)
{
    Rational* result = new Rational(this->num,this->denom);
    Rational temp = Rational(rational.num, rational.denom);
    result->denom *= rational.denom;
    result->num *= rational.denom;
    temp.num *= denom;
    result->num += temp.num;
    return *result;
}

Rational& Rational::operator-(const Rational& rational)
{
    Rational* result = new Rational(this->num, this->denom);
    Rational temp = Rational(rational);
    result->denom *= rational.denom;
    temp.num *= denom;
    result->num -= temp.num;
    return *result;
}

Rational& Rational::operator*(const Rational& rational)
{
    Rational* result = new Rational(this->num, this->denom);
    result->num *= rational.num;
    result->denom *= rational.denom;
    return *result;
}

ostream& operator<<(ostream& output, const Rational& rational)
{
    output << "Numerator = " << rational.num << "--------------------------\n" << "Denominator = " << rational.denom;
    return output;
}
