#include "students.hpp"

#include <fstream>
#include <random>

bool Student::readEquations(std::vector<QuadraticEq>& equations)
{
    std::ifstream inputFile(inputFileName);

    if (!inputFile.is_open()) {
        return false;
    }

    // Coefficients of ax^2 + bx + c = 0
    double a, b, c;

    while (inputFile >> a >> b >> c) {
        equations.push_back(QuadraticEq(a, b, c));
    }

    if (!inputFile.eof()) {
        equations.clear();
        return false;
    }

    return true;
}

bool Student::writeRoots(std::vector<Roots>& allRoots)
{
    std::ofstream outputFile(outputFileName);

    if (!outputFile.is_open()) {
        return false;
    }

    for (size_t i = 0; i < allRoots.size(); i++) {
        outputFile << i + 1 << std::endl;
        outputFile << surname << std::endl;

        for (auto& root : allRoots[i]) {
            outputFile << root << " ";
        }
        outputFile << std::endl;
    }

    return true;
}

void GoodStudent::solveEquations()
{
    std::vector<QuadraticEq> equations;
    std::vector<Roots> allRoots;

    readEquations(equations);

    for (auto& equation : equations) {
        allRoots.push_back(equation.solve());
    }

    writeRoots(allRoots);
}

void MidStudent::solveEquations()
{
    std::vector<QuadraticEq> equations;
    std::vector<Roots> allRoots;

    readEquations(equations);

    std::random_device rd;
    std::mt19937 generator(rd()); 
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    for (auto& equation : equations) {
        if (dist(generator) >= 0.55) {
            allRoots.push_back(equation.solve());
        }
        else {
            allRoots.emplace_back(0);
        }
    }

    writeRoots(allRoots);
}

void BadStudent::solveEquations()
{
    std::vector<QuadraticEq> equations;
    std::vector<Roots> allRoots;

    readEquations(equations);

    for (auto& equation : equations) {
        allRoots.emplace_back(0);
    }

    writeRoots(allRoots);
}
