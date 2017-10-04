//
// Created by Grégoire on 03/10/2017.
//

#include "Network/Buffer.hpp"
#include "../includes/Network/Buffer.hpp"

namespace spider {

    Buffer::Buffer() {

    }

    Buffer::~Buffer() {

    }

    void Buffer::push(std::string msg) {
        this->_buffer += msg;
    }

    Buffer &Buffer::BufferInstance() {
        return _Instance;
    }
}