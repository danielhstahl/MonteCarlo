#ifndef __MC_H_INCLUDED__
#define __MC_H_INCLUDED__
#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include <algorithm>
class MC {
	private:
        int m;
		auto estimate;
		auto error;
        std::vector<double> distribution;
	public:
		MC(int);
		auto getEstimate();
		auto getError();
		auto getVaR(double);
        std::vector<double> getDistribution();
		template<typename FN>
		void simulate(FN&& fn);
        template<typename FN>
		void simulateDistribution(FN&& fn);
};
#include "MC.hpp"
#endif
 
