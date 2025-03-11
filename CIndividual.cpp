//
// Created by milos on 13.01.2025.
//
#include "CIndividual.h"

#include <iostream>


#include <random>
namespace NGroupingChallenge {


    CIndividual::CIndividual() : v_genes(), d_fitness(0.0) {}

    CIndividual::CIndividual(const std::vector<int>& vGenes, CGroupingEvaluator& cEvaluator)
        : v_genes(vGenes), d_fitness(cEvaluator.dEvaluate(vGenes)) {}

    double CIndividual::dGetFitness() const {
        return d_fitness;
    }

    const std::vector<int>& CIndividual::vGetGenes() const {
        return v_genes;
    }

    std::pair<CIndividual, CIndividual> CIndividual::cPerformCrossover(
        const CIndividual& parent1,
        const CIndividual& parent2,
        size_t crossoverPoint,
        CGroupingEvaluator& evaluator)
    {

        std::vector<int> child1_genes = parent1.vGetGenes();
        std::vector<int> child2_genes = parent2.vGetGenes();

        // Swap gene segments after the crossover point
        std::copy(parent2.vGetGenes().begin() + crossoverPoint, parent2.vGetGenes().end(),
                  child1_genes.begin() + crossoverPoint);
        std::copy(parent1.vGetGenes().begin() + crossoverPoint, parent1.vGetGenes().end(),
                  child2_genes.begin() + crossoverPoint);

        // Create and return two new individuals
        CIndividual child1(child1_genes, evaluator);
        CIndividual child2(child2_genes, evaluator);

        return {child1, child2};
    }

    void CIndividual::vMutate(double dMutProb, int iNumGroups, std::mt19937& cRandomEngine,CGroupingEvaluator& cEvaluator ) {
        std::uniform_real_distribution<double> c_probability_distribution(0.0, 1.0);
        std::uniform_int_distribution<int> c_group_distribution(1, iNumGroups);

        // Iterate through each gene in the individual
        for (int& gene : v_genes) {
            double random_number = c_probability_distribution(cRandomEngine);
            // Check if mutation occurs for this gene
            if (random_number < dMutProb) {
                // Mutate the gene by assigning a new random group
                gene = c_group_distribution(cRandomEngine);
                std::cout<<"Mutation: "<<gene<<std::endl;
            }
        }
        d_fitness = cEvaluator.dEvaluate(v_genes);

    }// namespace NGroupingChallenge
}
// namespace NGroupingChallenge
