#include <iostream>
#include "tools.h"

using Eigen::VectorXd;
using Eigen::MatrixXd;
using std::vector;

Tools::Tools() {}

Tools::~Tools() {}

VectorXd Tools::CalculateRMSE(const vector<VectorXd> &estimations,
                              const vector<VectorXd> &ground_truth) 
{

	// Initialize
	VectorXd rmse(4);
	rmse << 0.0, 0.0, 0.0, 0.0;

	// Check:
	// * the estimation vector size should not be zero
	// * the estimation vector size should equal ground truth vector size
	if (estimations.size() != ground_truth.size() || estimations.size() == 0)
	{
		cout << "Invalid estimation or ground_truth data" << endl;
		return rmse;
	}
	// Accumulate squared residuals:
	for (unsigned int i = 0; i < estimations.size(); ++i)
	{
		VectorXd residual = estimations[i] - ground_truth[i];

		//coefficient-wise multiplication
		residual = residual.array() * residual.array();
		rmse += residual;
	}

	// Calculate the mean
	rmse = rmse / estimations.size();

	// Calculate the sqaured root
	rmse = rmse.array().sqrt();

	// Return the result
	return rmse;
}
