#ifndef __SIMULNORM_H_INCLUDED__
#define __SIMULNORM_H_INCLUDED__
#include <random>
#include <chrono>
class SimulateNorm{
private:
  std::mt19937_64 generator;
  std::normal_distribution<double> norm;
  int seed;
public:
  SimulateNorm(){
    seed=std::chrono::system_clock::now().time_since_epoch().count();
    generator.seed(seed);
    //n=n_;
    norm=std::normal_distribution<double>(0.0, 1.0);
  }
  SimulateNorm(int seed){
    generator.seed(seed);
    //n=n_;
    norm=std::normal_distribution<double>(0.0, 1.0);
  }
  SimulateNorm(double mu, double sigma, int seed){
    generator.seed(seed);
    norm=std::normal_distribution<double>(mu, sigma);
  }
  SimulateNorm(double mu, double sigma){
    seed=std::chrono::system_clock::now().time_since_epoch().count();
    generator.seed(seed);
    norm=std::normal_distribution<double>(mu, sigma);
  }
  
  double getNorm(){
    return norm(generator); //will this work???
  }

};
#endif