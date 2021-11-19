#ifndef __NODE_HPP__
#define __NODE_HPP__

#include "RefCtr.hpp"
#include "SmartPtr.hpp"
#include "Type.hpp"
#include "Typed.hpp"
#include "Timestamp.hpp"
#include "Flags.hpp"
#include "Link.hpp"
#include "Streamer.hpp"

#include <chrono>
#include <vector>
#include <type_traits> // for enable_if
#include <functional>

#include <jsoncpp/json/json.h>

using namespace std;
using namespace std::chrono;

namespace mobo
{
    class Context;

    class Node : public RefCtr, public Typed, public Streamer, Timestamp
    {
        public:
            static Node* generate(const string& iClassName);
            
        protected:
            static unordered_map<string, function<Node*(void)>> _generators;

        public:
            enum {
                UPDATE_FLAG = 1,
                ROOT_FLAG = UPDATE_FLAG << 1,
                ISOLATE = ROOT_FLAG << 1,
            };

        DECLARE_TYPE

        public:
            Node(uint64_t iRef = 0);
            Node(Node&& iNode) : RefCtr(), className(), nodeFlags(iNode.nodeFlags), nodeId(iNode.nodeId), inputs(move(iNode.inputs)), dinputs(move(iNode.dinputs)) { }
            virtual ~Node();


            const uuid& getNodeId() const { return nodeId; }

            virtual void setNodeFlags(uint64_t iFlags) { nodeFlags.set(iFlags); }
            virtual void clearNodeFlags(uint64_t iFlags) { nodeFlags.clear(iFlags); }
            virtual uint64_t testNodeFlags(uint64_t iFlags) const { return nodeFlags.test(iFlags); }

            void setClassName(const string& iClassName) { className = iClassName;}
            const string &getClassName() const { return className; }

            virtual Json::Value serialize() const;
            virtual void serializeSelf(Json::Value& self) const;
            virtual void deserialize(const Json::Value& self, uuidMap<Streamer*>& history, uuidMap<ForwardReference>& forwardReferences);
            virtual void deserializeSelf(const Json::Value& self) const;

            void addInput(const Type&);
            void removeInput(int i);

            template <class T, typename enable_if<is_base_of<Node,T>::value, bool>::type E = true> T* getInput(int iIndex)
            {
                if(iIndex >= inputs.size()) {
                    iIndex -= inputs.size();
                    return dynamic_cast<T*>(dinputs[iIndex].src.deref());
                }
                return dynamic_cast<T*>(inputs[iIndex].src.deref());
            }

            template <class T, typename enable_if<is_base_of<Node,T>::value, bool>::type E = true> const T* getInput(int iIndex) const
            {
                if(iIndex >= inputs.size()) {
                    iIndex -= inputs.size();
                    return dynamic_cast<const T*>(dinputs[iIndex].src.deref());
                }
                return dynamic_cast<const T*>(inputs[iIndex].src.deref());
            }

            void addLinkTo(Node* iNewLink);
            bool linkTo(int i, Node* iNode);
            void unlink(int i);
            
            bool checkUpdateNeeded(Context& iCtx, const time_point<steady_clock>& iTimestamp);
            void updateIfNeeded(Context &iCtx, const time_point<steady_clock>& iTimestamp);
            virtual bool update(Context& iCtx) { return true; }

            virtual bool deepSubmit(Context& iCtx);
            virtual bool deepRetract(Context& iCtx);
            virtual bool submit(Context& iCtx);
            virtual bool retract(Context& iCtx);

        protected:
            string className;
            Flags nodeFlags;
            uuid nodeId;
            vector<Link<Node>> inputs;
            vector<Link<Node>> dinputs;
            int submitCount;
    };
};

#endif