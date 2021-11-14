#include "Context.hpp"
#include "Link.hpp"

#include <iostream>

using namespace std;

namespace mobo
{

    Context::Context()
    : nodes(), roots()
    { }

    Context::~Context()
    { }

    Json::Value Context::serialize() const
    {
        Json::Value jsonThis(Json::arrayValue);
        for(auto node : nodes) {
            jsonThis.append(move(node.second->serialize()));
        }
        return jsonThis;
    }
    
    void Context::deserialize(Json::Value& root)
    {
        uuidMap<Streamer*> history;
        uuidMap<ForwardReference> forwardReferences;
        for(auto i = root.begin(); i != root.end(); i++) {
            Json::Value& jsonObject = *i;
            Node* newNode = Node::generate(jsonObject["type"].asString());
            newNode->deserialize(jsonObject, history, forwardReferences);
            nodes[newNode->getNodeId()] = newNode;
        }
    }

    void Context::addNode(Node* iNode)
    {
        nodes[iNode->getNodeId()] = iNode;
    }

    void Context::setRoot(const uuid& iNodeId)
    {
        auto i = nodes.find(iNodeId);
        if(i != nodes.end()) {
            if(i->second->testNodeFlags(Node::ROOT_FLAG)) return;
            roots[iNodeId] = i->second;
            i->second->setNodeFlags(Node::ROOT_FLAG);
        }
    }

    void Context::clearRoot(const uuid& iNodeId)
    {
        auto i = roots.find(iNodeId);
        if(i != nodes.end()) {
            auto node = i->second;
            node->clearNodeFlags(Node::ROOT_FLAG);
            roots.erase(i);
        }
    }

    void Context::update()
    {
        timestamp = steady_clock::now();

        for(auto i : roots) {
            i.second->checkUpdateNeeded(*this, timestamp);
        }
        /*
        for(auto i : roots) {
            i.second->updateIfNeeded(*this, timestamp);
        }
        */
    }

    void Context::submit()
    {
        initialize();
        for(auto i : roots) {
            i.second->deepSubmit(*this);
        }
    }

    void Context::retract()
    {
        for(auto i : roots) {
            i.second->deepRetract(*this);
        }
        finalize();
    }

    void Context::initialize()
    {
    }

    void Context::finalize()
    {
    }

    const time_point<steady_clock>& Context::getTimestamp() const
    {
        return timestamp;
    }

}