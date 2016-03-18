#ifndef __HANDLEPATH_H_INCLUDED__
#define __HANDLEPATH_H_INCLUDED__
#include "Date.h"
#include "CurveFeatures.h"
#include <unordered_map>
#include <vector>

template<typename riskFactor>
auto executePortfolio(
    std::vector<AssetFeatures>&, //portfolio
    Date&, //as of date
    const auto&, //factor generator (function)
    const riskFactor&, //initial value of risk factor
    const std::vector<Date>&, //date paths
    const auto& //pricing engine
);

template<typename riskFactor>
std::unordered_map<Date, riskFactor> getPath(
    std::vector<Date>&, //date paths
    Date&, //as of date
    const auto&, //factor generator (function)
    const riskFactor& //initial value of risk factor

);
//template<typename maturity>
std::vector<Date> getUniquePath(
    std::vector<AssetFeatures>&, //portfolio
    Date& //maturity of the portfolio
);
#include "HandlePath.hpp"
#endif
