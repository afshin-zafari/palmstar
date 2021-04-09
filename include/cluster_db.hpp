#include <vector>
#include <map>
#include "palm_features.hpp"
#include "database.hpp"
typedef ulong HandUniqueID;
HandUniqueID GetHandUniqueID(PersonID person_id, HandID hand_id)
{
  return (person_id << 2) + (hand_id %4);
}
struct HandOneFeature
{
  OneFeaturePtr feature;
  HandID        hand_id;
  PersonID      person_id;
  ushort        bit_count;
  HandOneFeature (HandUniqueID,OneFeaturePtr);
};
typedef HandOneFeature *HandOneFeaturePtr;
typedef std::vector<HandOneFeaturePtr> ArrayOfHandOneFeature;
typedef ArrayOfHandOneFeature *ArrayOfHandOneFeaturePtr;
typedef std::map<HandUniqueID,ArrayOfHandOneFeaturePtr> HandClusterType;

typedef HandClusterType *HandClusterTypePtr;
typedef std::vector<HandUniqueID> ArrayOfHandUniqueID;
typedef ArrayOfHandUniqueID *ArrayOfHandUniqueIDPtr;
typedef std::map<uint,ArrayOfHandUniqueIDPtr> BitCountClusterType;
typedef BitCountClusterType *BitCountClusterTypePtr;

class OneFeatureCluster 
{
    public:
    HandClusterTypePtr hands_cluster; // hand_id -> array of one feature of a hand 
    BitCountClusterTypePtr bit_count_cluster;
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