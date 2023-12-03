#include <random>
#include <string>
#include "boids.h"
#include "vector3d.h"


Boids::Boids(
    int n, double max_t, double dt, int sampling_period,
    double separation_coef, double cohesion_coef, double alignment_coef,
    double cohesion_dist,
    std::string fname_positions
    ) :
    n(n), max_t(max_t), dt(dt), sampling_period(sampling_period),
    separation_coef(separation_coef), cohesion_coef(cohesion_coef), alignment_coef(alignment_coef),
    cohesion_dist(cohesion_dist),
    fname_positions(fname_positions)
{
};

double randomDouble()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0.0, 1.0);
    return dis(gen);
};

void Boids::initSim()
{
    // initialize positions with random reals between 0.0 and 1.0
    // and initialize velocities with zeros
    for (int i = 0; i < n; ++i)
    {
        double x = randomDouble();
        double y = randomDouble();
        double z = randomDouble();
        Vector3d rd_position(x, y, z);

        //Vector3d zero_velocity(0.0, 0.0, 0.0);
        Vector3d small_velocity(0.01, -0.01, 0.0);

        positions.push_back(rd_position);
        velocities.push_back(small_velocity);
    };
};
