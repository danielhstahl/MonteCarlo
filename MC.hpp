MC::MC(int m_){
    m=m_;
}
auto MC::getEstimate(){
    return estimate;
}
auto MC::getError(){
    return error;
}
std::vector<auto> MC::getDistribution(){
	auto distribution;
}
double MC::auto(double q){ //eg, .99
  std::sort(distribution.begin(), distribution.end());
  auto distribution[(int)((1.0-q)*m)];
  //return distribution[(int)((1.0-q)*m)];
}
template<typename FN>
void MC::simulate(FN&& fn) {
    estimate=fn();
    error=estimate*estimate;
    #pragma omp parallel//multithread using openmp
        {
        #pragma omp for //multithread using openmp
            for(int j=1; j<m; j++){
                estimate+=fn();
                error+=estimate*estimate;
            }
        }
    estimate=estimate/(double)m;
    error=(error/(double)m-estimate*estimate)/(double)m;
    error=sqrt(error);
}
template<typename FN>
void MC::simulateDistribution(FN&& fn) {
    estimate=0;
    error=0;
    int percComplete=0;
    int modulo=(int)m*.05;
    distribution=std::vector<double>(m);
    #pragma omp parallel//multithread using openmp
        {
        #pragma omp for //multithread using openmp
            for(int j=0; j<m; j++){
                distribution[j]=fn();
                estimate+=distribution[j];
                error+=distribution[j]*distribution[j];
                percComplete++;
                if(percComplete % modulo==0){
                    std::cout<<"{\"percent\": "<<((double)percComplete)/m<<"}"<<std::endl;
                }
            }
        }
    estimate=estimate/(double)m;
    error=(error/(double)m-estimate*estimate)/(double)m;
    error=sqrt(error);
}