#include "Gene.h"

Gene::Gene(double value) : Value(value) {}

std::ostream& operator<<(std::ostream& out, const Gene& gene)
{
	out << std::fixed << std::setw(10) << gene.Value;
	return out;
}
