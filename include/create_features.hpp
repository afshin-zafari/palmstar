#include <vector>
#include "parameters.hpp"
#include <random>

typedef std::vector<char> FeatureVector;
typedef FeatureVector *FeatureVectorPtr;
FeatureVectorPtr create_random_features(void);