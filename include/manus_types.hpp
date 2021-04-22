#pragma once
#include <cstddef>
#include <bitset>
#include <array>
#include <vector>
#include "parameters.hpp"
struct Point
{
    float x,y;
};
typedef Point *PointPtr;
typedef std::bitset<Parameters::bits_per_feature> BitString;
typedef BitString  *BitStringPtr;

typedef std::array<std::byte,Parameters::bytes_per_feature> ArrayOfBytes;
typedef ArrayOfBytes *ArrayOfBytesPtr;

class DescriptorType
{
    public:
        BitString Bits;
        ArrayOfBytes Bytes;
        DescriptorType();
        ~DescriptorType();
        int CopyFrom(ArrayOfBytesPtr input);
        int CopyFrom(BitStringPtr input);
        int GetHammingDistance(DescriptorType *);
        int GetEuclideanDistance(DescriptorType *);
    private:
        void copy_to_bits();
        void copy_to_bytes();
};
typedef DescriptorType *DescriptorTypePtr;
typedef std::vector<DescriptorType> VectorOfDesriptors;
typedef VectorOfDesriptors *VectorOfDescriptosPtr;
class Feature
{
public:
    Point Keypoint;
    DescriptorTypePtr Descriptor;
    Feature();
    ~Feature();
};
typedef Feature *FeaturePtr;
typedef float HandGeometriesValueType;
class HandGeometriesType
{
    public:
    enum FingerNames
    {
        INDEX_FINGER,
        MIDDLE_FINGER,
        RING_FINGER,
        LITTLE_FINGER,
        PINKY_FINGER = LITTLE_FINGER
    };
    std::array<HandGeometriesValueType,4> FingerWidth, FingerLength;
    std::array<HandGeometriesValueType,3> FingerAngles;
    HandGeometriesValueType GetWidth(int finger);
    HandGeometriesValueType GetLength(int finger);
    HandGeometriesValueType GetAngle(int finger_1, int finger_2);
};
class Hand
{
public:
   VectorOfDesriptors PalmPrintFeatures;
   VectorOfDesriptors VeinFeatures;
   HandGeometriesType HandGeometries;
};
typedef Hand *HandPtr;
typedef std::vector<HandPtr> VectorofHandPtr;
typedef VectorofHandPtr *VectorOfHandPtrPtr;
class Person
{
  public:
    VectorOfHandPtrPtr RightHandPalm,RightHandBack, LeftHandPalm,LeftHandBack;
};