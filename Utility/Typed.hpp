#ifndef __TYPED_HPP__
#define __TYPED_HPP__

namespace mobo
{

    class Typed
    {
        public:
            virtual const Type& type() const = 0;

            bool isBaseOf(const Type& iType) const {
                return type().isBaseOf(iType);
            }
            
            bool isBaseOf(const Typed& iTyped) const {
                return isBaseOf(iTyped.type());
            }
    };

}

#endif
