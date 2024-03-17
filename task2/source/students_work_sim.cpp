#include "students_work_sim.hpp"

#include <random>

void StudentsWorkSim::fillStudents(size_t studentsNum, double goodStudentProb, double badStudentProb)
{
    clipProbValues(goodStudentProb, badStudentProb);

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    for (size_t i = 0; i < studentsNum; i++) {
        double generatedVal = dist(generator);

        if (generatedVal <= goodStudentProb) {
            students.emplace_back(new GoodStudent());
        }
        else if (generatedVal <= goodStudentProb + badStudentProb) {
            students.emplace_back(new BadStudent());
        }
        else {
            students.emplace_back(new MidStudent());
        }
    }

}

void StudentsWorkSim::clipProbValues(double& prob1, double& prob2)
{
    if (prob1 > 1.0) {
        prob1 = 1.0;
    }
    if (prob2 > 1.0) {
        prob2 = 1.0;
    }
    if (prob1 + prob2 > 1.0) {
        prob2 = 1.0 - prob1;
    }
}

void StudentsWorkSim::simulateSolvings(size_t studentsNum, double goodStudentProb, double badStudentProb)
{
    fillStudents(studentsNum, goodStudentProb, badStudentProb);

    for (auto& student : students) {
        student->solveEquations();
    }
}
