template<typename maturity>
std::vector<maturity> getUniquePath(std::vector<AssetFeatures>& portfolio, maturity portfolioMaturity){ //havent decided if portfolioMaturity is number of days or a date.  
    auto comparePortfolioByDate=[](const AssetFeatures1&, const AssetFeatures2&){
        return AssetFeatures1.Maturity<AssetFeatures2.Maturity;
    }
    std::sort(portfolio.begin(), portfolio.end(), comparePortfolioByDate); //a happy byproduct is that portfolio is now sorted by date
    int n=portfolio.size();
    int i=0;
    std::vector<maturity> datePaths;
    while(portfolio[i].Maturity<portfolioMaturity){//select distinct maturity that is less than desired portfolio simulation date
        if(datePaths.back()!=portfolio[i].Maturity){
            datePaths.push_back(portfolio[i].Maturity); //
        }   
    }
    datePaths.push_back(portfolioMaturity); //last maturity is the maturity date of the portfolio.
    return datePaths;
}
template<typename maturity, typename riskFactor>
std::unordered_map<maturity, riskFactor> getRatePath(std::vector<maturity>& datePaths, maturity& asOfDate, const auto& riskFactorGenerator, const riskFactor& initialRiskFactorValue){ //AsofDate is typically the current date, but is used in cases where the program may run overnight (causing "currdate" to return two different dates).
    int n=datePaths.size();
    std::unordered_map<maturity, riskFactor> vals;
    vals[datePaths[0]]=riskFactorGenerator(initialRiskFactorValue, datePaths[0]-asOfDate);
    for(int i=1; i<n; ++i){
        vals[datePaths[i]]=riskFactorGenerator(vals[datePaths[i-1]], datePaths[i]-asOfDate);
    }
    return vals;
}

template<typename maturity, typename riskFactor>
void executePortfolio( std::vector<AssetFeatures>& portfolio, maturity& asOfDate, const auto& riskFactorGenerator, const riskFactor initialRiskFactorValue){ //to be called after getUniquePath.  AsofDate is typically the current date, but is used in cases where the program may run overnight (causing "currdate" to return two different dates).
    std::unordered_map<maturity, riskFactor> riskPath=getRatePath(datePaths, asOfDate, riskFactorGenerator, initialRiskFactorValue);
    
    int n=portfolio.size();
    riskFactor portVal=
    for(int i=1; i<n;++i){
        
    }
}