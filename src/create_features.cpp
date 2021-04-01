#include "create_features.hpp"
FeatureVectorPtr create_random_features()
{
    FeatureVectorPtr fv = new FeatureVector(no_features_per_hand);
    for(int i =0; i< no_features_per_hand; i++)
    {
        fv->at(i) = std::rand() % 256;
    }
    return fv;
}
