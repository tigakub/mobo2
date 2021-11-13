#include "Context.hpp"
#include "Node.hpp"
#include "Link.hpp"
#include "Debug.hpp"

#include "NodeHeaders.hpp"

#include <algorithm> // For reverse()

#include <iostream>

using namespace std;

#define generator(CLASS) _generators[#CLASS] = [](void) { return new CLASS(); }

namespace mobo
{
    unordered_map<string, function<Node*(void)>> Node::_generators;
    Node* Node::generate(const string& iClassName)
    {
        if(_generators.size() == 0) {
            generator(HostV2BufferNode);
            generator(HostV3BufferNode);
            generator(HostV4BufferNode);
            generator(HostIndexBufferNode);
            generator(StringNode);
            generator(BinaryFileInputNode);
            generator(TextFileInputNode);
            generator(BinaryFileOutputNode);
            generator(TextFileOutputNode);
            generator(ImageNode);
            generator(GLV2BufferNode);
            generator(GLV3BufferNode);
            generator(GLV4BufferNode);
            generator(GLIndexBufferNode);
            generator(GLCamera);
            generator(GLDraw);
            generator(GLGeometry);
            generator(GLMaterial);
            generator(GLPipeline);
            generator(GLPipelineStart);
            generator(GLProgram);
            generator(GLVertexShader);
            generator(GLFragmentShader);
            generator(GL2DTexture);
            generator(GLRectTexture);
            generator(GLTransform);
        }
        if(_generators.find(iClassName) == _generators.end()) return nullptr;
        Node* obj = _generators[iClassName]();
        obj->setClassName(iClassName);
        cout << "Instantiated " << obj->getClassName() << endl;
        return obj;
    }

    DEFINE_TYPE(Node, "d8ce3630-2919-447c-9f7e-630bd647ff35")

    Node::Node(uint64_t iRef)
    : RefCtr(iRef), className(), nodeId(uuid::generate()), inputs()
    {
        nodeFlags.set(UPDATE_FLAG);
        stampTime(steady_clock::now());
    }

    Node::~Node()
    {
    }

    Json::Value Node::serialize() const
    {
        Json::Value jsonSelf(Json::objectValue);
        Json::Value jsonNodeId(nodeId.toString());
        Json::Value jsonNodeType(jsonType());
        Json::Value jsonInputs(Json::arrayValue);
        Json::Value jsonDInputs(Json::arrayValue);
        jsonSelf["nodeId"] = jsonNodeId;
        jsonSelf["type"] = jsonNodeType;
        for(auto l : inputs) {
            if(l.src) {
                jsonInputs.append(move(Json::Value(l.src.deref()->nodeId.toString())));
            } else {
                jsonInputs.append(move(Json::Value(Json::nullValue)));
            }
        }
        for(auto l : dinputs) {
            if(l.src) {
                jsonDInputs.append(move(Json::Value(l.src.deref()->nodeId.toString())));
            } else {
                jsonDInputs.append(move(Json::Value(Json::nullValue)));
            }
        }
        jsonSelf["inputs"] = jsonInputs;
        jsonSelf["dinputs"] = jsonDInputs;
        serializeSelf(jsonSelf);
        return jsonSelf;
    }

    void Node::serializeSelf(Json::Value& jsonSelf) const
    { }

    void Node::deserialize(const Json::Value& jsonSelf, uuidMap<Streamer*>& history, uuidMap<ForwardReference>& forwardReferences)
    {
        nodeId = jsonSelf["nodeId"].asString();
        history[nodeId] = this;
        for(auto i = forwardReferences.find(nodeId); i != forwardReferences.end(); i = forwardReferences.find(nodeId)) {
            i->second.resolve(this);
            forwardReferences.erase(i);
        }
        const Json::Value& jsonInputs = jsonSelf["inputs"];
        const Json::Value& jsonDInputs = jsonSelf["dinputs"];
        
        int inputIndex = 0;
        for(auto i = jsonInputs.begin(); i != jsonInputs.end() && inputIndex < inputs.size(); i++, inputIndex++) {
            if(!i->isNull()) {
                const Json::Value& jsonNodeRef = *i;
                uuid newNodeId(jsonNodeRef.asString());
                auto j = history.find(newNodeId);
                if(j == history.end()) {
                    forwardReferences.emplace(make_pair(newNodeId, inputs[inputIndex].src.forwardReference()));
                } else {
                    inputs[inputIndex].src = dynamic_cast<Node*>(j->second);
                }
            }
        }

        for(auto i = jsonDInputs.begin(); i != jsonDInputs.end(); i++) {
            const Json::Value& jsonNodeRef = *i;
            uuid newNodeId(jsonNodeRef.asString());
            auto j = history.find(newNodeId);
            if(j == history.end()) {
                dinputs.push_back(Link<Node>(nullptr));
                Link<Node>& linkRef = dinputs.back();
                forwardReferences.emplace(make_pair(newNodeId, linkRef.src.forwardReference()));
            } else {
                dinputs.push_back(Link<Node>(dynamic_cast<Node*>(j->second)));
            }
        }

        deserializeSelf(jsonSelf);
    }

    void Node::deserializeSelf(const Json::Value& jsonSelf) const
    { }

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
        if(i >= inputs.size()) {
            i -= inputs.size();
            if(i >= dinputs.size()) {
                return;
            }
            dinputs.erase(dinputs.begin() + i);
            return;
        }
        inputs[i].src = nullptr;
    }

    bool Node::deepSubmit(Context& iCtx)
    {
        for(auto i : inputs)
            i.src && i.src->deepSubmit(iCtx);
        for(auto i : dinputs)
            i.src && i.src->deepSubmit(iCtx);
        #ifdef TRACE
        cout << getClassName() << "::updateIfNeeded()" << endl;
        #endif
        updateIfNeeded(iCtx, iCtx.getTimestamp());
        #ifdef TRACE
        cout << getClassName() << "::submit()" << endl;
        #endif
        submit(iCtx);
        if(nodeFlags.test(ISOLATE)) {
            for(auto i = dinputs.rbegin(); i != dinputs.rend(); i++)
                i->src && i->src->deepRetract(iCtx);
            for(auto i = inputs.rbegin(); i != inputs.rend(); i++)
                i->src && i->src->deepRetract(iCtx);
        }
        return true;
    }
    bool Node::deepRetract(Context& iCtx)
    {
        #ifdef TRACE
        cout << getClassName() << "::retract()" << endl;
        #endif
        retract(iCtx);
        if(!nodeFlags.test(ISOLATE)) {
            for(auto i = dinputs.rbegin(); i != dinputs.rend(); i++)
                i->src && i->src->deepRetract(iCtx);
            for(auto i = inputs.rbegin(); i != inputs.rend(); i++)
                i->src && i->src->deepRetract(iCtx);
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
