#include "palm_features.hpp"
#include "cluster_db.hpp"

struct CandidateHand
{
    HandUniqueID hand_id;
    float score;
    CandidateHand(HandUniqueID h);
};
typedef CandidateHand *CandidateHandPtr;
typedef std::vector<CandidateHandPtr> ArrayOfCandidateHands;
typedef ArrayOfCandidateHands *ArrayOfCandidateHandsPtr;
class OneFeatureSearch
{
    public:
    int feature_index;
    ArrayOfCandidateHandsPtr candidates;
};
typedef OneFeatureSearch *OneFeatureSearchPtr;
typedef std::vector<OneFeatureSearchPtr> ArrayOfOneFeatureSearch;
typedef ArrayOfOneFeatureSearch *ArrayOfOneFeatureSearchPtr;
class Search
{
    public:
    FeatureArrayPtr query;
    ClusterDBPtr cluster_db;
    ArrayOfOneFeatureSearchPtr local_searches;
    Search(ClusterDBPtr,FeatureArrayPtr );
    void SearchForFeature(int feature_index);
    void Start();
    bool IsAcceptableDifference(float max_diff, float min_diff);
};