#include "database.hpp"
#include "log_manager.hpp"
void Database::CreateDatabase()
{
    ulong no_of_records = DbStructure.no_of_persons * DbStructure.no_of_records_for_a_hand * 2;
    records = new RecordSpase(no_of_records);
    for(int i=0;i< no_of_records; i++)
    {
        records->at(i) = new DbRecordType();
        records->at(i)->features = new FeatureSet(DbStructure.no_of_features, Parameters::bytes_per_feature);
    }


}
void Database::PopulateRandom(int bits_distance)
{
    long record_index = 0;
    for (int p=0; p< DbStructure.no_of_persons; p++)
    {
        for (int h = 0; h<2; h++)
        {
            auto originalRecord = records->at(record_index);
            auto originalFS = originalRecord ->features;
            originalRecord ->features->PopulateRandom();
            originalRecord ->person_id = p;
            originalRecord ->hand_id = h;
            for (int nh = 0; nh < DbStructure.no_of_records_for_a_hand; nh++ )            
            {
                record_index++;
                if ( record_index >=records->size())
                    break;
                int res = originalFS->CopyTo(records->at(record_index)->features);
                records->at(record_index)->features->TweakBits(bits_distance);
                records->at(record_index)->person_id = p;
                records->at(record_index)->hand_id = h;
            }
        }
    }
}
void Database::DumpRecordsView(int record_start, int record_end, int feature_start, int feature_end)
{
    for(int record_index=record_start; record_index < record_end; record_index++)
    {
        if ( record_index >=records->size())
            break;
        LogWrite(DEBUG_LEVEL,"person id: %ld, hand_id:%ld",(long)records->at(record_index)->person_id, (long)records->at(record_index)->hand_id )
        LogWrite(DEBUG_LEVEL,"features from %d to %d" , feature_start, feature_end);
        LogWrite(DEBUG_LEVEL,"record index %d", record_index);
        std::string row;
        for ( int j=feature_start; j < feature_end; j++)
        {
            auto fs = records->at(record_index)->features->get_feature(j);
            row += fs->to_string() +",";
        }            
        LogWrite(DEBUG_LEVEL,"%s",row.replace(row.size() -1 ,1," ").c_str());

    }
}
void Database::ReportHandsVariations(PersonID person, HandID hand)
{
    for(int record_index=0; record_index < records->size(); record_index++)
    {
        if ( records->at(record_index)->person_id != person) continue;
        if ( records->at(record_index)->hand_id != hand) continue;

        
    }

}