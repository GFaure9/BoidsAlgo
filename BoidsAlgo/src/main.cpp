#include <iostream>
#include <string>
#include "vector3d.h"
#include "boids.h"


int main(int argc, char* argv[])
{
	// Retrieving input values (n, max_t, dt, fname_positions, fname_velocities) for Boids instance

	// Verify the number of passed arguments (must be 9)
	if (argc != 10) // we include program's name in the arguments (=> 10 and not 9 args)
	{
		std::cerr << "Usage: " << argv[0] << "\nValueError: you must provide the following arguments:" << std::endl;
		std::cout << "n_boids (int) maximal_time (double) time_step (double) samples_period (int)" << std::endl;
		std::cout << "separation_coefficient (double) cohesion_coefficient (double) alignment_coefficient (double) cohesion_distance (double)" << std::endl;
		std::cout << "positions_filepath (str)" << std::endl;
		return 1; // indicates an error
	}

	// Parsing the arguments
	int n_boids = std::atoi(argv[1]); // convert to int
	double maximal_time = std::atof(argv[2]); // convert to double
	double time_step = std::atof(argv[3]);
	int samples_period = std::atoi(argv[4]);
	double cohesion_coefficient = std::atof(argv[5]);
	double separation_coefficient = std::atof(argv[6]);
	double alignment_coefficient = std::atof(argv[7]);
	double separation_distance = std::atof(argv[8]);
	std::string positions_filename = argv[9]; // string type

	// Instantiate Boids
	Boids boids(
		n_boids, maximal_time, time_step, samples_period,
		cohesion_coefficient, separation_coefficient, alignment_coefficient,
		separation_distance,
		positions_filename
	);
	std::cout << "|INFO| Starting a simulation with:" << std::endl;
	std::cout << "		* Number of boids = " << n_boids << std::endl;
	std::cout << "		* Maximum time = " << maximal_time << std::endl;
	std::cout << "		* Time step = " << time_step << std::endl;
	std::cout << "		* Separation coefficient = " << separation_coefficient << std::endl;
	std::cout << "		* Cohesion coefficient = " << cohesion_coefficient << std::endl;
	std::cout << "		* Alignment coefficient = " << alignment_coefficient << std::endl;
	std::cout << "		* Separation distance = " << separation_distance << std::endl;
	int n_samples = static_cast<int>(maximal_time / time_step / samples_period);
	std::cout << "		* Number of samples = " << n_samples << "\n" << std::endl;


	// Initialize the simulation
	boids.initSim();

	// Run the simulation
	boids.run();
	std::cout << "\n|INFO| Finished running simulation!" << std::endl;
	std::cout << "|INFO| Boids positions stored at: " << positions_filename << std::endl;
};