#include <iostream>
#include <bitset>
#include <functional>
#include <chrono>

#include "parameters.hpp"
#include "log_manager.hpp"

typedef std::bitset<bits_per_hand> FeaturesBits;
typedef FeaturesBits *FeaturesBitPtr;


std::hash<FeaturesBits> hash_fn;

typedef size_t HandKey;
typedef std::vector<HandKey> HandKerArray;
auto now=[](){return std::chrono::steady_clock::now();};