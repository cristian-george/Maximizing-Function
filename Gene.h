#pragma once
#include <ostream>
#include <iomanip>

class Gene
{
public:
	Gene(double value = 0);

	friend std::ostream& operator << (std::ostream& out, const Gene& gene);

public:
	double Value;
};

