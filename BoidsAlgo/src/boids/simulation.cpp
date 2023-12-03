#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "boids.h"
#include "rules.h"
#include "vector3d.h"


// Method to update positions of all boids to go from t to t + dt
// applying the cohesion, the separation and the alignment rules
void Boids::simulate()
{
	Vector3d v_cohesion(0.0, 0.0, 0.0);
	Vector3d v_separation(0.0, 0.0, 0.0);
	Vector3d v_alignment(0.0, 0.0, 0.0);

	for (int i = 0; i < n; ++i)
	{	
		// Compute the velocities to add to current i-th boid velocity to update its
		// position taking into accoung cohesion, separation and alignement

		// Steer to move towards the average position (center of mass) of local flockmates
		// "Boids try to fly towards the centre of mass of neighbouring boids"
		v_cohesion = rules::computeCohesionOrAlignmentVector(i, positions) * cohesion_coef;

		// Steer to avoid crowding local flockmates
		// "Boids try to keep a small distance away from other boids"
		v_separation = rules::computeSeparationVector(i, positions, separation_dist) * separation_coef;
		
		// Steer towards the average heading of local flockmates
		// "Boids try to match velocity with near boids"
		v_alignment = rules::computeCohesionOrAlignmentVector(i, velocities) * alignment_coef;

		// Confine inside 2*2*2 cube faces
		double v[3] = { 0.0, 0.0, 0.0 };
		Vector3d curr_pos = positions[i];
		double p[3] = { curr_pos.x, curr_pos.y, curr_pos.z };
		for (int j = 0; j < 3; ++j) {
			if (p[j] > 2)  // If a boid goes beyond a cube boundary
			{
				v[j] -= 0.005;  // Add small velocity to go in the opposite direction
			};
			if (p[j] < -2)
			{
				v[j] += 0.005;
			};
		};
		Vector3d v_confinment(v[0], v[1], v[2]);

		auto it = std::next(velocities.begin(), i);
		// Update velocity adding "incentives" velocities to respect rules
		*it = *it + v_cohesion + v_separation + v_alignment + v_confinment;

		auto it2 = std::next(positions.begin(), i);
		// Update position: X(t + dt) = X(t) + V(t) * dt
		*it2 = *it2 + velocities[i] * dt;
	};
};

// Function to write a vector<Vector3d> `vecs` object to a txt file
// Each line the file will be of the form
//				v0x v0y v0z v1x v1y v1z ... vNx vNy vNz
void writeVectorsToFile(const std::vector<Vector3d>& vecs, const std::string& fname) {
	std::ofstream outFile(fname, std::ios::app); // Open file in append mode

	if (!outFile.is_open()) {
		std::cerr << "Error opening file: " << fname << std::endl;
		return;
	}  // Make sure that the file is not already opened (if it is the case, returns an error)

	for (const auto& vec : vecs) {
		outFile << vec.x << " " << vec.y << " " << vec.z << " ";
	}

	outFile << std::endl; // Move to next line for next time step
	outFile.close();
}

// Method that runs boids flying simulations until time reaches `max_t`
// At each time step the positions vectors of all boids are added to the file `fname_positions` 
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