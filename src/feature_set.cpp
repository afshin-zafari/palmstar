#include "feature_set.hpp"
FeatureSet::FeatureSet(int n, int bytes_per_feature)
{
    no_of_features  = n;
    FeatureValues = new FeatureArray (n);
    for(int i=0; i < n; i++)
    {
        FeatureValues->at(i) = new OneFeature(bytes_per_feature);
    }
}
OneFeature *FeatureSet::get_feature(int i)
{
    return FeatureValues->at(i);
}
void FeatureSet::set_feature(int i,OneFeature *fs)
{
    FeatureValues->at(i) = fs;
}
void FeatureSet::PopulateRandom()
{
    for( auto f : *FeatureValues)
    {        
        f->PopulateRandom();
    }
}
void FeatureSet::TweakBits(int bits_distance_per_feature)
{
    for( auto f : *FeatureValues)
        f->TweakBits(bits_distance_per_feature);
}
int FeatureSet::CopyTo(FeatureSetPtr fs_dest)
{
    if (fs_dest->no_of_features < this->no_of_features)
        return -1;
    for(int i=0; i<no_of_features; i++)
        fs_dest->set_feature(i,get_feature(i));
    return 0;
}
std::string  FeatureSet::to_string()
{
    std::string result;
    for( auto f: *FeatureValues)
    {
        auto one_f_str = f->to_string();
        result += one_f_str + ",";
    }
    return result.replace(result.size()-1,1," ");
}