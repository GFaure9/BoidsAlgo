#include <vector>
#include <string>
#include "vector3d.h"

#ifndef BOIDS_H
#define BOIDS_H


class Boids
{
public:
	int n;
	double max_t;
	double dt;
	int sampling_period;
	double separation_coef;
	double cohesion_coef;
	double alignment_coef;
	double cohesion_dist;
	std::vector<Vector3d> positions;
	std::vector<Vector3d> velocities;
	std::string fname_positions;

	Boids(
		int n, double max_t, double dt, int sampling_period,
		double separation_coef, double cohesion_coef, double alignment_coef,
		double cohesion_dist,
		std::string fname_positions
	);

	void initSim();
	void simulate();
	void terminateSim();
	void run();
};

#endif