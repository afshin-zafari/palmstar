#include <vector>
#include <map>
#include "palm_features.hpp"
#include "database.hpp"
typedef std::pair<PersonID,HandID> PersonHandPair;
typedef ulong HandUniqueID_IntegralType;
class HandUniqueID
{
  private:
  PersonID person_id;
  HandID hand_id;  
  public: 
  HandUniqueID_IntegralType ul_hand_unique_id;
  HandUniqueID();
  HandUniqueID(PersonID p, HandID h);
  PersonHandPair GetPersonAndHand();
  void Set(PersonID p, HandID h);
};
typedef HandUniqueID *HandUniqueIDPtr;
HandUniqueID GetHandUniqueID(PersonID person_id, HandID hand_id)
{
  HandUniqueID h(person_id,hand_id);
  return h;
}
struct HandOneFeature
{
  OneFeaturePtr feature;
  HandID        hand_id;
  PersonID      person_id;
  ushort        bit_count;
  HandOneFeature (HandUniqueID,OneFeaturePtr);
};
typedef HandOneFeature *               HandOneFeaturePtr;
typedef std::vector<HandOneFeaturePtr> ArrayOfHandOneFeature;
typedef ArrayOfHandOneFeature *        ArrayOfHandOneFeaturePtr;
typedef std::map<HandUniqueID_IntegralType, ArrayOfHandOneFeaturePtr> HandClusterType;

typedef HandClusterType *                            HandClusterTypePtr;
typedef std::vector<HandUniqueIDPtr>                 ArrayOfHandUniqueID;
typedef ArrayOfHandUniqueID *                        ArrayOfHandUniqueIDPtr;
typedef unsigned long long                           ClusterKey;
typedef std::map<ClusterKey, ArrayOfHandUniqueIDPtr> FeatureClusterType;
typedef FeatureClusterType *                         FeatureClusterTypePtr;

struct ClusterInfo
{
  ClusterKey cluster_center;



};

class OneFeatureCluster 
{
    public:
    HandClusterTypePtr hands_cluster; // hand_id -> array of one feature of a hand 
    FeatureClusterTypePtr bit_count_cluster;
    OneFeatureCluster();
    void InsertFeature(HandUniqueID, OneFeaturePtr);
};
typedef OneFeatureCluster *OneFeatureClusterPtr;
typedef std::vector<OneFeatureClusterPtr> ArrayOfOneFeatureCluster;
typedef ArrayOfOneFeatureCluster *ArrayOfOneFeatureClusterPtr;

class ClusterDB
{
    private:
    Database *base_db;
    public:
    ArrayOfOneFeatureClusterPtr columns;
    ClusterDB(Database *);
    void InsertFeature(Database::DbRecordTypePtr record, int feature_index);
    HandUniqueID GetUniqueID(Database::DbRecordTypePtr record);
    void BuildBitsCluster(void);
    void ClusterTheDB(void);
};
typedef ClusterDB *ClusterDBPtr;
class rBRIFAlgorithm
{
  
  public:
  struct Parameters
  {
    int SubFeature_offset, SubFeature_length;
    int no_of_features_per_hash;
  };

};