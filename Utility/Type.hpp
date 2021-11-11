#ifndef __TYPE_HPP__
#define __TYPE_HPP__

#include "uuid.hpp"

#include <string>
#include <vector>
#include <cstdint> // for uint64_t
#include <jsoncpp/json/json.h>

using namespace std;

namespace mobo
{
    class Type
    {
        protected:
            static const vector<const Type*> nullVector;

        public:
            Type(const string& iId, const Type& iSuper)
            : baseTypes(), id(iId)
            {
                baseTypes[iSuper.id] = &iSuper;
            }

            Type(const uuid& iId, const Type& iSuper)
            : baseTypes(), id(iId)
            {
                baseTypes[iSuper.id] = &iSuper;
            }

            Type(const string& iId, const vector<const Type*>& iSupers = nullVector)
            : baseTypes(), id(iId)
            {
                for(auto t : iSupers) {
                    baseTypes[t->id] = t;
                }
            }

            Type(const uuid& iId, const vector<const Type*>& iSupers = nullVector)
            : baseTypes(), id(iId)
            {
                for(auto t : iSupers) {
                    baseTypes[t->id] = t;
                }
            }

            Type(const Type& iType)
            : baseTypes(iType.baseTypes), id(iType.id)
            { }

            Type(Type&& iType)
            : baseTypes(move(iType.baseTypes)), id(iType.id)
            { }

            virtual Type& operator=(const Type& iType) {
                id = iType.id;
                baseTypes = iType.baseTypes;
                return *this;
            }

            virtual Type& operator=(Type&& iType) {
                id = iType.id;
                baseTypes = move(iType.baseTypes);
                return *this;
            }

            void subtype(const Type* iType) {
                baseTypes[iType->id] = iType;
            }

            bool isBaseOf(const Type& iType) const;

            bool isSame(const Type& iType) const {
                return id == iType.id;
            }

        protected:
            uuid id;
            uuidMap<const Type*> baseTypes;
    };

}

#define DECLARE_TYPE public: static const Type _type; virtual const Type& type() const { return _type; } static const string _jsonType; virtual const string& jsonType() const { return _jsonType; }

#define DEFINE_TYPE(CLASS, ID) const Type CLASS::_type(ID); const string CLASS::_jsonType(#CLASS);
#define DERIVE_TYPE(CLASS, ID, SUBS) const Type CLASS::_type(ID, vector<const Type*>SUBS); const string CLASS::_jsonType(#CLASS);

#endif
