#include "Chromosome.h"

Chromosome::Chromosome(Gene x, Gene y) : X(x), Y(y) {}

std::ostream& operator<<(std::ostream& out, const Chromosome chromosome)
{
	out << chromosome.X << ' ' << chromosome.Y;
	return out;
}
