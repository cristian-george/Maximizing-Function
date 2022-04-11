#pragma once
#include "Population.h"

class GeneticAlgorithm
{
public:
	static void Start(size_t maxGeneration);

private:
	static Population population;
};

