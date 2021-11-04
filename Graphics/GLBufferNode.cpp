#include "GLBufferNode.hpp"

namespace mobo
{

    const Type GLBUFFERTYPE("6daf4786-0e35-4fb2-8796-d170d5e0627e");

    DERIVE_TYPE(GLV2BufferNode, "51c0e1c6-26bc-427c-b9bf-e8498fa5eab7", { &GLBUFFERTYPE });
    DERIVE_TYPE(GLV3BufferNode, "46a867b9-e00a-4b73-8a1a-9a504b5c9238", { &GLBUFFERTYPE });
    DERIVE_TYPE(GLV4BufferNode, "24941cad-ba78-4b81-a867-8011c1385ea0", { &GLBUFFERTYPE });
    DERIVE_TYPE(GLIndexBufferNode, "068f32a9-97f6-4908-9bed-07c6370efe8f", { &GLBUFFERTYPE });

}
