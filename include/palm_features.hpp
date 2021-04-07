
#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <ios>
#include <iostream>
#include <cstddef>
#include <bitset>
#include <assert.h>
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
    void get_value_from_bits();
    public:
    ByteVectorPtr Bytes;
    FeatureDataType Bits;
    OneFeature(int);
    OneFeature(std::vector<int>  &);
    OneFeature(std::string);
    std::string to_string();
    std::string to_bit_string();
    void PopulateRandom();
    void TweakBits(int);
    double Difference(OneFeature*);
    byte get_byte_from_bitset(int byte_index);
    void copy_value_from(OneFeature *);
};

typedef std::vector<OneFeature*> FeatureArray;
typedef FeatureArray *FeatureArrayPtr;
