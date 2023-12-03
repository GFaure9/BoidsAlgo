#include "vector3d.h"
#include <vector>
#include <iostream>


namespace rules 
{
	Vector3d perceivedCenter(int vec_id, std::vector<Vector3d> vecs)
	{
		Vector3d pc(0.0, 0.0, 0.0);

		std::vector<Vector3d> new_vecs(vecs.begin(), std::next(vecs.begin(), vec_id));
		new_vecs.insert(new_vecs.end(), std::next(vecs.begin(), vec_id + 1), vecs.end());

		for (const Vector3d& vec : new_vecs)
		{
			pc = pc + vec;
		}
		return pc / (new_vecs.size() - 1);
	}

	double norm(Vector3d vec)
	{
		return std::sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	};

	Vector3d computeSeparationVector(int vec_id, std::vector<Vector3d> vecs)
	{
		Vector3d perceived_center = perceivedCenter(vec_id, vecs);

		for (int i = 0; i < vecs.size(); i++)
		{
			if (i != vec_id)
			{
				perceived_center = perceived_center + vecs[i];
			};
		};
		perceived_center = perceived_center / (vecs.size() - 1);

		return perceived_center - vecs[vec_id];
	};

	Vector3d computeCohesionVector(int vec_id, std::vector<Vector3d> vecs, double cohesion_dist)
	{
		Vector3d subtracted_vector(0.0, 0.0, 0.0);

		for (int i = 0; i < vecs.size(); i++)
		{
			if (i != vec_id)
			{
				if (norm(vecs[i] - vecs[vec_id]) < cohesion_dist)
				{
					subtracted_vector = subtracted_vector - (vecs[i] - vecs[vec_id]);
				};
			};
		};
		return subtracted_vector;
	};

	Vector3d computeAlignmentVector(int vec_id, std::vector<Vector3d> vecs)
	{
		Vector3d perceived_velocity = perceivedCenter(vec_id, vecs);

		for (int i = 0; i < vecs.size(); i++)
		{
			if (i != vec_id)
			{
				perceived_velocity = perceived_velocity + vecs[i];
			};
		};
		perceived_velocity = perceived_velocity / (vecs.size() - 1);

		return perceived_velocity - vecs[vec_id];
	};

	Vector3d computeEdgesVector(int vec_id, std::vector<Vector3d> vecs)
	{
		Vector3d perceived_velocity = perceivedCenter(vec_id, vecs);

		for (int i = 0; i < vecs.size(); i++)
		{
			if (i != vec_id)
			{
				perceived_velocity = perceived_velocity + vecs[i];
			};
		};
		perceived_velocity = perceived_velocity / (vecs.size() - 1);

		return perceived_velocity - vecs[vec_id];
	};
};