#include <random>
#include <string>
#include "boids.h"
#include "vector3d.h"


// Constructor to initialize an instance of Boids class
Boids::Boids(
    int n, double max_t, double dt, int sampling_period,
    double cohesion_coef, double separation_coef, double alignment_coef,
    double separation_dist,
    std::string fname_positions
    ) :
    n(n), max_t(max_t), dt(dt), sampling_period(sampling_period),
    cohesion_coef(cohesion_coef), separation_coef(separation_coef), alignment_coef(alignment_coef),
    separation_dist(separation_dist),
    fname_positions(fname_positions)
{
};

// Function to retrurn a random double type number between 0.0 and 1.0
double randomDouble()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0.0, 1.0);
    return dis(gen);
};

// Method to initialize a simulation of boids
// All boids positions are randomly chosen in a unit cube
// All boids velocities are set to -0.01 u_x + 0.01 u_y
void Boids::initSim()
{
    // initialize positions with random reals between 0.0 and 1.0
    // and initialize velocities to (0.01, -0.01, 0.0)
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
