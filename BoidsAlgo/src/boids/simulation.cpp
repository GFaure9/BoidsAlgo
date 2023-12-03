#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "boids.h"
#include "rules.h"
#include "vector3d.h"


void Boids::simulate()
{
	Vector3d v_separation(0.0, 0.0, 0.0);
	Vector3d v_cohesion(0.0, 0.0, 0.0);
	Vector3d v_alignment(0.0, 0.0, 0.0);

	for (int i = 0; i < n; ++i)
	{
		v_separation = rules::computeSeparationVector(i, positions) * separation_coef;
		v_cohesion = rules::computeCohesionVector(i, positions, cohesion_dist) * cohesion_coef;
		v_alignment = rules::computeAlignmentVector(i, velocities) * alignment_coef;

		// confine inside 2*2*2 cube faces
		double v[3] = { 0.0, 0.0, 0.0 };
		Vector3d curr_pos = positions[i];
		double p[3] = { curr_pos.x, curr_pos.y, curr_pos.z };
		for (int j = 0; j < 3; ++j) {
			if (p[j] > 2)
			{
				v[j] -= 0.005;
			};
			if (p[j] < -2)
			{
				v[j] += 0.005;
			};
		};
		Vector3d v_confinment(v[0], v[1], v[2]);

		auto it = std::next(velocities.begin(), i);
		*it = *it + v_separation + v_cohesion + v_alignment + v_confinment;

		auto it2 = std::next(positions.begin(), i);
		*it2 = *it2 + velocities[i];
	};
};

void writeVectorsToFile(const std::vector<Vector3d>& vecs, const std::string& fname) {
	std::ofstream outFile(fname, std::ios::app); // Open file in append mode

	if (!outFile.is_open()) {
		std::cerr << "Error opening file: " << fname << std::endl;
		return;
	}

	for (const auto& vec : vecs) {
		outFile << vec.x << " " << vec.y << " " << vec.z << " ";
	}

	outFile << std::endl; // Move to next line for next time step
	outFile.close();
}

void Boids::run()
{
	int n_t = static_cast<int>(max_t / dt);

	for (int i = 0; i < n_t; ++i)
	{
		if (i % sampling_period == 0)
		{
			double time = i * dt;
			writeVectorsToFile(positions, fname_positions);
			//std::cout << "...written time: " << time << std::endl;
		}

		simulate();
	};
};