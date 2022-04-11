#pragma once
#include "Gene.h"

class Chromosome
{
public:
	Chromosome() = default;
	Chromosome(Gene x, Gene y);

	friend std::ostream& operator << (std::ostream& out, const Chromosome chromosome);

public:
	Gene X, Y;
};

