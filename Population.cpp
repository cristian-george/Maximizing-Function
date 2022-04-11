#include "Population.h"

Population::Population()
{
	Individuals.resize(POPULATION_SIZE);
}

void Population::SeedPopulation()
{
	std::random_device rd;
	std::mt19937_64 generator(rd());
	std::uniform_real_distribution<double> uniformX(DOMAIN_X.inf, DOMAIN_X.sup);
	std::uniform_real_distribution<double> uniformY(DOMAIN_Y.inf, DOMAIN_Y.sup);

	for (size_t index = 0; index < POPULATION_SIZE; ++index)
	{
		Individuals[index].Codification(uniformX(generator), uniformY(generator));
	}
}

void Population::Selection()
{
	// Compute fitness and total sum for each individual
	std::vector<double> fitness = FitnessValues();
	double				totalSum = TotalSum(fitness);

	// Probabilities of selection and cummulative probabilities of selection
	std::vector<double> p, q = { 0 };

	for (size_t index = 0; index < POPULATION_SIZE; ++index)
	{
		p.push_back(fitness[index] / totalSum);
		q.push_back(q[index] + p[index]);
	}

	// Selection based on roulette method
	std::vector<double> roulette = RouletteWheel();

	// The actual selection
	TheActualSelection(q, roulette);
}

void Population::Crossover()
{
	// Generate crossover probabilities
	std::vector<double> crossover = CrossoverProbabilities();

	// Select individuals for crossover based on CROSSOVER_PROBABILITY
	std::vector<size_t> selectedIndividuals = CrossoverSelection(crossover);

	// The actual crossover
	TheActualCrossover(selectedIndividuals);
}

void Population::Mutation()
{
	// Generate mutation probabilities
	std::vector<double> mutation = MutationProbabilities();

	// Select individuals for mutation based on MUTATION_PROBABILITY
	std::vector<size_t> selectedIndividuals = MutationSelection(mutation);

	// Modify genes for the selected individual based on gaussian distribution
	ModifyGenes(selectedIndividuals);
}

Individual Population::GetBestIndividual()
{
	double bestIndividualFitness = Individuals[0].Fitness();
	size_t best = 0;

	for (size_t index = 1; index < POPULATION_SIZE; ++index)
	{
		double individualFitness = Individuals[index].Fitness();
		if (bestIndividualFitness < individualFitness)
		{
			bestIndividualFitness = individualFitness;
			best = index;
		}
	}

	return Individuals[best];
}

std::vector<double> Population::FitnessValues()
{
	std::vector<double> fitness;
	for (size_t index = 0; index < POPULATION_SIZE; ++index)
	{
		double fitness_i = Individuals[index].Fitness();
		fitness.push_back(fitness_i);
	}

	return fitness;
}

double Population::TotalSum(const std::vector<double>& fitness)
{
	double totalSum = 0;
	for (size_t index = 0; index < POPULATION_SIZE; ++index)
	{
		double fitness_i = Individuals[index].Fitness();
		totalSum += fitness_i;
	}

	return totalSum;
}

std::vector<double> Population::RouletteWheel()
{
	std::vector<double> roulette;

	std::random_device rd;
	std::mt19937_64 generator(rd());
	std::uniform_real_distribution<double> distrib(0, 1);

	for (size_t index = 0; index < POPULATION_SIZE; ++index)
	{

		roulette.push_back(distrib(generator));
	}

	return roulette;
}

void Population::TheActualSelection(const std::vector<double>& q, const std::vector<double>& roulette)
{
	std::vector<Individual> selectedIndividuals;

	for (size_t k = 0; k < roulette.size(); ++k)
	{
		double r_k = roulette[k];
		for (size_t index = 0; index < POPULATION_SIZE + 1; ++index)
		{
			if (q[index] < r_k && r_k <= q[index + 1])
			{
				selectedIndividuals.push_back(Individuals[index]);
				break;
			}
		}
	}

	Individuals = selectedIndividuals;
}

std::vector<double> Population::CrossoverProbabilities()
{
	std::vector<double> crossover;

	std::random_device rd;
	std::mt19937_64 generator(rd());
	std::uniform_real_distribution<double> distrib(0, 1);

	for (size_t index = 0; index < POPULATION_SIZE; ++index)
	{
		crossover.push_back(distrib(generator));
	}

	return crossover;
}

std::vector<size_t> Population::CrossoverSelection(const std::vector<double>& crossover)
{
	std::vector<size_t> selectedIndividuals;

	for (size_t k = 0; k < POPULATION_SIZE; ++k)
	{
		if (crossover[k] < CROSSOVER_PROBABILITY)
		{
			selectedIndividuals.push_back(k);
		}
	}

	return selectedIndividuals;
}

void Population::TheActualCrossover(const std::vector<size_t>& selectedIndividuals)
{
	for (size_t index = 0; index < selectedIndividuals.size() / 2; ++index)
	{
		size_t parent1 = selectedIndividuals[index];
		size_t parent2 = selectedIndividuals[selectedIndividuals.size() - index - 1];

		std::swap(Individuals[parent1].Chromosome.X, Individuals[parent2].Chromosome.X);
	}
}

std::vector<double> Population::MutationProbabilities()
{
	std::vector<double> mutation;

	std::random_device rd;
	std::mt19937_64 generator(rd());
	std::uniform_real_distribution<double> uniform_distrib(0, 1);

	for (size_t index = 0; index < POPULATION_SIZE; ++index)
	{
		mutation.push_back(uniform_distrib(generator));
	}

	return mutation;
}

std::vector<size_t> Population::MutationSelection(const std::vector<double>& mutation)
{
	std::vector<size_t> selectedIndividuals;

	for (size_t k = 0; k < POPULATION_SIZE; ++k)
	{
		if (mutation[k] <= MUTATION_PROBABILITY)
		{
			selectedIndividuals.push_back(k);
		}
	}

	return selectedIndividuals;
}

void Population::ModifyGenes(const std::vector<size_t>& selectedIndividuals)
{
	std::random_device rd;
	std::mt19937_64 generator(rd());
	std::normal_distribution<double> normal_distrib(0, 1);

	for (size_t index = 0; index < selectedIndividuals.size(); ++index)
	{
		size_t k = selectedIndividuals[index];

		double x = normal_distrib(generator);
		double y = normal_distrib(generator);

		Gene geneX = Individuals[k].Chromosome.X.Value + x;
		Gene geneY = Individuals[k].Chromosome.Y.Value + y;

		if (geneX.Value < DOMAIN_X.inf)
			geneX = DOMAIN_X.inf;
		else
			if (geneX.Value > DOMAIN_X.sup)
				geneX = DOMAIN_X.sup;

		Individuals[k].Chromosome.X = geneX;

		if (geneY.Value < DOMAIN_Y.inf)
			geneY = DOMAIN_Y.inf;
		else
			if (geneY.Value > DOMAIN_Y.sup)
				geneY = DOMAIN_Y.sup;

		Individuals[k].Chromosome.Y = geneY;
	}
}
