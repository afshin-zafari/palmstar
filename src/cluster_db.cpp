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
        columns->at(i)->bit_count_cluster = new BitCountClusterType();
    }
    ClusterTheDB();
}
HandUniqueID ClusterDB::GetUniqueID(Database::DbRecordTypePtr record)
{
    HandUniqueID result;//TODO
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
            ulong sum = 0;
            uint count = 0;
            for( auto hand_f: _features)
            {
                sum += hand_f->bit_count;
                count++;
            }
            ulong avg = sum / count;
            auto bc = *columns->at(col)->bit_count_cluster;
            if (bc[avg] == nullptr)
            {
                bc[avg] =  new ArrayOfHandUniqueID();
            }
            bc[avg]->push_back(hand_uid);
        }
    }

}
void OneFeatureCluster::InsertFeature(HandUniqueID hand, OneFeaturePtr fp)
{
    HandClusterType &hc = *hands_cluster;
    if ( hc[hand] == nullptr)
    {
        hc[hand]  = new ArrayOfHandOneFeature();
    }
    auto h_f = new HandOneFeature(hand,fp);
    hc[hand]->push_back(h_f);
}
HandOneFeature::HandOneFeature(HandUniqueID hand,OneFeaturePtr fp)
{
    feature = new OneFeature(fp->_no_of_bytes);
    feature->copy_value_from(fp);
    hand_id = hand & 0x03;
    person_id = hand >> 2;
    bit_count = feature->Bits.count();
}