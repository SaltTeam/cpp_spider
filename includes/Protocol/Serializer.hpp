//
// Created by delacr_a on 28/09/17.
//

#ifndef JSON_CPP_SERIALIZER_H
#define JSON_CPP_SERIALIZER_H

#include <boost/property_tree/ptree.hpp>
#include <map>
#include "dataStructure.hpp"

class Serializer
{
private:
    std::map<std::string, std::function<t_unserialized (boost::property_tree::ptree const &)>> unserialize_func;

public:
    Serializer();
    ~Serializer();
    boost::property_tree::ptree serialize(t_message const &data) const;
    boost::property_tree::ptree serialize(t_register const &data) const;
    boost::property_tree::ptree serialize(t_mouse const &data) const;
    boost::property_tree::ptree serialize(t_command const &data) const;
    t_unserialized unserialize(boost::property_tree::ptree const &pt);
    boost::property_tree::ptree get_ptree_from_string(std::string const &json) const;
    std::string const &get_string_from_ptree(boost::property_tree::ptree const &pt) const;
};


#endif //JSON_CPP_SERIALIZER_H
