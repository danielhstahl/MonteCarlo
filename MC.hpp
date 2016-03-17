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
    error=(error/(double)m-estimate*estimate)/(double)(m-1);
    error=sqrt(error);
}
template<typename Number>
template<typename FN>
void MC<Number>::simulateDistribution(FN&& fn) {
    estimate=fn();
    error=estimate*estimate;
    distribution=std::vector<Number>(m);
    distribution[0]=estimate;
    #pragma omp parallel//multithread using openmp
        {
        #pragma omp for //multithread using openmp
            for(int j=1; j<m; j++){
                distribution[j]=fn();
                estimate+=distribution[j];
                error+=distribution[j]*distribution[j];
            }
        }
    estimate=estimate/(double)m;
    error=(error/(double)m-estimate*estimate)/(double)(m-1);
    error=sqrt(error);
}
template<typename Number>
template<typename FN>
void MC<Number>::simulateDistribution(FN&& fn, auto& ws) {
    estimate=fn();
    error=estimate*estimate;
    int percComplete=1;
    int modulo=(int)(m*.05);
    distribution=std::vector<Number>(m);
    distribution[0]=estimate;
    std::stringstream wsMessage;

    #pragma omp parallel//multithread using openmp
        {
        #pragma omp for //multithread using openmp
            for(int j=1; j<m; j++){
                distribution[j]=fn();
                estimate+=distribution[j];
                error+=distribution[j]*distribution[j];
                percComplete++;
                //std::cout<<percComplete<<", "<<modulo<<std::endl;
                if(percComplete % modulo==0){
                  wsMessage<<"{\"percent\": "; //to send to node
                  wsMessage<<((double)percComplete)/m<<"}";
                  ws(wsMessage.str());
                  wsMessage.str(std::string());
                }
            }
        }
    estimate=estimate/(double)m;
    error=(error/(double)m-estimate*estimate)/(double)(m-1);
    error=sqrt(error);
}
