//
// Created by Grégoire on 03/10/2017.
//

#ifndef _BUFFER_HPP
# define _BUFFER_HPP

#include <string>

/// \namespace spider
namespace spider {

    /// \class Buffer
    class Buffer {
    public:
        /// \brief constructor
        Buffer();

        /// \brief destructor
        ~Buffer();

        Buffer(Buffer const &copy) = delete;

    public:
        /// \brief Call a Buffer Instance
        static Buffer &BufferInstance();

        /// \brief push a string in the buffer
        void push(std::string msg);

    private:
        static Buffer _Instance;
        std::string _buffer;
    };
}

#endif //_BUFFER_HPP
