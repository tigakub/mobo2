#ifndef __TIMESTAMP_HPP__
#define __TIMESTAMP_HPP__

#include "uuid.hpp"

namespace mobo
{
    
    class Timestamp
    {
        public:
            const time_point<steady_clock>& timestamp() { return stamp; }
            void stampTime(const time_point<steady_clock>& iTimestamp) { stamp = iTimestamp; }

        protected:
            time_point<steady_clock> stamp;
    };

}

#endif
