#pragma once
#include <cmath>
#include "Chromosome.h"

class Individual
{
public:
	void Codification(double x = 0, double y = 0);
	double Fitness();

	friend std::ostream& operator << (std::ostream& out, const Individual& individual);

public:
	Chromosome Chromosome;
};