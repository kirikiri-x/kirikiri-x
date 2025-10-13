#include <tjs.h>
#include <tjsNative.h>

namespace LibRuntime {
    namespace Rendering {
        class LayerTree;
    }

    namespace TJSClasses {
        class StoragesClass : public tTJSNativeClass {
        public:
            StoragesClass();

            static tjs_uint32 ClassID;
            tTJSNativeInstance *CreateNativeInstance() override;
        };
    }

}