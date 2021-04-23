void f()
{
    auto id = document["ID"];
    auto hand_geometris = document["left hand features"]["Hand geometric features"];
    auto palm_width= hand_geometris["palm width"];
    auto index_finger_width = hand_geometris["index finger width"];
    auto index_finger_length= hand_geometris["index finger length"];
    auto index_finger_width = hand_geometris["index finger width"];
    auto index_finger_width = hand_geometris["index finger width"];



    auto palm_features = document["left hand features"]["Palm print image features"];
    for (int i = 0; i < palm_features.Size(); i++)
    {
        auto f = palm_features[i];
        auto keypoint_x = f["keypoint"][0];
        auto keypoint_y = f["keypoint"][1];
        auto descriptor= f["discriptor"];
        for(int j=0;j<descriptor.Size();j++)
        {
            auto byte = descriptor[j];
        }

    }
    auto vein_features = document["left hand features"]["Palm vein image features"];
    for (int i = 0; i < vein_features.Size(); i++)
    {
        auto f = vein_features[i];
        auto keypoint_x = f["keypoint"][0];
        auto keypoint_y = f["keypoint"][1];
        auto descriptor= f["discriptor"];
        for(int j=0;j<descriptor.Size();j++)
        {
            auto byte = descriptor[j];
        }

    }

}