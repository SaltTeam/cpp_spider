//
// Created by Grégoire on 03/10/2017.
//

#include <string>
#include "Network/Buffer.hpp

namespace spider {

    Buffer::Buffer() {

    }

    Buffer::~Buffer() {

    }

    void Buffer::push(int id, std::string msg) {
        this->_bufferMap[id] += msg;
    }

    Buffer &Buffer::BufferInstance() {
        return _Instance;
    }

    void Buffer::addBuffer(int id) {
        std::string newbuf = "";
        this->_bufferMap[id] = newbuf;
    }
}