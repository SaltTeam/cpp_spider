//
// Created by Grégoire on 26/09/2017.
//

#ifndef CPP_SPIDER_SERVICE_HPP
#define CPP_SPIDER_SERVICE_HPP

#include <queue>
#include <boost/atomic/atomic.hpp>

namespace spider {

    class Service {
    public:
        void manageCom();

        void loop();

        void checkClient();
    };
}
#endif //CPP_SPIDER_SERVICE_HPP
