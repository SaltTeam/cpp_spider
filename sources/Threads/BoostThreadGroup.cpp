//
// Created by Grégoire on 26/09/2017.
//

#include "../../includes/Threads/BoostThreadGroup.hpp"

BoostThreadGroup::BoostThreadGroup(){

}

BoostThreadGroup::~BoostThreadGroup() {

}

void BoostThreadGroup::createThreads(std::function<void(void)> funcPtr) {
    boost::thread   newThread(funcPtr);
    group.add_thread(&newThread);
}

void BoostThreadGroup::joinAll() {
    group.join_all();
}

void BoostThreadGroup::interruptAll() {
    group.interrupt_all();
}