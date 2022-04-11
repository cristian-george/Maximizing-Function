#pragma once
#include <iostream>
#include <vector>
#include <random>
#include "Individual.h"

const size_t POPULATION_SIZE = 100;
const double CROSSOVER_PROBABILITY = 0.5;
const double MUTATION_PROBABILITY = 0.01;

const std::pair<double, double> DOMAIN_X = { -20, 20 };
const std::pair<double, double> DOMAIN_Y = { -5, 5 };

#define inf first
#define sup second

class Population
{
public:
	Population();

	void SeedPopulation();
	void Selection();
	void Crossover();
	void Mutation();

	Individual GetBestIndividual();

private:
	/* Selection helper methods */
	std::vector<double> FitnessValues();
	double				TotalSum(const std::vector<double>& fitness);
	std::vector<double> RouletteWheel();
	void				TheActualSelection(const std::vector<double>& cummulativeProbabilities, const std::vector<double>& roulette);

	/* Crossover helper methods */
	std::vector<double> CrossoverProbabilities();
	std::vector<size_t> CrossoverSelection(const std::vector<double>& crossover);
	void				TheActualCrossover(const std::vector<size_t>& selectedIndividuals);

	/* Mutation helper methods */
	std::vector<double> MutationProbabilities();
	std::vector<size_t> MutationSelection(const std::vector<double>& mutation);
	void				ModifyGenes(const std::vector<size_t>& selectedIndividuals);

public:
	std::vector<Individual> Individuals;
};
