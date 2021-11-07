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
                ROOT_FLAG = UPDATE_FLAG << 1
            };

        DECLARE_TYPE

        public:
            Node(uint64_t iRef = 0);
            virtual ~Node();

            virtual Json::Value serialize() const;
            virtual void serializeSelf(Json::Value& self) const;
            virtual void deserialize(const Json::Value& self, uuidMap<Streamer*>& history, uuidMap<ForwardReference>& forwardReferences);
            virtual void deserializeSelf(const Json::Value& self) const;

            void addInput(const Type&);

            template <class T, typename enable_if<is_base_of<Node,T>::value, bool>::type E = true> T* getInput(int iIndex)
            {
                if(iIndex >= inputs.size()) {
                    iIndex -= inputs.size();
                    return dynamic_cast<T*>(dinputs[iIndex].src.deref());
                }
                return dynamic_cast<T*>(inputs[iIndex].src.deref());
            }

            void addLinkTo(Node& iNewLink);
            bool linkTo(int i, Node& iNode);
            void unlink(int i);
            
            void updateIfNeeded(Context &iCtx, const time_point<steady_clock>& iTimestamp);
            virtual bool update(Context& iCtx) { return true; }

            bool deepSubmit(Context& iCtx);
            bool deepRetract(Context& iCtx);
            virtual bool submit(Context& iCtx);
            virtual bool retract(Context& iCtx);

        public:
            Flags nodeFlags;

            uuid nodeId;
            vector<Link<Node>> inputs;
            vector<Link<Node>> dinputs;
    };
};

#endif