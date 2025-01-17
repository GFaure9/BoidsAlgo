#include <vector>
#include <vector3d.h>

#ifndef RULES_H
#define RULES_H

namespace rules
{
	Vector3d perceivedCenter(int vec_id, std::vector<Vector3d> vecs);
	double norm(Vector3d vec);
	Vector3d computeCohesionOrAlignmentVector(int vec_id, std::vector<Vector3d> vecs);
	Vector3d computeSeparationVector(int vec_id, std::vector<Vector3d> vecs, double separation_dist);
}

#endif
