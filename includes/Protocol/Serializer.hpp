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

/// \namespace spider
namespace spider
{
  /// \class Serializer
  class Serializer
  {
  private:
    std::map<std::string, std::function<t_unserialized (boost::property_tree::ptree const &)>> unserialize_func;
    static Serializer m_instance;
    std::map<KEYTYPE, std::string> keytype_string;

  public:
    /// \brief Function to get the Serializer or create it if he hasnn't been created yet.
    /// \return Returns the Serializer object.
    static Serializer &getSerializer();

    /// \brief Creates a ptree with the infos contained in the data structure (message).
    /// \param A t_message structure containing all the infos that needs to be serialized.
    /// \return Returns a ptree containing the infos of the structure that was given as parameter.
    boost::property_tree::ptree serialize(t_message const &data) const;

    /// \brief Creates a ptree with the infos contained in the data structure (register).
    /// \param A t_register structure containing all the infos that needs to be serialized.
    /// \return Returns a ptree containing the infos of the structure that was given as parameter.
    boost::property_tree::ptree serialize(t_register const &data) const;

    /// \brief Creates a ptree with the infos contained in the data structure (mouse).
    /// \param A t_mouse structure containing all the infos that needs to be serialized.
    /// \return Returns a ptree containing the infos of the structure that was given as parameter.
    boost::property_tree::ptree serialize(t_mouse const &data) const;

    /// \brief Creates a ptree with the infos contained in the data structure (command).
    /// \param A t_command structure containing all the infos that needs to be serialized.
    /// \return Returns a ptree containing the infos of the structure that was given as parameter.
    boost::property_tree::ptree serialize(t_command const &data) const;

    /// \brief Creates a t_unserialized structure that contains one structure with the infos that are contained in ptree (message, register, mouse or command).
    /// \param A ptree containing all the infos that needs to be unserialized.
    /// \return Returns a t_unserialized structure containing one structure with the infos that was contained in ptree (message, register, mouse or command).
    t_unserialized unserialize(boost::property_tree::ptree const &pt);

    /// \brief This function creates a ptree from a json formatted string.
    /// \param A json formatted string.
    /// \return Returns a ptree which contain the infos contained in the json formatted string
    boost::property_tree::ptree get_ptree_from_string(std::string const &json) const;

    /// \brief This function creates a json formatted string from a ptree.
    /// \param A ptree that contains the info you need to retrieve.
    /// \return Returns a string which contain the infos contained in the ptree in json format
    std::string get_string_from_ptree(boost::property_tree::ptree const &pt) const;

    /// \brief This function is used to get the name of the keytype in a string.
    /// \param A keytype you want to retrieve the name.
    /// \return Returns the string that correspond to name of the keytype.
    std::string get_string_from_keytype(KEYTYPE const &key) const;

    /// \brief This function is used to get the keytype value from its name.
    /// \param A string correponding to the name of the keytype.
    /// \return Returns the keytype value that correspond to the keytype name passed in parameter.
    KEYTYPE get_keytype_from_string(std::string const &str) const;

  private:
    Serializer();
    ~Serializer();
    Serializer &operator=(Serializer const &other);
    Serializer(Serializer const &other);
  };
}
