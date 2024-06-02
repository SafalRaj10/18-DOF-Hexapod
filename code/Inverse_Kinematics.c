#include <iostream>
#include <cmath>
#include <Eigen/Dense>
#include <unsupported/Eigen/NonLinearOptimization>

using namespace Eigen;
using namespace std;

// Function representing the system of equations
struct EqFunction
{
    const double c1, c2, c3, n1, n2;

    EqFunction(double c1, double c2, double c3, double n1, double n2)
        : c1(c1), c2(c2), c3(c3), n1(n1), n2(n2)
    {}

    int operator()(const Vector2d &vars, Vector2d &residual) const
    {
        double theta = vars(0);
        double alpha = vars(1);

        residual(0) = c1 + c2 * cos(theta) + c3 * cos(theta + alpha) - n1;
        residual(1) = -c2 * sin(theta) + c3 * sin(theta + alpha) - n2;

        return 0;
    }
};

int main()
{
    // Given coefficients and constants
    double c1 = 1;
    double c2 = 2;
    double c3 = 3;
    double n1 = 4;
    double n2 = 5;

    // Initial guess for theta and alpha
    Vector2d initial_guess(0, 0);

    // Solve the system of equations numerically
    LevenbergMarquardt<EqFunction, double> lm(EqFunction(c1, c2, c3, n1, n2));
    lm.minimize(initial_guess);

    // Extract the results for theta and alpha
    double theta_solution = initial_guess(0);
    double alpha_solution = initial_guess(1);

    // Print the results
    cout << "Theta: " << theta_solution << " radians" << endl;
    cout << "Alpha: " << alpha_solution << " radians" << endl;

    return 0;
}
