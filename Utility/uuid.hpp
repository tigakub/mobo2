#ifndef __UUID_HPP__
#define __UUID_HPP__

#include <chrono>
#include <cstdint> // for uint64_t

using namespace std;
using namespace std::chrono;

#include <unordered_map>
#include <unordered_set>

#include <uuid/uuid.h>

using namespace std;

namespace mobo
{
    typedef struct uuid
    {
        static uuid generate();
        uuid();
        uuid(const string& i);
        uuid(const uuid_t& i);
        uuid(const uuid& i);

        bool operator==(const uuid& i) const;
        bool operator!=(const uuid& i) const;

        string toString() const;

        uuid_t bytes;
    } uuid;

    typedef struct timesafe_uuid : uuid
    {
        static timesafe_uuid generate();

        timesafe_uuid();   
        timesafe_uuid(const timesafe_uuid& i);

        bool operator>=(const timesafe_uuid& i) const;
        bool operator<=(const timesafe_uuid& i) const;
        bool operator>(const timesafe_uuid& i) const;
        bool operator<(const timesafe_uuid& i) const;

        time_point<system_clock> toTime() const;

        private:
            timesafe_uuid(const uuid_t& i);
    } typesafe_uuid;

    typedef struct uuidHasher
    {
        size_t operator()(const uuid& iId) const {
            const uint64_t* half = reinterpret_cast<const uint64_t*>(&iId.bytes);
            return half[0] ^ half[1];
        }
    } uuidHasher;

    template <class T>
    using uuidMap = unordered_map<uuid, T, uuidHasher>;
    using uuidSet = unordered_set<uuid, uuidHasher>;
}

#endif
