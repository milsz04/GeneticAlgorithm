//
// Created by milos on 13.01.2025.
//

#ifndef CINDIVIDUAL_H
#define CINDIVIDUAL_H

#include <random>
#include <vector>

#include "CGeneticAlgorithm.h"
#include "GroupingEvaluator.h"

namespace NGroupingChallenge {

    class CIndividual {
    public:
        CIndividual();

        // Constructor that calculates fitness based on provided genes and evaluator
        CIndividual(const std::vector<int>& vGenes, CGroupingEvaluator& cEvaluator);

        double dGetFitness() const; // Get the fitness value
        const std::vector<int>& vGetGenes() const; // Get the genes
        double dGetFitness(const CGroupingEvaluator & grouping_evaluator) const;

        static std::pair<CIndividual, CIndividual> cPerformCrossover(
            const CIndividual &parent1,
            const CIndividual &parent2,
            size_t crossoverPoint, CGroupingEvaluator &evaluator);
        void vMutate(double dMutProb, int iNumGroups, std::mt19937 &cRandomEngine, CGroupingEvaluator &cEvaluator);
    private:
        std::vector<int> v_genes; // Genes representing the individual
        double d_fitness; // Fitness value of the individual
    };

} // namespace NGroupingChallenge

#endif // CINDIVIDUAL_H
