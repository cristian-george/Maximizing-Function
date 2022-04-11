#include "Individual.h"

void Individual::Codification(double x, double y)
{
	Chromosome.X = x;
	Chromosome.Y = y;
}

double Individual::Fitness()
{
	double x = Chromosome.X.Value;
	double y = Chromosome.Y.Value;

	//return fabs(x + y);
	return fabs(10 * pow(x, 2) * y - 5 * pow(x, 2) - 4 * pow(y, 2) - pow(x, 4) - 2 * pow(y, 4)) / 2 + 1;
	//return pow(sin(x + y), 2) + pow(cos(x - y), 2);
	//return fabs(pow(x, 2) + pow(y, 2) - 10) + 1;
}

std::ostream& operator<<(std::ostream& out, const Individual& individual)
{
	out << individual.Chromosome;
	return out;
}
