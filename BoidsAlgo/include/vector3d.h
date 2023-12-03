#ifndef VECTOR3D_H
#define VECTOR3D_H

class Vector3d 
{
public:
	double x, y, z;

	Vector3d(double x, double y, double z);

	Vector3d operator+(const Vector3d& other_vec3d);
	Vector3d operator-(const Vector3d& other_vec3d);
	Vector3d operator/(const double& scalar);
	Vector3d operator*(const double& scalar);
};

#endif