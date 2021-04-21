#include "palm_search.hpp"
Search::Search(ClusterDBPtr _cluster_db,FeatureArrayPtr _fa):
    cluster_db(_cluster_db),
    query(_fa)
{
    local_searches = new ArrayOfOneFeatureSearch(query->size());
    for(int feature_index=0;feature_index<local_searches->size(); feature_index++)
    {
        local_searches->at(feature_index)->candidates = new ArrayOfCandidateHands();
        local_searches->at(feature_index)->feature_index = feature_index;
    }
}
void Search::SearchForFeature(int f)
{
    auto bit_cluster   = * (cluster_db->columns->at(f)->bit_count_cluster);
    auto hand_cluster  = * (cluster_db->columns->at(f)->hands_cluster);
    auto query_feature = * query->at(f);
    uint bit_count = query_feature.GetBitCountGroup();

    auto hand_list = *bit_cluster[bit_count];
    for(auto hand : hand_list)
    {
        auto hands_feature_values = *hand_cluster[hand->ul_hand_unique_id];
        float max_diff = 0.0;
        float min_diff = 0.0;
        HandUniqueID hand_uid;
        for(auto feature_value: hands_feature_values)
        {
            auto diff = query_feature.DifferenceWith(feature_value->feature);
            max_diff == (max_diff > diff) ? max_diff : diff;
            min_diff == (min_diff < diff) ? min_diff : diff;            
            hand_uid.Set(feature_value->person_id,feature_value->hand_id);
        }
        if (IsAcceptableDifference(min_diff, max_diff))
        {
            auto candidates = *local_searches->at(f)->candidates;
            auto hand_candidate = new CandidateHand(hand_uid);
            hand_candidate->score = 1-max_diff;
            candidates.push_back(hand_candidate);
        }
    }

}
bool Search::IsAcceptableDifference(float min_diff, float max_diff)
{   
    return (1-max_diff) > 0.6 && (1-min_diff) > 0.6;
}
CandidateHand::CandidateHand(HandUniqueID h)
{
    hand_id = h;
}