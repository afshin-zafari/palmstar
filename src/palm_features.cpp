#include "palm_features.hpp"
OneFeature::OneFeature(int no_of_bytes)
{
    this->Bytes = new ByteVector(no_of_bytes);
    _no_of_bytes = no_of_bytes;
}
OneFeature::OneFeature(std::string hex_string)
{
    _no_of_bytes = hex_string.length()/2;
    this->Bytes = new ByteVector(_no_of_bytes);
    ByteVector &_Bytes = *Bytes;
    short int b;
    for(int i=0; i < _no_of_bytes; i++)    
    {
        std::istringstream ss( hex_string.substr(i*2,2));
        ss >> std::hex >> b;
        _Bytes[i] = (byte)b;
    }
}
std::string OneFeature::to_string()
{
    ByteVector &_Bytes = *Bytes;
    std::ostringstream ss;
    char s[3];
    for(int i=0; i< _no_of_bytes; i++)    
    {
        sprintf(s,"%02X",(short int)_Bytes[i]);
        ss << s ;
    }
    return ss.str();
}
