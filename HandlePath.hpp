std::vector<Date> getUniquePath(std::vector<AssetFeatures>& portfolio, Date& portfolioMaturity){ //
    auto comparePortfolioByDate=[](const AssetFeatures& asset1, const AssetFeatures& asset2){
        return asset1.Maturity<asset2.Maturity;
    };
    std::sort(portfolio.begin(), portfolio.end(), comparePortfolioByDate); //a happy byproduct is that portfolio is now sorted by date
    int n=portfolio.size();
    int i=0;
    std::vector<Date> datePaths;
    while(portfolio[i].Maturity<portfolioMaturity){//select distinct maturity that is less than desired portfolio simulation date
        if(datePaths.back()!=portfolio[i].Maturity){
            datePaths.push_back(portfolio[i].Maturity); //
        }
    }
    datePaths.push_back(portfolioMaturity); //last maturity is the maturity date of the portfolio.
    return datePaths;
}
template<typename riskFactor>
std::unordered_map<std::time_t, riskFactor> getPath(const std::vector<Date>& datePaths, Date& asOfDate, const auto& riskFactorGenerator, const riskFactor& initialRiskFactorValue){ //AsofDate is typically the current date, but is used in cases where the program may run overnight (causing "currdate" to return two different dates).
    int n=datePaths.size();
    std::unordered_map<std::time_t, riskFactor> vals;
    vals[datePaths[0].getPrimitive()]=riskFactorGenerator(initialRiskFactorValue, datePaths[0]-asOfDate);
    for(int i=1; i<n; ++i){
        vals[datePaths[i].getPrimitive()]=riskFactorGenerator(vals[datePaths[i-1].getPrimitive()], datePaths[i]-datePaths[i-1]);
    }
    return vals;
}
template<typename riskFactor>
auto executePortfolio( std::vector<AssetFeatures>& portfolio, Date& asOfDate, const auto& riskFactorGenerator, const riskFactor& initialRiskFactorValue, const std::vector<Date>& datePaths, const auto& pricingEngine){ //to be called after getUniquePath.  AsofDate is typically the current date, but is used in cases where the program may run overnight (causing "currdate" to return two different dates).
    std::unordered_map<std::time_t, riskFactor> riskPath=getPath(datePaths, asOfDate, riskFactorGenerator, initialRiskFactorValue);
    int n=portfolio.size();
    Date dt=datePaths.back();
    if(riskPath.find(portfolio[0].Maturity.getPrimitive())!=riskPath.end()){ //if maturity is less than portfolio maturity
        dt=portfolio[0].Maturity;
    }
    auto val=riskPath.find(dt.getPrimitive())->second;
    auto portVal=pricingEngine(portfolio[0], val, dt, asOfDate);
    for(int i=1; i<n;++i){
        if(riskPath.find(portfolio[i].Maturity.getPrimitive())!=riskPath.end()){ //if maturity is less than portfolio maturity
            val=riskPath.find(portfolio[i].Maturity.getPrimitive())->second;
            portVal+=pricingEngine(portfolio[i], val, portfolio[i].Maturity, asOfDate);
        }
        else{
            dt=datePaths.back();
            val=riskPath.find(dt.getPrimitive())->second;
            portVal+=pricingEngine(portfolio[i], val, dt, asOfDate);
        }
    }
    return portVal;
}
