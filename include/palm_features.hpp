
#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <ios>
#include <iostream>
#include <cstddef>
#include <bitset>
#include "parameters.hpp"
typedef std::byte byte;
typedef std::bitset<Parameters::bits_per_feature> FeatureDataType;
typedef std::vector<byte> ByteVector;
typedef ByteVector *ByteVectorPtr;

class OneFeature
{
    private:
    int _no_of_bytes ;
    int id;
    public:
    ByteVectorPtr Bytes;
    FeatureDataType Bits;
    void set_value(std::string);
    OneFeature(int);
    OneFeature(std::vector<int>  &);
    OneFeature(std::string);
    std::string to_string();
    std::string to_bit_string();
    void PopulateRandom();
    void TweakBits(int);
};

typedef std::vector<OneFeature*> FeatureArray;
typedef FeatureArray *FeatureArrayPtr;
