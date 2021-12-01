#include "Fraction.hpp"

#include <algorithm>
#include <cassert>

Fraction::Fraction(std::string const& str_fraction)
{
	assert(std::find(str_fraction.begin(), str_fraction.end(), "/") != std::end(str_fraction) && "Aucun delimiteur n'a ete trouve.");
}