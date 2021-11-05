#ifndef __CONTEXT_HPP__
#define __CONTEXT_HPP__

#include "uuid.hpp"
#include "SmartPtr.hpp"
#include "Node.hpp"

namespace mobo
{
    class Context
    {
        public:
            Context();
            virtual ~Context();

            void addNode(Node* iNode);

            void setRoot(const uuid& iNodeId);
            void clearRoot(const uuid& iNodeId);

            void update();

            void submit();
            void retract();

            virtual void initialize();
            virtual void finalize();

            const time_point<steady_clock>& getTimestamp() const;

        protected:
            time_point<steady_clock> timestamp;
            uuidMap<SmartPtr<Node>> nodes;
            uuidMap<SmartPtr<Node>> roots;
    };
}

#endif