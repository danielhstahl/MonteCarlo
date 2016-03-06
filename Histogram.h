#ifndef __HISTOGRAM_H_INCLUDED__
#define __HISTOGRAM_H_INCLUDED__
#include <vector>
#include <sstream>


template<typename Number>
std::vector<int> bin(
    int, //numbins 
    const Number&, //min 
    const Number&, //max
    const std::vector<Number>& //data
);
template<typename Number>
void binAndSend(
    auto&, 
    int, //numbins
    const Number&, //min
    const Number&,  //max
    const std::vector<Number>& //data
);
template<typename Number>
void binAndSend(
    auto&, 
    Number&, //min
    Number&, //max
    const std::vector<Number>& //data
);
#include "Histogram.hpp"
#endif