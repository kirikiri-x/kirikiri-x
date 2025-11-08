#include "system.h"
#include "minimal.h"
#include "../script_manager.h"
#include "../event_manager.h"
#include "../libruntime.h"
#include "../storage/unified_storage_path.h"

using namespace LibRuntime::NativeClasses;

tjs_uint32 SystemNativeClass::ClassID = -1;

SystemNativeClass::SystemNativeClass() : tTJSNativeClass(TJS_W("System")) {
    TJS_BEGIN_NATIVE_MEMBERS(System)
        TJS_DECL_EMPTY_FINALIZE_METHOD

        //===== CONSTRUCTOR =====
        TJS_BEGIN_NATIVE_CONSTRUCTOR_DECL_NO_INSTANCE(System)
            return TJS_S_OK;
        TJS_END_NATIVE_CONSTRUCTOR_DECL(System)


        //===== METHODS =====
        TJS_BEGIN_NATIVE_METHOD_DECL(addContinuousHandler)
            if (numparams < 1) return TJS_E_BADPARAMCOUNT;
            auto clo = param[0]->AsObjectClosureNoAddRef();
            EventManager::add_continuous_handler(clo);
            return TJS_S_OK;
        TJS_END_NATIVE_METHOD_DECL(addContinuousHandler)


        TJS_BEGIN_NATIVE_METHOD_DECL(assignMessage)
            if (numparams < 2) return TJS_E_BADPARAMCOUNT;
            ScriptManager::assign_message(param[0]->GetString(), param[1]->GetString());
            return TJS_S_OK;
        TJS_END_NATIVE_METHOD_DECL(assignMessage)


        TJS_BEGIN_NATIVE_METHOD_DECL(createAppLock)
            if (numparams < 1) return TJS_E_BADPARAMCOUNT;
            auto func_result=  KrkrRuntime::sysfunc->create_app_lock(param[0]->GetString());
            if (result != nullptr) *result = func_result;
            return TJS_S_OK;
        TJS_END_NATIVE_METHOD_DECL(createAppLock)


        TJS_BEGIN_NATIVE_METHOD_DECL(createUUID)
            if (result != nullptr) *result = KrkrRuntime::sysfunc->get_uuid();
            return TJS_S_OK;
        TJS_END_NATIVE_METHOD_DECL(createUUID)


        TJS_BEGIN_NATIVE_METHOD_DECL(doCompact)
            return TJS_E_NOTIMPL;
        TJS_END_NATIVE_METHOD_DECL(doCompact)


        TJS_BEGIN_NATIVE_METHOD_DECL(dumpHeap)
            return TJS_E_NOTIMPL;
        TJS_END_NATIVE_METHOD_DECL(dumpHeap)


        TJS_BEGIN_NATIVE_METHOD_DECL(exit)
                exit(param[0]->AsInteger());
                return TJS_S_OK;    //関数が戻ることはないはず
        TJS_END_NATIVE_METHOD_DECL(exit)


        TJS_BEGIN_NATIVE_METHOD_DECL(getArgument)
            if (numparams < 1) return TJS_E_BADPARAMCOUNT;
            ttstr argval;

            if (!KrkrRuntime::get_argument(param[0]->GetString(), argval)) {
                result->Clear();
                return TJS_S_OK;
            }

            if (result != nullptr) *result = argval.c_str();
            return TJS_S_OK;
        TJS_END_NATIVE_METHOD_DECL(getArgument)


        TJS_BEGIN_NATIVE_METHOD_DECL(getKeyState)
            if (numparams < 1) return TJS_E_BADPARAMCOUNT;
            int numKeys = 0;
            const tjs_uint8* arr = SDL_GetKeyboardState(&numKeys);

            if (arr == nullptr || param[0]->AsInteger() >= numKeys) return TJS_E_INVALIDPARAM;
            if (result != nullptr) {
                *result = arr[param[0]->AsInteger()] ? 1 : 0;
            }
            return TJS_S_OK;
        TJS_END_NATIVE_METHOD_DECL(getKeyState)


        TJS_BEGIN_NATIVE_METHOD_DECL(getTickCount)
            if (result != nullptr) {
                *result = static_cast<tTVInteger>(KrkrRuntime::sysfunc->get_tick_time());
            }
            return TJS_S_OK;
        TJS_END_NATIVE_METHOD_DECL(getTickCount)


        TJS_BEGIN_NATIVE_METHOD_DECL(inform)
            if (numparams < 1) return TJS_E_BADPARAMCOUNT;
            ttstr message;
            ttstr caption;
            if (numparams > 1) {
                message = param[0]->GetString();
                caption = param[1]->GetString();
            } else {
                message = param[0]->GetString();
                caption = TJS_W("通知");
            }

            KrkrRuntime::system_ui->show_dialog(caption, message);
            return TJS_S_OK;
        TJS_END_NATIVE_METHOD_DECL(inform)


        TJS_BEGIN_NATIVE_METHOD_DECL(readRegValue)
            return TJS_E_NOTIMPL;
        TJS_END_NATIVE_METHOD_DECL(readRegValue)


        TJS_BEGIN_NATIVE_METHOD_DECL(removeContinuousHandler)
            if (numparams < 1) return TJS_E_BADPARAMCOUNT;
            auto clo = param[0]->AsObjectClosureNoAddRef();
            EventManager::remove_continuous_handler(clo);
            return TJS_S_OK;
        TJS_END_NATIVE_METHOD_DECL(removeContinuousHandler)


        TJS_BEGIN_NATIVE_METHOD_DECL(setArgument)
            if (numparams < 2) return TJS_E_BADPARAMCOUNT;
            KrkrRuntime::set_argument(param[0]->GetString(), param[1]->GetString());
            return TJS_S_OK;
        TJS_END_NATIVE_METHOD_DECL(setArgument)


        TJS_BEGIN_NATIVE_METHOD_DECL(shellExecute)
            if (numparams < 1) return TJS_E_BADPARAMCOUNT;
            const tjs_char *program = param[0]->GetString();
            const tjs_char *args = numparams > 1 ? param[1]->GetString() : nullptr;
            KrkrRuntime::sysfunc->execute(program, args);
            return TJS_S_OK;
        TJS_END_NATIVE_METHOD_DECL(shellExecute)


        TJS_BEGIN_NATIVE_METHOD_DECL(showVersion)
            KrkrRuntime::system_ui->show_version_dialog();
            return TJS_S_OK;
        TJS_END_NATIVE_METHOD_DECL(showVersion)


        TJS_BEGIN_NATIVE_METHOD_DECL(terminate)
            KrkrRuntime::request_quit(param[0]->AsInteger());
            return TJS_S_OK;
        TJS_END_NATIVE_METHOD_DECL(terminate)


        TJS_BEGIN_NATIVE_METHOD_DECL(toActualColor)
            return TJS_E_NOTIMPL;
        TJS_END_NATIVE_METHOD_DECL(toActualColor)


        TJS_BEGIN_NATIVE_METHOD_DECL(touchImages)
                return TJS_E_NOTIMPL;
        TJS_END_NATIVE_METHOD_DECL(touchImages)


        //===== PROPERTIES =====
        TJS_BEGIN_NATIVE_PROP_DECL(appDataPath)
        {
            TJS_BEGIN_NATIVE_PROP_GETTER
                {
                    ttstr app_data_path;
                    KrkrRuntime::filesystem->get_appdata_directory(app_data_path);
                    *result = app_data_path.c_str();
                    return TJS_S_OK;
                }
            TJS_END_NATIVE_PROP_GETTER

            TJS_DENY_NATIVE_PROP_SETTER
        }
        TJS_END_NATIVE_PROP_DECL(appDataPath)


        TJS_BEGIN_NATIVE_PROP_DECL(dataPath)
        {
            TJS_BEGIN_NATIVE_PROP_GETTER
                {
                    ttstr app_data_path;
                    if (!(KrkrRuntime::get_argument(TJS_W("-datapath"), app_data_path) || KrkrRuntime::filesystem->get_savedata_directory(app_data_path))) {
                        result->Clear();
                        return TJS_E_FAIL;
                    }
                    *result = static_cast<ttstr>(Storage::UnifiedStoragePath(KrkrRuntime::filesystem->get_unified_storage_path(app_data_path)));
                    return TJS_S_OK;
                }
            TJS_END_NATIVE_PROP_GETTER

            TJS_DENY_NATIVE_PROP_SETTER
        }
        TJS_END_NATIVE_PROP_DECL(dataPath)


        TJS_BEGIN_NATIVE_PROP_DECL(eventDisabled)
        {
            TJS_BEGIN_NATIVE_PROP_GETTER
            {
                *result = EventManager::is_event_enabled;
                return TJS_S_OK;
            }
            TJS_END_NATIVE_PROP_GETTER

            TJS_BEGIN_NATIVE_PROP_SETTER
            {
                EventManager::is_event_enabled = *param;
                return TJS_S_OK;
            }
            TJS_END_NATIVE_PROP_SETTER
        }
        TJS_END_NATIVE_PROP_DECL(eventDisabled)


        TJS_BEGIN_NATIVE_PROP_DECL(exceptionHandler)
        {
            TJS_BEGIN_NATIVE_PROP_GETTER
            {
                *result = EventManager::get_exception_handler();
                return TJS_S_OK;
            }
            TJS_END_NATIVE_PROP_GETTER

            TJS_BEGIN_NATIVE_PROP_SETTER
            {
                auto clo = param->AsObjectClosureNoAddRef();
                EventManager::set_exception_handler(clo);
                return TJS_S_OK;
            }
            TJS_END_NATIVE_PROP_SETTER
        }
        TJS_END_NATIVE_PROP_DECL(exceptionHandler)


        TJS_BEGIN_NATIVE_PROP_DECL(exeBits)
        {
            TJS_BEGIN_NATIVE_PROP_GETTER
            {
                *result = sizeof(void*) == 8 ? 64 : 32;
                return TJS_S_OK;
            }
            TJS_END_NATIVE_PROP_GETTER

            TJS_DENY_NATIVE_PROP_SETTER
        }
        TJS_END_NATIVE_PROP_DECL(exeBits)


        TJS_BEGIN_NATIVE_PROP_DECL(exeName)
        {
            TJS_BEGIN_NATIVE_PROP_GETTER
            {
                ttstr exe_path;
                auto get_result = KrkrRuntime::environment->get_execution_path(exe_path);
                if (!get_result) {
                    return TJS_E_FAIL; // Execution path could not be retrieved
                }
                Storage::UnifiedStoragePath path = KrkrRuntime::filesystem->get_unified_storage_path(exe_path.AsStdString());
                *result = path.get_fullpath();
                return TJS_S_OK;
            }
            TJS_END_NATIVE_PROP_GETTER

            TJS_DENY_NATIVE_PROP_SETTER
        }
        TJS_END_NATIVE_PROP_DECL(exeName)


        TJS_BEGIN_NATIVE_PROP_DECL(exePath)
        {
            TJS_BEGIN_NATIVE_PROP_GETTER
            {
                ttstr exe_path;
                if (!KrkrRuntime::environment->get_execution_path(exe_path)) {
                    return TJS_E_FAIL; // Execution path could not be retrieved
                }
                Storage::UnifiedStoragePath unified_path = KrkrRuntime::filesystem->get_unified_storage_path(exe_path.AsStdString());
                *result = unified_path.parent_directory().get_fullpath();
                return TJS_S_OK;
            }
            TJS_END_NATIVE_PROP_GETTER

            TJS_DENY_NATIVE_PROP_SETTER
        }
        TJS_END_NATIVE_PROP_DECL(exePath)


        TJS_BEGIN_NATIVE_PROP_DECL(exitOnWindowClose)
        {
            TJS_BEGIN_NATIVE_PROP_GETTER
            {
                return TJS_E_NOTIMPL;
            }
            TJS_END_NATIVE_PROP_GETTER

            TJS_BEGIN_NATIVE_PROP_SETTER
            {
                return TJS_E_NOTIMPL;
            }
            TJS_END_NATIVE_PROP_SETTER
        }
        TJS_END_NATIVE_PROP_DECL(exitOnWindowClose)


        TJS_BEGIN_NATIVE_PROP_DECL(graphicCacheLimit)
        {
            TJS_BEGIN_NATIVE_PROP_GETTER
            {
                return TJS_E_NOTIMPL;
            }
            TJS_END_NATIVE_PROP_GETTER

            TJS_BEGIN_NATIVE_PROP_SETTER
            {
                return TJS_E_NOTIMPL;
            }
            TJS_END_NATIVE_PROP_SETTER
        }
        TJS_END_NATIVE_PROP_DECL(graphicCacheLimit)


        TJS_BEGIN_NATIVE_PROP_DECL(onActivate)
        {
            TJS_BEGIN_NATIVE_PROP_GETTER
            {
                return TJS_E_NOTIMPL;
            }
            TJS_END_NATIVE_PROP_GETTER

            TJS_BEGIN_NATIVE_PROP_SETTER
            {
                return TJS_E_NOTIMPL;
            }
            TJS_END_NATIVE_PROP_SETTER
        }
        TJS_END_NATIVE_PROP_DECL(onActivate)


        TJS_BEGIN_NATIVE_PROP_DECL(onDeactivate)
        {
            TJS_BEGIN_NATIVE_PROP_GETTER
            {
                return TJS_E_NOTIMPL;
            }
            TJS_END_NATIVE_PROP_GETTER

            TJS_BEGIN_NATIVE_PROP_SETTER
            {
                return TJS_E_NOTIMPL;
            }
            TJS_END_NATIVE_PROP_SETTER
        }
        TJS_END_NATIVE_PROP_DECL(onDeactivate)


        TJS_BEGIN_NATIVE_PROP_DECL(osName)
        {
            TJS_BEGIN_NATIVE_PROP_GETTER
            {
                ttstr osname;
                KrkrRuntime::environment->get_os_name(osname);
                *result = osname;
                return TJS_S_OK;
            }
            TJS_END_NATIVE_PROP_GETTER

            TJS_DENY_NATIVE_PROP_SETTER
        }
        TJS_END_NATIVE_PROP_DECL(osName)


        TJS_BEGIN_NATIVE_PROP_DECL(personalPath)
        {
            TJS_BEGIN_NATIVE_PROP_GETTER
            {
                ttstr personal_path;
                if (!KrkrRuntime::environment->get_personal_path(personal_path)) {
                    return TJS_E_FAIL; // Personal path could not be retrieved
                }
                *result = KrkrRuntime::filesystem->get_unified_storage_path(personal_path.AsStdString()).get_fullpath();
                return TJS_S_OK;
            }
            TJS_END_NATIVE_PROP_GETTER

            TJS_DENY_NATIVE_PROP_SETTER
        }
        TJS_END_NATIVE_PROP_DECL(personalPath)


        TJS_BEGIN_NATIVE_PROP_DECL(platformName)
        {
            TJS_BEGIN_NATIVE_PROP_GETTER
            {
                ttstr platform_name;
                if (!KrkrRuntime::environment->get_platform_name(platform_name)) {
                    return TJS_E_FAIL; // Platform name could not be retrieved
                }
                *result = platform_name;
                return TJS_S_OK;
            }
            TJS_END_NATIVE_PROP_GETTER

            TJS_DENY_NATIVE_PROP_SETTER
        }
        TJS_END_NATIVE_PROP_DECL(platformName)


        TJS_BEGIN_NATIVE_PROP_DECL(savedGamesPath)
        {
            TJS_BEGIN_NATIVE_PROP_GETTER
            {
                ttstr saved_games_path;
                if (!KrkrRuntime::environment->get_saved_games_path(saved_games_path)) {
                    return TJS_E_FAIL; // Saved games path could not be retrieved
                }
                *result = KrkrRuntime::filesystem->get_unified_storage_path(saved_games_path.AsStdString()).get_fullpath();
                return TJS_S_OK;
            }
            TJS_END_NATIVE_PROP_GETTER

            TJS_DENY_NATIVE_PROP_SETTER
        }
        TJS_END_NATIVE_PROP_DECL(savedGamesPath)


        TJS_BEGIN_NATIVE_PROP_DECL(screenHeight)
        {
            TJS_BEGIN_NATIVE_PROP_GETTER
            {
                SDL_DisplayMode dm;
                SDL_GetCurrentDisplayMode(0, &dm);
                *result = static_cast<tTVInteger>(dm.h);
                return TJS_S_OK;
            }
            TJS_END_NATIVE_PROP_GETTER

            TJS_DENY_NATIVE_PROP_SETTER
        }
        TJS_END_NATIVE_PROP_DECL(screenHeight)


        TJS_BEGIN_NATIVE_PROP_DECL(screenWidth)
        {
            TJS_BEGIN_NATIVE_PROP_GETTER
            {
                SDL_DisplayMode dm;
                SDL_GetCurrentDisplayMode(0, &dm);
                *result = static_cast<tTVInteger>(dm.w);
                return TJS_S_OK;
            }
            TJS_END_NATIVE_PROP_GETTER

            TJS_DENY_NATIVE_PROP_SETTER
        }
        TJS_END_NATIVE_PROP_DECL(screenWidth)


        TJS_BEGIN_NATIVE_PROP_DECL(title)
        {
            TJS_BEGIN_NATIVE_PROP_GETTER
            {
                return TJS_E_NOTIMPL;
            }
            TJS_END_NATIVE_PROP_GETTER

            TJS_BEGIN_NATIVE_PROP_SETTER
            {
                return TJS_E_NOTIMPL;
            }
            TJS_END_NATIVE_PROP_SETTER
        }
        TJS_END_NATIVE_PROP_DECL(title)


        TJS_BEGIN_NATIVE_PROP_DECL(versionString)
        {
            TJS_BEGIN_NATIVE_PROP_GETTER
                {
                    ttstr runtime_str;
                    KrkrRuntime::get_runtime_version(runtime_str);
                    *result = runtime_str.c_str();
                    return TJS_S_OK;
                }
            TJS_END_NATIVE_PROP_GETTER

            TJS_DENY_NATIVE_PROP_SETTER
        }
        TJS_END_NATIVE_STATIC_PROP_DECL(versionString)


        TJS_BEGIN_NATIVE_PROP_DECL(versionInformation)
        {
            TJS_BEGIN_NATIVE_PROP_GETTER
                {
                    ttstr runtime_str;
                    KrkrRuntime::get_runtime_version_full(runtime_str);
                    *result = runtime_str.c_str();
                    return TJS_S_OK;
                }
            TJS_END_NATIVE_PROP_GETTER

            TJS_DENY_NATIVE_PROP_SETTER
        }
        TJS_END_NATIVE_STATIC_PROP_DECL(versionInformation)
    TJS_END_NATIVE_MEMBERS

    tTJSVariant val(nullptr, nullptr);
    PropSet(TJS_MEMBERENSURE, TJS_W("exceptionHandler"), nullptr, &val, this);
    PropSet(TJS_MEMBERENSURE, TJS_W("onActivate"), nullptr, &val, this);
    PropSet(TJS_MEMBERENSURE, TJS_W("onDeactivate"), nullptr, &val, this);
}

tTJSNativeInstance *SystemNativeClass::CreateNativeInstance() {
    return nullptr;
}