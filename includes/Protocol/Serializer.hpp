//
// Serializer.hpp for cpp_spider in /home/delacr_a/rendu/CPP/cpp_spider
// 
// Made by Maxence Delacroix
// Login   <delacr_a@epitech.net>
// 
// Started on  Fri Oct  6 15:54:01 2017 Maxence Delacroix
// Last update Fri Oct  6 15:54:02 2017 Maxence Delacroix
//


#pragma once

#include <boost/property_tree/ptree.hpp>
#include <map>
#include "dataStructure.hpp"

namespace spider
{
  class Serializer
  {
  private:
    std::map<std::string, std::function<t_unserialized (boost::property_tree::ptree const &)>> unserialize_func;
    static Serializer m_instance;
    std::map<KEYTYPE, std::string> keytype_string;

  public:
    static Serializer &getSerializer();
    boost::property_tree::ptree serialize(t_message const &data) const;
    boost::property_tree::ptree serialize(t_register const &data) const;
    boost::property_tree::ptree serialize(t_mouse const &data) const;
    boost::property_tree::ptree serialize(t_command const &data) const;
    t_unserialized unserialize(boost::property_tree::ptree const &pt);
    boost::property_tree::ptree get_ptree_from_string(std::string const &json) const;
    std::string get_string_from_ptree(boost::property_tree::ptree const &pt) const;
    std::string get_string_from_keytype(KEYTYPE const &key) const;
    KEYTYPE get_keytype_from_string(std::string const &str) const;

  private:
    Serializer();
    ~Serializer();
    Serializer &operator=(Serializer const &other);
    Serializer(Serializer const &other);
  };
}
