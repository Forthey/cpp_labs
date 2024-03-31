#pragma once
#include "students_work_sim.hpp"
#include "teacher.hpp"



class ConsoleUserInterface {
	using CommandFunc = void(*)();
	using CommandRunner = std::map<std::string, CommandFunc>;


	static std::unique_ptr<Teacher> teacher;
	static std::unique_ptr<StudentsWorkSim> studentsWorkSim;
	static CommandRunner commandRunner;


	static void exitSim();

	static void generateEquations();

	static void printGrades();

	static void solveEquations();

	static void checkSolutions();

	static void resetInOutFiles();

	static void printMenu();

	static void startSimulation();

public:
	static void startInteration();
};