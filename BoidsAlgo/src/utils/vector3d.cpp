#include "vector3d.h"
#include <iostream>


Vector3d::Vector3d(double x, double y, double z) : x(x), y(y), z(z) {};

Vector3d Vector3d::operator+(const Vector3d& other_vector)
{
    return Vector3d(x + other_vector.x, y + other_vector.y, z + other_vector.z);
};

Vector3d Vector3d::operator-(const Vector3d& other_vector)
{
    return Vector3d(x - other_vector.x, y - other_vector.y, z - other_vector.z);
};

Vector3d Vector3d::operator/(const double& scalar)
{
    if (scalar != 0.0) 
    {
        return Vector3d(x / scalar, y / scalar, z / scalar);
    }
    else 
    {
        std::cerr << "Error: division by zero" << std::endl;
        return *this;  // returning initial vector as default
    };
};

Vector3d Vector3d::operator*(const double& scalar)
{
    return Vector3d(scalar * x, scalar * y, scalar * z);
};