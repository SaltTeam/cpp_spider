//
// Created by delacr_a on 28/09/17.
//

#ifndef JSON_CPP_DATASTRUCTURE_H
#define JSON_CPP_DATASTRUCTURE_H

# include <string>

enum class	KEYTYPE
{
    NONE = 0,
    RC,
    LC,
    SCROLLUP,
    SCROLLDOWN,
    MC
};

struct		        t_message
{
    std::string 	timestamp;
    std::string	    process;
    std::string	    data;
    std::string     type;
};

struct              t_mouse
{
    std::string     timestamp;
    std::string	    process;
    int             keytype;
    unsigned int    x;
    unsigned int    y;
    std::string     type;
};

struct		    t_register
{
    std::string os;
    std::string	mac;
    std::string	antivirus;
};

struct          t_command
{
    std::string type;
    std::string data;
};

struct          t_unserialized
{
    t_message   *message;
    t_register  *register_;
    t_mouse     *mouse;
    t_command   *command;
};

#endif //JSON_CPP_DATASTRUCTURE_H
