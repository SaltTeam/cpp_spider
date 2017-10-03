//
// Created by Grégoire on 03/10/2017.
//

#ifndef _BUFFER_HPP
# define _BUFFER_HPP

#include <string>

class Buffer {
public:
    Buffer();
    ~Buffer();

public:
    static Buffer &BufferInstance();
    void push(std::string msg);

private:
    static Buffer       _Instance;
    std::string         _buffer;

private:
    Buffer(Buffer const& copy) = delete;
};


#endif //_BUFFER_HPP
