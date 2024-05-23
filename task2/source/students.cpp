#include "students.hpp"

#include <fstream>
#include <random>
#include <iomanip>


int Student::surnamePosInFile = 0;


Student::Student()
{
    std::ifstream surnamesFile("surnames.txt");

    for (int i = 0; i < surnamePosInFile && !surnamesFile.eof(); i++) {
        surnamesFile.ignore(INT_MAX, '\n');
    }

    if (surnamesFile.eof()) {
        surnamesFile.seekg(0);
        surnamePosInFile = 0;
    }

    surnamesFile >> surname;

    
    surnamePosInFile++;
}


std::string const& Student::getSurname() const
{
    return surname;
}


void Student::readEquations(std::vector<QuadraticEq>& equations)
{
    std::ifstream inputFile(inputFileName);

    if (!inputFile.is_open()) {
        return;
    }

    std::string equationAsStr;
    while (!inputFile.eof()) {
        std::getline(inputFile, equationAsStr);
        if (!equationAsStr.empty()) {
            equations.push_back(QuadraticEq(equationAsStr));
        }
    }

    inputFile.close();
}


void Student::writeRoots(std::vector<QuadraticEq> &equations, std::vector<Roots>& allRoots) const
{
    std::ofstream outputFile(outputFileName, std::ofstream::app);

    if (!outputFile.is_open()) {
        return;
    }

    for (size_t i = 0; i < allRoots.size(); i++) {
        outputFile << equations[i].toString() << std::endl;
        outputFile << surname << std::endl;


        outputFile << std::setprecision(DEFAULT_PRECISION);
        switch (allRoots[i].size()) {
        case 0:
            outputFile << "N";
            break;
        case 1:
            outputFile << allRoots[i][0];
            break;
        case 2:
            outputFile << allRoots[i][0] << " " << allRoots[i][1];
            break;
        }

        outputFile << std::endl;
    }

    outputFile.close();
}


void GoodStudent::solveEquations()
{
    std::vector<QuadraticEq> equations;
    std::vector<Roots> allRoots;

    readEquations(equations);

    for (auto& equation : equations) {
        allRoots.push_back(equation.solve());
    }

    writeRoots(equations, allRoots);
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
            allRoots.push_back({ 0 });
        }
    }

    writeRoots(equations, allRoots);
}


void BadStudent::solveEquations()
{
    std::vector<QuadraticEq> equations;
    std::vector<Roots> allRoots;

    readEquations(equations);

    for (auto& equation : equations) {
        allRoots.push_back({ 0 });
    }

    writeRoots(equations, allRoots);
}
