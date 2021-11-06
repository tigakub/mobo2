#include "Context.hpp"
#include "Node.hpp"
#include "Link.hpp"

#include <algorithm> // For reverse()

#include <iostream>

using namespace std;

namespace mobo
{
    DEFINE_TYPE(Node, "d8ce3630-2919-447c-9f7e-630bd647ff35")

    Node::Node(uint64_t iRef)
    : RefCtr(iRef), nodeId(uuid::generate()), inputs()
    {
        nodeFlags.set(UPDATE_FLAG);
        stampTime(steady_clock::now());
    }

    Node::~Node()
    {
    }

    void Node::addInput(const Type& iType)
    {
        inputs.push_back(Link<Node>(iType));
    }

    void Node::addLinkTo(Node& iNode)
    {
        dinputs.push_back(Link<Node>(&iNode));
    }

    bool Node::linkTo(int i, Node& iNode)
    {
        if(i >= inputs.size()) return false;
        if(i >= inputs.size()) {
            i -= inputs.size();
            if(i >= dinputs.size()) return false;
            if(dinputs[i].type().isBaseOf(iNode.type())) {
                #ifdef TRACE
                cout << "Linking " << nodeId.toString() << " to " << iNode.nodeId.toString() << endl;
                #endif
                dinputs[i].src = &iNode;
                return true;
            }
        }
        if(inputs[i].type().isBaseOf(iNode.type())) {
            #ifdef TRACE
            cout << "Linking " << nodeId.toString() << " to " << iNode.nodeId.toString() << endl;
            #endif
            inputs[i].src = &iNode;
            return true;
        }
        return false;
    }

    void Node::updateIfNeeded(Context &iCtx, const time_point<steady_clock>& iTimestamp)
    {
        /*
        int i = inputs.size();
        while(i--) {
            Node* inputNode = getInput<Node>(i);
            if(inputNode) {
                #ifdef TRACE
                cout << "Updating source " << i << endl;
                #endif
                inputNode->updateIfNeeded(iCtx, iTimestamp);
            }
        }
        */
        if(iTimestamp > timestamp()) {
            if(nodeFlags.test(UPDATE_FLAG)) {
                update(iCtx);
                nodeFlags.clear(UPDATE_FLAG);
            }
            stampTime(iTimestamp);
        }
    }

    void Node::unlink(int i) {
        if(i >= inputs.size()) return;
        inputs[i].src = nullptr;
    }

    bool Node::deepSubmit(Context& iCtx)
    {
        for(auto i : inputs)
            i.src && i.src->deepSubmit(iCtx);
        #ifdef TRACE
        cout << "Deep submit " << nodeId.toString() << endl;
        #endif
        updateIfNeeded(iCtx, iCtx.getTimestamp());
        submit(iCtx);
        return true;
    }
    bool Node::deepRetract(Context& iCtx)
    {
        retract(iCtx);
        auto i = inputs.rbegin();
        while(i != inputs.rend()) {
            i->src && i->src->deepRetract(iCtx);
            i++;
        }
        return true;
    }

    bool Node::submit(Context& iCtx)
    {
        return true;
    }

    bool Node::retract(Context& iCtx)
    {
        return true;
    }
}
