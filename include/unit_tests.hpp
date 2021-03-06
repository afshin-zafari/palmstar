#pragma once 
#include <iostream>
#include <bitset>
#include <functional>
#include <chrono>
#include <map>
#include <cassert>

#include "parameters.hpp"
#include "log_manager.hpp"
#include "create_features.hpp"
#include "palm_features.hpp"
#include "database.hpp"
#include "profiler.hpp"
#include "json_input.hpp"
#include <random>

#define UNIT_TEST_RESULT(a)\
        LogWrite(DEBUG_LEVEL,"Test Result\t\t\t\t\t[%s]", (a) ? "PASSED" : "FAILED")

typedef std::bitset<Parameters::bits_per_hand> FeaturesBits;
typedef FeaturesBits *FeaturesBitPtr;


std::hash<FeaturesBits> hash_fn;

typedef size_t HandKey;
typedef std::vector<HandKey> HandKerArray;
auto now=[](){return std::chrono::steady_clock::now();};
namespace UnitTests{
    namespace ExactMatch{
        void test_exact_equality();
    }
    namespace FeatureBasics
    {
        void CreateFeatures();
        void CreateFeaturesIntArray();
    }
    namespace DatabaseTests
    {
        void CreateRandomDB();
        void BruteForcePerformanceTest();
        void BruteForcePerformanceTest2();
        void TestMatrixCompare();
        void LoadPersonFromJSONFile();
    }

}