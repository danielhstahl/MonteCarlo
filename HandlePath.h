#ifndef __HANDLEPATH_H_INCLUDED__
#define __HANDLEPATH_H_INCLUDED__
#include "Date.h"
#include "CurveFeatures.h"
#include <vector>

template<typename maturity>
std::vector<maturity> getUniquePath(std::vector<AssetFeatures>& portfolio, maturity portfolioMaturity);


#include "HandlePath.h"
#endif