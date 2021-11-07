#include "StringNode.hpp"

namespace mobo
{

    DERIVE_TYPE(StringNode, "7a9791ca-2fed-4faf-8a9e-a62a32e773ba", { &Node::_type })

    void StringNode::serializeSelf(Json::Value& jsonSelf) const
    {
        jsonSelf["value"] = Json::Value(value);
    }

    void StringNode::desereializeSelf(const Json::Value &jsonSelf)
    {
        value = jsonSelf["value"].asString();
    }
}