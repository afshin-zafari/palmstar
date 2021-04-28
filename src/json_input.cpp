#include "json_input.hpp" 
#include <assert.h>

void f_convert(void)
{
    rapidjson::Document document;
    auto id = document["ID"].GetInt();
    const char left_hand_features[] = "left hand features";
    const rapidjson::Value &hand_geometris_ = document[left_hand_features];
    const rapidjson::Value &hand_geometris = hand_geometris_["Hand geometric features"];
    auto palm_width= hand_geometris["palm width"].GetFloat();
    auto index_finger_width = hand_geometris["index finger width"].GetFloat();
    auto index_finger_length= hand_geometris["index finger length"].GetFloat();



    const rapidjson::Value &palm_features_ = document["left hand features"];
    const rapidjson::Value &palm_features = palm_features_["Palm print image features"];
    for (int i = 0; i < palm_features.Size(); i++)
    {
        const rapidjson::Value &f = palm_features[i].GetObject();
        const rapidjson::Value &keypoint_x_ = f["keypoint"];
        const rapidjson::Value &keypoint_x = keypoint_x_[0];

    }

}