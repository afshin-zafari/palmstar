#include "cluster_db.hpp"
void ClusterDB::ClusterTheDB(void)
{
    for( int r_index=0;base_db->records->size();r_index++)
    {
        auto rec = base_db->records->at(r_index);
        for(int  j=0; j<base_db->DbStructure.no_of_features; j++)
        {
            InsertFeature(rec,j);
        }
    }
    BuildBitsCluster();
}
ClusterDB::ClusterDB(Database *db)
{
    base_db = db;
    int nf = db->DbStructure.no_of_features;
    columns = new ArrayOfOneFeatureCluster(nf);
    for(int i=0; i<nf; i++)
    {
        columns->at(i)->hands_cluster = new HandClusterType();
        columns->at(i)->bit_count_cluster = new FeatureClusterType();
    }
    ClusterTheDB();
}
HandUniqueID ClusterDB::GetUniqueID(Database::DbRecordTypePtr record)
{
    HandUniqueID result(record->person_id,record->hand_id);
    return result;
}
void ClusterDB::InsertFeature(Database::DbRecordTypePtr record, int feature_index)
{
    auto f = record->features->get_feature(feature_index);
    HandUniqueID uhand = GetUniqueID(record);
    columns->at(feature_index)->InsertFeature(uhand, f);
}
void ClusterDB::BuildBitsCluster()
{
    for(int col=0; col< columns->size(); col++)
    {
        HandClusterType &hc = *(columns->at(col)->hands_cluster);
        for(auto hand_feature : hc)
        {
            auto _features = *hand_feature.second;
            auto hand_uid = hand_feature.first;
        }
    }

}
void OneFeatureCluster::InsertFeature(HandUniqueID hand, OneFeaturePtr fp)
{
    HandClusterType &hc = *hands_cluster;
    if ( hc[hand.ul_hand_unique_id] == nullptr)
    {
        hc[hand.ul_hand_unique_id]  = new ArrayOfHandOneFeature();
    }
    auto h_f = new HandOneFeature(hand,fp);
    hc[hand.ul_hand_unique_id]->push_back(h_f);
}
HandOneFeature::HandOneFeature(HandUniqueID hand,OneFeaturePtr fp)
{
    feature = new OneFeature(fp->_no_of_bytes);
    feature->copy_value_from(fp);
    person_id = hand.GetPersonAndHand().first;
    hand_id = hand.GetPersonAndHand().second;
    bit_count = feature->Bits.count();
}
HandUniqueID::HandUniqueID(PersonID p, HandID h)
{
    Set(p,h);
}
PersonHandPair HandUniqueID::GetPersonAndHand()
{
    PersonHandPair h(person_id,hand_id);
    return h;
}
HandUniqueID::HandUniqueID()
{
    person_id = 0;
    hand_id = 0;
    ul_hand_unique_id = 0;
}
void HandUniqueID::Set(PersonID p, HandID h)
{
    person_id = p;
    hand_id = h;
    ul_hand_unique_id = person_id << 2  | hand_id & 0x03;        
}