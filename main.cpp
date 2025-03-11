//
// Created by milos on 13.01.2025.
//
#include "CGeneticAlgorithm.h"
#include "Point.h"
#include "GroupingEvaluator.h"
#include <iostream>
#include "CIndividual.h"
#include "GaussianGroupingEvaluatorFactory.h"

int main() {
    const int popSize = 20;
    const int numberOfGroups = 9;
    const int numOfPoints =10;
    // Example setup: Create a set of points for the evaluator
    NGroupingChallenge::CGaussianGroupingEvaluatorFactory c_evaluator_factory(numberOfGroups, numOfPoints,4);

    c_evaluator_factory
        .cAddDimension(-100, 100, 1.0, 1.0)
        .cAddDimension(-100, 100, 1.0, 1.0)
        .cAddDimension(-100, 100, 1.0, 1.0)
        .cAddDimension(-100, 100, 1.0, 1.0)
    .cAddDimension(-100, 100, 1.0, 1.0)
    .cAddDimension(-100, 100, 1.0, 1.0)
    .cAddDimension(-100, 100, 1.0, 1.0)
    .cAddDimension(-100, 100, 1.0, 1.0)
    .cAddDimension(-100, 100, 1.0, 1.0)

    .cAddDimension(-100, 100, 1.0, 1.0);


    NGroupingChallenge::CGroupingEvaluator* pc_evaluator = c_evaluator_factory.pcCreateEvaluator(0);

    // Initialize Genetic Algorithm
    NGroupingChallenge::CGeneticAlgorithm geneticAlgorithm(popSize, numOfPoints, numberOfGroups, *pc_evaluator); // PopSize=4, Points=4, Groups=3

    geneticAlgorithm.vInitializePopulation();

    // Print initial population
    std::cout << "Initial Population:\n";
    geneticAlgorithm.vPrintPopulation();

    // Run the genetic algorithm for x iterations with crossover and mutation probabilities
    int iterations = 1000;
    double crossoverProbability = 0.6; // 60%
    double mutationProbability = 0.1;  // 10%

    geneticAlgorithm.Run(iterations, crossoverProbability,mutationProbability);
    geneticAlgorithm.vPrintBestIndividual();

   // return 0;
}
