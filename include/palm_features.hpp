
#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <ios>
#include <iostream>
#include <cstddef>
typedef std::byte byte;
typedef std::vector<byte> ByteVector;
typedef ByteVector *ByteVectorPtr;

class OneFeature
{
    private:
    int _no_of_bytes ;
    int id;
    public:
    ByteVectorPtr Bytes;
    void set_value(std::string);
    OneFeature(int);
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