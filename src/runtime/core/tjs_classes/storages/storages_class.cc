#include "storages_class.h"
#include "../../libruntime.h"

using namespace LibRuntime::TJSClasses;

tjs_uint32 StoragesClass::ClassID = -1;

StoragesClass::StoragesClass() : tTJSNativeClass(TJS_W("Storages")) {
    TJS_BEGIN_NATIVE_MEMBERS(Storages)
    TJS_DECL_EMPTY_FINALIZE_METHOD
        // constructor
        TJS_BEGIN_NATIVE_CONSTRUCTOR_DECL_NO_INSTANCE(Storages)
            return TJS_S_OK;
        TJS_END_NATIVE_CONSTRUCTOR_DECL(Storages)

        // methods
        TJS_BEGIN_NATIVE_METHOD_DECL(addAutoPath)
            if (numparams < 1) return TJS_E_BADPARAMCOUNT;
            if (param[0]->Type() != tvtString) return TJS_E_INVALIDPARAM;
            LibRuntime::KrkrRuntime::auto_paths.push_back(param[0]->AsString());
            return TJS_S_OK;
        TJS_END_NATIVE_METHOD_DECL(addAutoPath)

        TJS_BEGIN_NATIVE_METHOD_DECL(removeAutoPath)
            if (numparams < 1) return TJS_E_BADPARAMCOUNT;
            if (param[0]->Type() != tvtString) return TJS_E_INVALIDPARAM;
            LibRuntime::KrkrRuntime::auto_paths.erase(
                std::remove(
                    LibRuntime::KrkrRuntime::auto_paths.begin(),
                    LibRuntime::KrkrRuntime::auto_paths.end(), param[0]->AsString()
                ),
                LibRuntime::KrkrRuntime::auto_paths.end()
            );
            return TJS_S_OK;
        TJS_END_NATIVE_METHOD_DECL(removeAutoPath)

        TJS_BEGIN_NATIVE_METHOD_DECL(chopStorageExt)
            if (numparams < 1) return TJS_E_BADPARAMCOUNT;
            if (param[0]->Type() != tvtString) return TJS_E_INVALIDPARAM;

            auto storage_path = param[0]->GetString();
            int ext_last_index = -1;
            for (int i = wcslen(storage_path) - 1; i >= 0; i--) {
                if (storage_path[i] == TJS_W('.')) {
                    ext_last_index = i;
                    break;
                }
            }
            if (ext_last_index == -1) {
                return TJS_E_INVALIDPARAM;
            }
            
            if (result) {
                *result = tTJSString(storage_path, ext_last_index);
            }
            return TJS_S_OK;
        TJS_END_NATIVE_METHOD_DECL(chopStorageExt)

        TJS_BEGIN_NATIVE_METHOD_DECL(extractStorageExt)
            if (numparams < 1) return TJS_E_BADPARAMCOUNT;
            if (param[0]->Type() != tvtString) return TJS_E_INVALIDPARAM;
            auto storage_path = param[0]->GetString();
            int ext_last_index = -1;
            for (int i = wcslen(storage_path) - 1; i >= 0; i--) {
                if (storage_path[i] == TJS_W('.')) {
                    ext_last_index = i;
                    break;
                }
            }
            if (ext_last_index == -1) {
                return TJS_E_INVALIDPARAM;
            }
            if (result) {
                *result = tTJSString(storage_path + ext_last_index);
            }
            return TJS_S_OK;
        TJS_END_NATIVE_METHOD_DECL(extractStorageExt)

        TJS_BEGIN_NATIVE_METHOD_DECL(extractStorageName)
            if (numparams < 1) return TJS_E_BADPARAMCOUNT;
            if (param[0]->Type() != tvtString) return TJS_E_INVALIDPARAM;
            auto storage_path = param[0]->GetString();
            int name_last_index = -1;
            for (int i = wcslen(storage_path) - 1; i >= 0; i--) {
                if (storage_path[i] == TJS_W('/')) {
                    name_last_index = i;
                    break;
                }
            }
            if (name_last_index == -1) {
                return TJS_E_INVALIDPARAM;
            }
            if (result) {
                *result = tTJSString(storage_path, name_last_index);
            }
            return TJS_S_OK;
        TJS_END_NATIVE_METHOD_DECL(extractStorageName)

        TJS_BEGIN_NATIVE_METHOD_DECL(extractStoragePath)
            if (numparams < 1) return TJS_E_BADPARAMCOUNT;
            if (param[0]->Type() != tvtString) return TJS_E_INVALIDPARAM;
            auto storage_path = param[0]->GetString();
            int path_last_index = -1;
            for (int i = wcslen(storage_path) - 1; i >= 0; i--) {
                if (storage_path[i] == TJS_W('/')) {
                    path_last_index = i;
                    break;
                }
            }
            if (path_last_index == -1) {
                return TJS_E_INVALIDPARAM;
            }
            if (result) {
                *result = tTJSString(storage_path + path_last_index + 1);
            }
            return TJS_S_OK;
        TJS_END_NATIVE_METHOD_DECL(extractStoragePath)

        TJS_BEGIN_NATIVE_METHOD_DECL(getFullPath)
            if (numparams < 1) return TJS_E_BADPARAMCOUNT;
            if (param[0]->Type() != tvtString) return TJS_E_INVALIDPARAM;
            auto converted = KrkrRuntime::filesystem->get_unified_storage_path(param[0]->GetString());
            if (result) {
                *result = converted.get_fullpath();
            }
            return TJS_S_OK;
        TJS_END_NATIVE_METHOD_DECL(getFullPath)

        TJS_BEGIN_NATIVE_METHOD_DECL(getLocalName)
            if (numparams < 1) return TJS_E_BADPARAMCOUNT;
            if (param[0]->Type() != tvtString) return TJS_E_INVALIDPARAM;
            //TODO: UnifiedStoragePath -> LocalNameに変換する
            auto converted = KrkrRuntime::filesystem->get_unified_storage_path(param[0]->GetString());
            if (result) {
                *result = converted.get_fullpath();
            }
            return TJS_S_OK;
        TJS_END_NATIVE_METHOD_DECL(getLocalName)

    TJS_END_NATIVE_MEMBERS
}

tTJSNativeInstance *StoragesClass::CreateNativeInstance() {
    return nullptr;
}
