#include "GeneticAlgorithm.h"

Population GeneticAlgorithm::population;

void GeneticAlgorithm::Start(size_t maxGeneration)
{
	int generation = 0;
	population.SeedPopulation();

	while (generation < maxGeneration)
	{
		population.Selection();
		population.Crossover();
		population.Mutation();

		++generation;
	}

	Individual bestIndividual = population.GetBestIndividual();
	std::cout << "Solution: " << bestIndividual << std::endl;
	std::cout << "Maximum: " << bestIndividual.Fitness() << std::endl;
}