#ifndef CPP_FRACTION_HPP
#define CPP_FRACTION_HPP

#include <string>

class Fraction
{
public:
	explicit Fraction(std::string const& str_fraction) = delete;

private:
	int numerator;
	int denominator;
};

#endif