//
// Created by milos on 13.01.2025.
//

#ifndef GENERICALGORITHM_H
#define GENERICALGORITHM_H
#include <vector>
#include <random>
#include <iostream>

#include "GroupingEvaluator.h"

#include "CIndividual.h"

namespace NGroupingChallenge {
 class CIndividual;
 class CGeneticAlgorithm {
 public:
  CGeneticAlgorithm(int iPopSize, int iNumPoints, int iNumGroups, CGroupingEvaluator& cEvaluator);

  void vInitializePopulation(); // Generate population
  void vPrintPopulation() const; // Display population with fitness
  int SelectRandomParent() ;

  std::pair<CIndividual, CIndividual> vPerformCrossover(int parent1_index, int parent2_index,double dCrossProb);
  void vMutatePopulation(double dMutProb);

  const int SelectRandomParents() const;

  void Run(int iIterations, double dCrossProb, double dMutProb);

  void vPrintBestIndividual() const;

 private:
  int i_pop_size; // Population size
  int i_num_points; // Number of points in each solution
  int i_num_groups; // Number of groups to assign points to

  std::vector<CIndividual> v_population; // Population represented as a vector of individuals
  std::mt19937 c_random_engine;; // Random number generator
  double d_best_fitness; // Best fitness value across all iterations
  std::vector<int> v_best_genes; // Genes of the individual with the best fitness
  CGroupingEvaluator& c_evaluator; // Reference to the grouping evaluator
 };

} // namespace NGroupingChallenge

#endif // GENETIC_ALGORITHM_H
// namespace NGroupingChallenge

