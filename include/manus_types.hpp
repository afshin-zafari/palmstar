#pragma once
#include <cstddef>
#include <bitset>
#include <array>
#include <vector>
#include <map>
#include "parameters.hpp"
/*=================================================================================*/
struct Point
{
    float x,y;
};
typedef Point *PointPtr;
typedef std::bitset<Parameters::bits_per_feature> BitString;
typedef BitString  *BitStringPtr;

/*=================================================================================*/
typedef std::array<std::byte,Parameters::bytes_per_feature> ArrayOfBytes;
typedef ArrayOfBytes *ArrayOfBytesPtr;

class DescriptorType
{
    public:
        BitString Bits;
        ArrayOfBytes Bytes;
        DescriptorType(){}
        ~DescriptorType(){}
        int CopyFrom(ArrayOfBytesPtr input);
        int CopyFrom(BitStringPtr input);
        int GetHammingDistance(DescriptorType *);
        int GetEuclideanDistance(DescriptorType *);
        void CopyToBits();
    private:
        void copy_to_bytes();
};
typedef DescriptorType *DescriptorTypePtr;
typedef std::vector<DescriptorType> VectorOfDesriptors;
typedef VectorOfDesriptors *VectorOfDescriptosPtr;
/*=================================================================================*/
typedef ulong HandIDType;
typedef ulong PersonIDType;

class Feature
{
public:
    HandIDType HandID;
    PersonIDType PersonID;
    bool IsPalmPrintFeature;
    Point Keypoint;
    DescriptorTypePtr Descriptor;
    Feature();
    ~Feature();
};
typedef Feature *FeaturePtr;
typedef std::vector<FeaturePtr> VectorOfFeaturePtrs;
typedef std::vector<Feature> VectorOfFeatures;
typedef VectorOfFeaturePtrs *VectorOfFeaturePtrsPtr;
typedef float HandGeometriesValueType;
/*=================================================================================*/
struct FingerType
{
    HandGeometriesValueType Width, Length;
};
class HandGeometriesType
{
    public:
    FingerType IndexFinger, MiddleFinger, RingFinger, PinkyFinger;
    HandGeometriesValueType PalmWidth;
};
/*=================================================================================*/
class Hand
{
public:
   HandIDType HandID;   
   VectorOfFeaturePtrs PalmPrintFeatures;
   VectorOfFeaturePtrs VeinFeatures;
   HandGeometriesType HandGeometries;
};
typedef Hand *HandPtr;
typedef std::vector<HandPtr> VectorOfHandPtr;
typedef VectorOfHandPtr *VectorOfHandPtrPtr;
/*=================================================================================*/
typedef std::map<std::string,std::string> TagsMap;

class Person
{
  public:
    PersonIDType PersonId;
    TagsMap Tags;
    HandPtr RightHandPalm,RightHandBack, LeftHandPalm,LeftHandBack;
    Person();
};
typedef Person *PersonPtr;
typedef std::vector<PersonPtr> VectorOfPersonPtrs;
typedef VectorOfPersonPtrs *VectorOfPersonPtrsPtr;
/*=================================================================================*/
struct QueryRequest
{
    VectorOfFeaturePtrsPtr QueryFeatures;
};
typedef QueryRequest *QueryRequestPtr;
/*=================================================================================*/
struct QueryResponse
{

};
typedef QueryResponse *QueryResponsePtr;
typedef std::vector<QueryResponsePtr> VectorOfQueryResponsePtrs;
typedef VectorOfQueryResponsePtrs *VectorOfQueryResponsePtrsPtr;
/*=================================================================================*/
class FeatureDatabase
{
    void InsertPerson(PersonPtr p);
    bool VerifyPerson(PersonPtr p);
    VectorOfQueryResponsePtrsPtr IdentifyPerson(QueryRequestPtr q);
};
    /*
    p-id, hid(l/r,b/p), tags, geo, palm-print/vein image

    f[]
        p-hlrbp-pv-id, x,y, [64]
    */

/*=================================================================================*/
struct StorageInfoType
{
    VectorOfFeatures features;
};
typedef StorageInfoType *StorageInfoTypePtr;
typedef std::vector<StorageInfoTypePtr> VectorOfStorageTypePtrs;
typedef VectorOfStorageTypePtrs *VectorOfStorageTypePtrsPtr;
/*=================================================================================*/
class StorageManager
{
    VectorOfStorageTypePtrsPtr GetStorage(FeaturePtr fp);
};
typedef StorageManager *StorageManagerPtr;
/*=================================================================================*/
class FeatureMatcher
{
    /*
    for qf in query
        for f_list in GetStorage(qf)
            pid, score = brute_force ( qf, f_list)
            result.append ( (pid,score) ) 
    return result.top_most()
    */
};
