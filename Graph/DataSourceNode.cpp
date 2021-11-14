#include "DataSourceNode.hpp"

namespace mobo
{

    DERIVE_TYPE(DataSourceNode, "915326c4-0886-499a-ad2f-5f9b8916e9c4", {&Node::_type});
    DERIVE_TYPE(FrameSourceNode, "c09b6687-51f7-4f56-9468-a98a238a5b24", {&DataSourceNode::_type});

}