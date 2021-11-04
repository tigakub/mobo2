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
    
    void Context::addNode(Node* iNode)
    {
        nodes[iNode->nodeId] = iNode;
    }

    void Context::setRoot(const uuid& iNodeId)
    {
        auto i = nodes.find(iNodeId);
        if(i != nodes.end()) {
            if(i->second->nodeFlags.test(Node::ROOT_FLAG)) return;
            roots[iNodeId] = i->second;
            i->second->nodeFlags.set(Node::ROOT_FLAG);
        }
    }

    void Context::clearRoot(const uuid& iNodeId)
    {
        auto i = roots.find(iNodeId);
        if(i != nodes.end()) {
            auto node = i->second;
            node->nodeFlags.clear(Node::ROOT_FLAG);
            roots.erase(i);
        }
    }

    void Context::update()
    {
        time_point<steady_clock> timestamp = steady_clock::now();

        for(auto i : roots) {
            i.second->updateIfNeeded(*this, timestamp);
        }
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

}