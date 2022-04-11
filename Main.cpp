#include "GeneticAlgorithm.h"

int main()
{
	size_t maxGeneration;
	std::cout << "Number of generations: ";
	std::cin >> maxGeneration;

	GeneticAlgorithm::Start(maxGeneration);

	return 0;
}