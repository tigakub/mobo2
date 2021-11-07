#ifndef __STREAMER_HPP__
#define __STREAMER_HPP__

#include "uuid.hpp"
#include "SmartPtr.hpp"

#include <jsoncpp/json/json.h>

namespace mobo
{

    class Streamer
    {
        public:
            virtual ~Streamer() { }

            virtual Json::Value serialize() const = 0;

            virtual void deserialize(const Json::Value& jsonSelf, uuidMap<Streamer*>& history, uuidMap<ForwardReference>& forwardReferences) = 0;
    };

}

#endif