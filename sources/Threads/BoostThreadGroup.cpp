//
// Created by Grégoire on 26/09/2017.
//

#include "Threads/BoostThreadGroup.hpp"

BoostThreadGroup::BoostThreadGroup(){

}

BoostThreadGroup::~BoostThreadGroup() {

}

void BoostThreadGroup::createThreads() {

}

void BoostThreadGroup::joinAll() {
    group.join_all();
}

void BoostThreadGroup::interruptAll() {
    group.interrupt_all();
}