//
// Created by milos on 13.01.2025.
//
#include "CGeneticAlgorithm.h"
#include "CIndividual.h"
#include <algorithm>
#include <limits>
#include <iostream>


namespace NGroupingChallenge {

CGeneticAlgorithm::CGeneticAlgorithm(int iPopSize, int iNumPoints, int iNumGroups, CGroupingEvaluator& cEvaluator)
    : i_pop_size(iPopSize), i_num_points(iNumPoints), i_num_groups(iNumGroups), c_random_engine(std::random_device{}()),
      c_evaluator(cEvaluator), d_best_fitness(std::numeric_limits<double>::max()) {

}

void CGeneticAlgorithm::vInitializePopulation() {
    std::uniform_int_distribution<int> c_group_distribution(1, i_num_groups);
    v_population.clear();

    for (int i = 0; i < i_pop_size; ++i) {
        std::vector<int> v_genes;
        for (int j = 0; j < i_num_points; ++j) {
            v_genes.push_back(c_group_distribution(c_random_engine));
        }
        v_population.emplace_back(v_genes, c_evaluator);
    }
}

void CGeneticAlgorithm::vPrintPopulation() const {
    for (size_t i = 0; i < v_population.size(); ++i) {
        const CIndividual& individual = v_population[i];
        std::cout << "Individual " << i + 1 << ": ";
        for (int gene : individual.vGetGenes()) {
            std::cout << gene;
        }
        std::cout << " (Fitness: " << individual.dGetFitness() << ")\n";
    }
}

int CGeneticAlgorithm::SelectRandomParent() {
    std::uniform_int_distribution<int> c_distribution(0, v_population.size() - 1);
    int i_random_index1 = c_distribution(c_random_engine);
    int i_random_index2 = c_distribution(c_random_engine);

    const CIndividual& cParent1 = v_population[i_random_index1];
    const CIndividual& cParent2 = v_population[i_random_index2];

    return (cParent1.dGetFitness() < cParent2.dGetFitness()) ? i_random_index1 : i_random_index2;
}

std::pair<CIndividual, CIndividual> CGeneticAlgorithm::vPerformCrossover(
    int parent1_index, int parent2_index, double dCrossProb) {
    std::uniform_real_distribution<double> c_probability_distribution(0.0, 1.0);
    if (c_probability_distribution(c_random_engine) < dCrossProb) {
        // Choose a random crossover point between 1 and n-1
        std::uniform_int_distribution<size_t> c_crossover_point_distribution(1, i_num_points - 1);
        size_t crossover_point = c_crossover_point_distribution(c_random_engine);

        return CIndividual::cPerformCrossover(
            v_population[parent1_index],
            v_population[parent2_index],
            crossover_point, c_evaluator);
    } else {
        return {v_population[parent1_index], v_population[parent2_index]};
    }
}

void CGeneticAlgorithm::Run(int iNumIterations, double dCrossProb, double dMutProb) {
    for (int iteration = 0; iteration < iNumIterations; ++iteration) {
        std::vector<CIndividual> v_new_population;

        while (v_new_population.size() < v_population.size()) {
            int parent1_index = SelectRandomParent();
            int parent2_index = SelectRandomParent();

            auto [child1, child2] = vPerformCrossover(parent1_index, parent2_index, dCrossProb);

            v_new_population.push_back(std::move(child1));
            if (v_new_population.size() < v_population.size()) {
                v_new_population.push_back(std::move(child2));
            }
        }

        v_population = std::move(v_new_population);
        vMutatePopulation(dMutProb);

        for (const CIndividual& individual : v_population) {
            if (individual.dGetFitness() < d_best_fitness) {
                d_best_fitness = individual.dGetFitness();
                v_best_genes = individual.vGetGenes();
            }
        }

        std::cout << "Iteration " << iteration + 1 << ":\n";
        vPrintPopulation();
    }
}

void CGeneticAlgorithm::vMutatePopulation(double dMutProb) {
    for (CIndividual& individual : v_population) {
        individual.vMutate(dMutProb, i_num_groups, c_random_engine, c_evaluator);
    }
}

void CGeneticAlgorithm::vPrintBestIndividual() const {
    std::cout << "Best Individual\n";
    std::cout << "Genes: ";
    for (int gene : v_best_genes) {
        std::cout << gene;
    }
    std::cout << "\nFitness: " << d_best_fitness << "\n";
}

} // name
// namespace NGroupingChallenge
