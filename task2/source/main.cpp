#include "students_work_sim.hpp"
#include "teacher.hpp"


int main() {
	Teacher teacher;
	StudentsWorkSim studentsWorkSim;

	studentsWorkSim.simulateSolvings(10, 0.4, 0.3);

	return 0;
}