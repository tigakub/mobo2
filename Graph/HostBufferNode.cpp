#include "HostBufferNode.hpp"

namespace mobo
{

    DERIVE_TYPE(HostBufferNode, "11174dd5-2234-4b69-9af7-4f099b16ad28", { &DataSourceNode::_type });

    DERIVE_TYPE(HostV2BufferNode, "9c95978c-beed-48dd-8fe0-ce1d0abf65fa", { &HostBufferNode::_type });
    DERIVE_TYPE(HostV3BufferNode, "daf63155-3800-434c-8157-94dda0c62082", { &HostBufferNode::_type });
    DERIVE_TYPE(HostV4BufferNode, "cd1995a0-35b1-49c0-95a5-3bfe2aa1fc31", { &HostBufferNode::_type });
    DERIVE_TYPE(HostIndexBufferNode, "859ff41a-3008-4c8a-8b33-d95770808dd3", { &HostBufferNode::_type });

}
