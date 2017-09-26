//
// Created by Grégoire on 26/09/2017.
//

#include "Threads/boostThreadGroup.hpp"

boostThreadGroup::boostThreadGroup(){

}

~boostThreadGroup::~boostThreadGroup() {

}

void boostThreadGroup::init(int nbThreads) {
/*
 * missing function pointer
 */
}

void boostThreadGroup::joinAll() {
    group.join_all();
}

void boostThreadGroup::interruptAll() {
    group.interrupt_all();
}