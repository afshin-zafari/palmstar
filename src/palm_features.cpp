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

    if (Bits.size() < _no_of_bytes * 8)
        Bits.reset();

    ByteVector &_Bytes = *Bytes;
    short int b;
    for(int i=0; i < _no_of_bytes; i++)    
    {
        std::istringstream ss( hex_string.substr(i*2,2));
        ss >> std::hex >> b;
        _Bytes[i] = (byte)b;
        if ( Bits.size() < _no_of_bytes * 8)
        {
            FeatureDataType bits (static_cast<long>(b));
            Bits <<= 8;
            Bits |= bits;
        }
    }
}
OneFeature::OneFeature(std::vector<int>  &list)
{
    _no_of_bytes = list.size();
    this->Bytes = new ByteVector(_no_of_bytes);
    ByteVector &_Bytes = *Bytes;
    if (Bits.size() <= _no_of_bytes * 8)
        Bits.reset();
    short int b;
    for(int i=0; i < _no_of_bytes; i++)    
    {
        _Bytes[i] = (byte)list[i];
        if ( Bits.size() <= _no_of_bytes * 8)
        {
            FeatureDataType bits (static_cast<long>(list[i]));
            Bits <<= 8;
            Bits |= bits;
        }
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
std::string OneFeature::to_bit_string()
{
    if ( Bits.size() <= _no_of_bytes * 8)
        return Bits.to_string();
    return "";
}