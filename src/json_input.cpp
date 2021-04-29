#include "json_input.hpp" 



void AddFeatures(const rapidjson::Value &json_features,VectorOfFeaturePtrs &person_features )
{
    for (int i = 0; i < json_features.Size(); i++)
    {
        FeaturePtr new_feautre = new Feature();
        const rapidjson::Value &f = json_features[i];
        const rapidjson::Value &keypoint = f["keypoint"];
        new_feautre->Keypoint.x = keypoint[0].GetFloat();
        new_feautre->Keypoint.y = keypoint[1].GetFloat();
        const rapidjson::Value &descriptor= f["descriptor"];
        for(int j=0; j< descriptor.Size(); j++)
        {
            new_feautre->Descriptor->Bytes[j] = static_cast<std::byte>(descriptor[j].GetInt());
        }
        new_feautre->Descriptor->CopyToBits();

        person_features.push_back(new_feautre);
    }
    LogWrite(DEBUG_LEVEL,"");
}
void GetHandGeometries(const rapidjson::Value &json_geometries,HandGeometriesType &hand_geo)
{
    auto palm_width= json_geometries["palm width"].GetFloat();
    auto index_finger_width = json_geometries["index finger width"].GetFloat();
    auto index_finger_length= json_geometries["index finger length"].GetFloat();
    auto middle_finger_width = json_geometries["middle finger width"].GetFloat();
    auto middle_finger_length= json_geometries["middle finger length"].GetFloat();
    auto ring_finger_width = json_geometries["ring finger width"].GetFloat();
    auto ring_finger_length= json_geometries["ring finger length"].GetFloat();
    auto pinky_finger_width = json_geometries["pinky finger width"].GetFloat();
    auto pinky_finger_length= json_geometries["pinky finger length"].GetFloat();

    hand_geo.PalmWidth = palm_width;
    hand_geo.IndexFinger.Width = index_finger_width ;
    hand_geo.IndexFinger.Length = index_finger_length;
    hand_geo.MiddleFinger.Width = middle_finger_width;
    hand_geo.MiddleFinger.Length = middle_finger_length;
    hand_geo.RingFinger.Width = ring_finger_width ;
    hand_geo.RingFinger.Length = ring_finger_length;
    hand_geo.PinkyFinger.Width = pinky_finger_width ;
    hand_geo.PinkyFinger.Length = pinky_finger_length;
}
void GetHandInfo(const rapidjson::Value &json_hand_info,HandPtr new_hand )
{
    const char hand_geo_key[]="Hand geometric features";
    if (json_hand_info.HasMember(hand_geo_key))
    {
        const rapidjson::Value &hand_geometries = json_hand_info[hand_geo_key];
        GetHandGeometries( hand_geometries, new_hand->HandGeometries);
    }

    const rapidjson::Value &palm_features = json_hand_info["Palm print image features"];
    AddFeatures(palm_features, new_hand->PalmPrintFeatures);

    const rapidjson::Value &vein_features = json_hand_info["Palm vein image features"];
    AddFeatures(vein_features, new_hand->VeinFeatures);

}
void GetHandBackInfo(const rapidjson::Value &json_hand_info,HandPtr new_hand )
{
    const char hand_geo_key[]="Hand geometric features";
    if (json_hand_info.HasMember(hand_geo_key))
    {
        const rapidjson::Value &hand_geometries = json_hand_info[hand_geo_key];
        GetHandGeometries( hand_geometries, new_hand->HandGeometries);
    }

    const char back_print_image_key []="Back print image features";
    if (json_hand_info.HasMember(back_print_image_key ))
    {
        const rapidjson::Value &palm_features = json_hand_info[back_print_image_key];
        AddFeatures(palm_features, new_hand->PalmPrintFeatures);
    }

    const char back_vein_image_key []="Back vein image features";
    if (json_hand_info.HasMember(back_vein_image_key ))
    {
        const rapidjson::Value &vein_features = json_hand_info[back_vein_image_key ];
        AddFeatures(vein_features, new_hand->VeinFeatures);
    }

}
PersonPtr CreateNewPersonFromJSON(std::string json_filename)
{
    rapidjson::Document document;

    std::ifstream json_file(json_filename);
    std::stringstream json_source;
    json_source << json_file.rdbuf();
    document.Parse(json_source.str().c_str());

    PersonPtr new_person = new Person();

    auto id = document["ID"].GetInt64();
    new_person->PersonId = id;
    const rapidjson::Value &tags = document["tag information"];
    for (rapidjson::Value::ConstMemberIterator itr = tags.MemberBegin(); itr != tags.MemberEnd(); ++itr)
    {
        if (itr->value.IsString())
            new_person->Tags[itr->name.GetString()] = itr->value.GetString();
        else
        {
            int a= itr->value.GetInt();
            new_person->Tags[itr->name.GetString()] = std::to_string(a);
        }
    }

    const rapidjson::Value &left_hand_features = document["left hand features"];
    GetHandInfo(left_hand_features, new_person->LeftHandPalm);

    const rapidjson::Value &right_hand_features = document["right hand features"];
    GetHandInfo(right_hand_features, new_person->RightHandPalm);

    const char left_hand_back_key[]="left hand back features";
    if ( document.HasMember(left_hand_back_key))
    {
        const rapidjson::Value &left_hand_back_features = document[left_hand_back_key];
        GetHandBackInfo(left_hand_back_features, new_person->LeftHandBack);
    }

    const char right_hand_back_key[]="right hand back features";
    if ( document.HasMember(right_hand_back_key))
    {
        const rapidjson::Value &right_hand_back_features = document[right_hand_back_key];
        GetHandBackInfo(right_hand_back_features, new_person->RightHandBack);
    }
    json_file.close();
    return new_person;
}