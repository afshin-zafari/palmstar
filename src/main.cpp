#include "main.hpp"

int main()
{ 
    LogStart();
    UnitTests::ExactMatch::test_exact_equality();
    UnitTests::FeatureBasics::CreateFeatures();
    UnitTests::FeatureBasics::CreateFeaturesIntArray();
    UnitTests::DatabaseTests::CreateRandomDB();
    UnitTests::DatabaseTests::BruteForcePerformanceTest();
    UnitTests::DatabaseTests::BruteForcePerformanceTest2();
    UnitTests::DatabaseTests::TestMatrixCompare();
    LogFinish();
}