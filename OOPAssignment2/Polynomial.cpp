#include "Polynomial.h"

int Polynomial::maxDegree = 0;

void Polynomial::operator=(const Polynomial& polynomial) {
    this->actualDegree = polynomial.actualDegree;
    this->potentialDegree = polynomial.potentialDegree;
    this->coefficients = new double[potentialDegree+1];
    for (int i = 0; i <= potentialDegree;i++) 
            this->coefficients[i] = polynomial.coefficients[i];
}

Polynomial& Polynomial::operator+(const Polynomial& polynomial) const
{
    int higherDegree = this->potentialDegree > polynomial.potentialDegree ? this->potentialDegree : polynomial.potentialDegree;
    int lowerDegree = this->potentialDegree < polynomial.potentialDegree ? this->potentialDegree : polynomial.potentialDegree;
    Polynomial* result = new Polynomial(higherDegree);
    result->actualDegree = this->actualDegree > polynomial.actualDegree ? this->actualDegree : polynomial.actualDegree;
    int i = 0;
    for (; i <= lowerDegree; i++)
        result->coefficients[i] = this->coefficients[i] + polynomial.coefficients[i];
    if (this->potentialDegree > polynomial.potentialDegree) {
        for (; i <= higherDegree; i++) {
            result->coefficients[i] = this->coefficients[i];
            if (coefficients[i])
                result->actualDegree = i;
        }
    }
    else {
        for (; i <= higherDegree; i++) {
            result->coefficients[i] = polynomial.coefficients[i];
            if (polynomial.coefficients[i])
                result->actualDegree = i;
        }
    }
    return *result;
}

Polynomial& Polynomial::operator-(const Polynomial& polynomial) const
{
    int higherDegree = this->potentialDegree > polynomial.potentialDegree ? this->potentialDegree : polynomial.potentialDegree;
    int lowerDegree = this->potentialDegree < polynomial.potentialDegree ? this->potentialDegree : polynomial.potentialDegree;
    Polynomial* result = new Polynomial(higherDegree);
    result->actualDegree = this->actualDegree > polynomial.actualDegree ? this->actualDegree : polynomial.actualDegree;
    int i = 0;
    for (; i <= lowerDegree; i++)
        result->coefficients[i] = this->coefficients[i] - polynomial.coefficients[i];
    if (this->potentialDegree > polynomial.potentialDegree) {
        for (; i <= higherDegree; i++)
            result->coefficients[i] = this->coefficients[i];
    }
    else {
        for (; i <= higherDegree; i++)
            result->coefficients[i] = polynomial.coefficients[i]*(-1);
    }
    return *result;
}

Polynomial& Polynomial::operator*(const Polynomial& polynomial) const
{
    Polynomial* result = new Polynomial(this->potentialDegree +polynomial.potentialDegree);
    result->actualDegree = actualDegree + polynomial.actualDegree;
    if (result->actualDegree > maxDegree)
        maxDegree = result->actualDegree;
    for (int i = 0; i <= potentialDegree; i++) {
        for (int j = 0; j <= polynomial.potentialDegree; j++) {
            result->coefficients[i + j] += coefficients[i]*polynomial.coefficients[j];
        }
    }
    return *result;
}

void Polynomial::operator+=(const Polynomial& polynomial)
{
    *this = (*this) + polynomial;
}

void Polynomial::operator-=(const Polynomial& polynomial)
{
    *this = (*this) - polynomial;
}

void Polynomial::operator*=(const Polynomial& polynomial)
{
    *this = (*this) * polynomial;
}

const double Polynomial::operator[](int index)
{
    if (index > potentialDegree || index < 0)
        exit(0);
    return coefficients[index];
}

double& Polynomial::operator[](int index) const
{
     if (index > potentialDegree || index < 0)
        exit(0);
     return coefficients[index];
}

Polynomial& operator*(const double& num, const Polynomial& polynomial)
{
    Polynomial* result = new Polynomial(polynomial.actualDegree);
    result->actualDegree = polynomial.actualDegree;
        for (int i = 0; i < polynomial.actualDegree; i++) {
            result->coefficients[i] = polynomial.coefficients[i]*num;
        }
        return *result;
}

Polynomial::Polynomial()
{
    this->potentialDegree = 0;
    this->actualDegree = 0;
    this->coefficients = new double[1];
    this->coefficients[0] = 0;
}

Polynomial::Polynomial(int degree)
{
    this->potentialDegree = degree;
    this->actualDegree = 0;
    this->coefficients = new double[degree + 1];
    for (int i = 0; i < degree + 1; i++)
        this->coefficients[i] = 0;
}

Polynomial::Polynomial(double* coefficients, int degree)
{
    this->actualDegree = 0;
    this->coefficients = new double[degree + 1];
    for (int i = 0; i <= degree; i++) {
        this->coefficients[i] = coefficients[i];
        if (coefficients[i])
            actualDegree = i;
        if (coefficients[i] && i > maxDegree) {
            maxDegree = i;
        }
    }
    this->potentialDegree = degree;
}

Polynomial::~Polynomial()
{
    delete[] coefficients;
}

void Polynomial::setCoeff(int position, double coefficient)
{
    this->coefficients[position] = coefficient;
    if (position > maxDegree && coefficient)
        maxDegree = position;
    if (position > actualDegree && coefficient)
        actualDegree = position;
    else if (position == actualDegree) {
        int flag = 0;
        for (int i = 0; i < position; i++)
            if (coefficients[i]) {
                actualDegree = i;
                flag = 1;
            }
        if (!flag)
            actualDegree = 0;
    }
}

int Polynomial::getDegree(bool flag) const
{
    if (!flag) {
        return potentialDegree;
    }
    return actualDegree;
}

int Polynomial::getMaxDegree()
{
    return maxDegree;
}

double Polynomial::getCoeff(int position) const
{
    return this->coefficients[position];
}

void Polynomial::print() const
{
    int monomPrints = 0;
    cout << "Polynomial = ";
    if (!potentialDegree||!actualDegree)
        cout << coefficients[0];
    else {
        for (int i = 0; i <= actualDegree; i++) {
            if (!i) {
                if (coefficients[i]) {
                    cout << coefficients[i];
                    monomPrints++;
                }
                else {
                    cout << 0;
                    monomPrints++;
                }
            }
            else if (coefficients[i] > 0 && monomPrints) {
                cout << "+(" << coefficients[i] << ")*X^" << i;
                monomPrints++;
            }
            else {
                cout << "-(" << coefficients[i]*(-1) << ")*X^" << i;
                monomPrints++;
            }
        }
        if (!monomPrints)
            cout << 0;
    }
    cout << endl;
}


ostream& operator<<(ostream& output, const Polynomial& polynomial)
{
    output << "Polynomial = ";
    int monomPrints = 0;
    if (!polynomial.potentialDegree || !polynomial.actualDegree)
        output<< polynomial.coefficients[0];
    else {
        for (int i = 0; i <= polynomial.actualDegree; i++) {
            if (!i) {
                if (polynomial.coefficients[i]) {
                    output << polynomial.coefficients[i];
                    monomPrints++;
                }
                else {
                    output << '0';
                    monomPrints++;
                }
            }
            else if (polynomial.coefficients[i] >= 0 && monomPrints) {
                output << "+(" << polynomial.coefficients[i] << ")*X^" << i;
                monomPrints++;
            }
            else {
                output << "-(" << polynomial.coefficients[i]*(-1) << ")*X^" << i;
                monomPrints++;
            }
        }
        if (!monomPrints)
            output << 0;
    }
    output << endl;
    return output;
}
