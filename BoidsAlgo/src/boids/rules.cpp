#include "vector3d.h"
#include <vector>
#include <iostream>


// Namespace defning different functions to update boids positions at current time step
namespace rules 
{
	// Function computing the center perceived by the boids of id `vec_id`
	// Parameters:
	//		vec_id: the id of the boid in `vecs`
	//		vecs: the list of Vector3d objects representing boids positions at current time
	Vector3d perceivedCenter(int vec_id, std::vector<Vector3d> vecs)
	{
		Vector3d pc(0.0, 0.0, 0.0);

		std::vector<Vector3d> new_vecs(vecs.begin(), std::next(vecs.begin(), vec_id));
		// `new_vecs` is `vecs` without its `vec_id`-th element
		new_vecs.insert(new_vecs.end(), std::next(vecs.begin(), vec_id + 1), vecs.end());

		for (const Vector3d& vec : new_vecs)
		{
			pc = pc + vec;
		}
		return pc / (new_vecs.size() - 1);  // Sum{ vecs[i] if i != vec_id } / ( N - 1 )
	}

	// Function computing the L2 norm of a Vector3d object
	double norm(Vector3d vec)
	{
		return std::sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	};

	// Function used to compute either the "cohesion velocity vector" or 
	// the "alignment velocity vector" added to boid current velocity to
	// respect either the Cohesion rule or the Alignment rule of birds' flocking behaviour
	// Parameters:
	//		vec_id: the id of the boid in `vecs`
	//		vecs: 
	//			- if used for Cohesion: list of Vector3d representing boids positions at current time
	//			- if used for Alignement: list of Vector3d representing boids velocities at current time
	Vector3d computeCohesionOrAlignmentVector(int vec_id, std::vector<Vector3d> vecs)
	{
		Vector3d perceived_vector = perceivedCenter(vec_id, vecs);

		// Direction from vec[vec_id] to perceived vector
		return perceived_vector - vecs[vec_id];
	};

	// Function used to compute the "separation velocity vector" added to 
	// boid current velocity to respect the Separation rule of birds' flocking behaviour
	// Parameters:
	//		vec_id: the id of the boid in `vecs`
	//		vecs: the list of Vector3d objects representing boids positions at current time
	//		cohesion_dis: the distance under which
	Vector3d computeSeparationVector(int vec_id, std::vector<Vector3d> vecs, double separation_dist)
	{
		Vector3d subtracted_vector(0.0, 0.0, 0.0);

		for (int i = 0; i < vecs.size(); i++)
		{
			if (i != vec_id)
			{
				if (norm(vecs[i] - vecs[vec_id]) < separation_dist)  // If too close to i-th boid
				{
					// Make the boid go in the opposite direction from the i-th boid
					// to maintain a distance from it
					subtracted_vector = subtracted_vector - (vecs[i] - vecs[vec_id]);
				};
			};
		};
		return subtracted_vector;
	};
};