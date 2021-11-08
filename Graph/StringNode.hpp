#ifndef __STRINGNODE_HPP__
#define __STRINGNODE_HPP__

#include "Node.hpp"

#include <string>

using namespace std;

namespace mobo
{
    class StringNode : public Node
    {
        DECLARE_TYPE

        public:
            StringNode(const string& iValue = "") : Node(), value(iValue) { }
            virtual void serializeSelf(Json::Value &jsonSelf) const;
            virtual void desereializeSelf(const Json::Value &jsonSelf);

            void setValue(const string& iValue) { value = iValue; }
            const string& getValue() { return value; }

        protected:
            string value;
    };
}

#endif
