#include "uuid.hpp"

namespace mobo
{
    uuid uuid::generate()
    {
        uuid_t bytes;
        uuid_generate(bytes);
        return uuid(bytes);
    }
    uuid::uuid()
    {
    }

    uuid::uuid(const string& i)
    {
        uuid_parse(i.c_str(), bytes);
    }

    uuid::uuid(const uuid_t& i)
    {
        uuid_copy(bytes, i);
    }

    uuid::uuid(const uuid& i)
    {
        uuid_copy(bytes, i.bytes);
    }

    bool uuid::operator==(const uuid& i) const
    {
        return !uuid_compare(bytes, i.bytes);
    }

    bool uuid::operator!=(const uuid& i) const
    {
        return !((*this) == i);
    }

    string uuid::toString() const
    {
        char uuidstr[37];
        uuid_unparse(bytes, uuidstr);
        return move(string(uuidstr));
    }

    timesafe_uuid timesafe_uuid::generate()
    {
        uuid_t bytes;
        uuid_generate_time_safe(bytes);
        return timesafe_uuid(bytes);
    }

    timesafe_uuid::timesafe_uuid()
    : uuid()
    { }

    timesafe_uuid::timesafe_uuid(const timesafe_uuid& i)
    : uuid(i) { }

    timesafe_uuid::timesafe_uuid(const uuid_t& i)
    : uuid(i) { }

    time_point<system_clock> timesafe_uuid::toTime() const
    {
        struct timeval tv;
        time_t timeSinceEpoch = uuid_time(bytes, &tv);
        return system_clock::from_time_t(timeSinceEpoch);
    }

    bool timesafe_uuid::operator>=(const timesafe_uuid& i) const
    {
        return toTime() >= i.toTime();
    }

    bool timesafe_uuid::operator<=(const timesafe_uuid& i) const
    {
        return toTime() <= i.toTime();
    }

    bool timesafe_uuid::operator>(const timesafe_uuid& i) const
    {
        return toTime() > i.toTime();
    }

    bool timesafe_uuid::operator<(const timesafe_uuid& i) const
    {
        return toTime() < i.toTime();
    }

}
