
#pragma once
#include <vector>
#include <string>
typedef unsigned char byte;
typedef std::vector<byte> ByteVector;
typedef ByteVector *ByteVectorPtr;
class OneFeature
{
    public:
    int no_of_bytes ;
    int id;
    ByteVectorPtr Bytes;
    void set_value(std::string);
    OneFeature();
    OneFeature(std::string);
    std::string to_string();
};
typedef std::vector<OneFeature> FeatureArray;
typedef FeatureArray *FeatureArrayPtr;
class FeatureSet
{
    public:
    int no_of_features ;
    FeatureArrayPtr Set;
    FeatureSet();
    std::string to_string();

};
typedef FeatureSet *FeatureSetPtr;