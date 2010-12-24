#pragma once

#include <boost/serialization/serialization.hpp>
#include <boost/numeric/ublas/vector.hpp>


class KGCOMMON_API PlayerData
{
    friend class boost::serialization::access; 

public:
    PlayerData() {};
    virtual ~PlayerData() {};

    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & pos;
    }

private:
    boost::numeric::ublas::vector<double> pos_;
};
