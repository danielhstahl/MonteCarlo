template<typename Number>
MC<Number>::MC(int m_){
    m=m_;
}
template<typename Number>
MC<Number>::MC(){
    
}
template<typename Number>
void MC<Number>::setM(int m_){
    m=m_;
}
template<typename Number>
Number MC<Number>::getEstimate(){
    return estimate;
}
template<typename Number>
Number MC<Number>::getError(){
    return error;
}
template<typename Number>
std::vector<Number> MC<Number>::getDistribution(){
	return distribution;
}
template<typename Number>
Number MC<Number>::getVaR(double q){ //eg, .99
  std::sort(distribution.begin(), distribution.end());
  return distribution[(int)((1.0-q)*m)];
  //return distribution[(int)((1.0-q)*m)];
}
template<typename Number>
template<typename FN>
void MC<Number>::simulate(FN&& fn) {
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
template<typename Number>
template<typename FN>
void MC<Number>::simulateDistribution(FN&& fn) {
    estimate=fn();
    error=estimate*estimate;
    int percComplete=1;
    int modulo=(int)m*.05;
    distribution=std::vector<Number>(m);
    distribution[0]=estimate;
    //std::stringstream msg;
    /*std::mutex m_screen;
    auto msg=[&](const auto& perc, const auto& dist){
        //m_screen.lock();
        std::lock_guard<std::mutex> lock(m_screen);
        std::cout<<"{\"percent\": "<<perc<<", \"data\":"<<dist<<"}"<<std::endl;
        //m_screen.unlock();
    };*/
    //char buffer[50]; //should be enough...
    //msg<<"{\"percent\": "<<((double)percComplete)/m<<", \"data\":"<<estimate<<"}"<<"\n";
    //sprintf(buffer, "{\"percent\": %d, \"data\": %d}\n", ((double)percComplete)/m, estimate);
    //msg(((double)percComplete)/m, estimate);
    #pragma omp parallel//multithread using openmp
        {
        #pragma omp for //multithread using openmp
            for(int j=1; j<m; j++){
                distribution[j]=fn();
                estimate+=distribution[j];
                error+=distribution[j]*distribution[j];
                percComplete++;
                //if(percComplete % modulo==0){
                //    std::cout<<"{\"percent\": "<<((double)percComplete)/m<<"}"<<std::endl;
               // }
            }
        }
    estimate=estimate/(double)m;
    error=(error/(double)m-estimate*estimate)/(double)m;
    error=sqrt(error);
}
