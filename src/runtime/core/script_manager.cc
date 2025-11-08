#include <tjsTypes.h>
#include "script_manager.h"
#include "native_classes/minimal.h"
#include "native_classes/system.h"
#include "native_classes/window.h"
#include "native_classes/layer.h"

using namespace LibRuntime;

// --- Init global variable ---
bool ScriptManager::initialized = false;
tTJS *ScriptManager::tjs_engine = nullptr;
ttstr ScriptManager::startup_script_name = TJS_W("startup.tjs");


bool ScriptManager::init(const ttstr &startup_script_name, const ttstr &encoding, int krkr_compatible) {
    // --- Check if already initialized ---
    if (initialized) return true;

    // --- Initialize TJS ---
    tjs_engine = new tTJS;
    if (tjs_engine == nullptr) return false;

    // --- 吉里吉里互換モード毎の初期化 ---
    switch (krkr_compatible) {
        default:
        case 0:
            // 吉里吉里X
            tjs_engine->SetPPValue(TJS_W("kirikirix"), 1);
            break;

        case 1:
            // 吉里吉里Z
            tjs_engine->SetPPValue(TJS_W("kirikiriz"), 1);
            break;

        case 2:
            // 吉里吉里2
            tjs_engine->SetPPValue(TJS_W("kirikiri2"), 1);
            break;
    }

    // --- Register native objects ---
    iTJSDispatch2 *global = tjs_engine->GetGlobalNoAddRef();
    iTJSDispatch2 *dsp;
    tTJSVariant val;
    #define REGISTER_OBJECT(classname, native_classname) \
        dsp = new native_classname(); \
        val = tTJSVariant(dsp/*, dsp*/); \
        dsp->Release(); \
        global->PropSet(TJS_MEMBERENSURE|TJS_IGNOREPROP, TJS_W(#classname), NULL, \
            &val, global);
    REGISTER_OBJECT(mini, NativeClasses::MinimalNativeClass);
    REGISTER_OBJECT(System, NativeClasses::SystemNativeClass);
    REGISTER_OBJECT(Window, NativeClasses::WindowNativeClass);
    REGISTER_OBJECT(Layer, NativeClasses::LayerNativeClass);

    // --- Finalize ---
    initialized = true;
    return true;
}


void ScriptManager::run(const ttstr &script) {
    try {
        tjs_engine->ExecScript(script);
    } catch (eTJSScriptException &error) {
        handle_script_error(error);
    }
}

tTJSVariant ScriptManager::eval(const ttstr &script) {
    tTJSVariant result;
    tjs_engine->EvalExpression(script, &result);
    return result;
}

bool ScriptManager::assign_message(const ttstr& msg, const ttstr& val) {
    return TJSAssignMessage(msg.c_str(), val.c_str());
}

bool ScriptManager::handle_script_error(eTJSScriptException &error) {
    auto global_clo = tjs_engine->GetGlobalNoAddRef();
    if (global_clo == nullptr) return false;

    tTJSVariant system;
    auto result = global_clo->PropGet(TJS_MEMBERMUSTEXIST, TJS_W("System"), nullptr, &system, global_clo);
    if (TJS_FAILED(result)) return false;
    auto system_clo = system.AsObjectClosureNoAddRef();

    tTJSVariant exception_handler;
    result = system_clo.PropGet(TJS_MEMBERMUSTEXIST, TJS_W("exceptionHandler"), nullptr, &exception_handler, nullptr);
    if (TJS_FAILED(result) || exception_handler.Type() != tvtObject) return false;

    tTJSVariant param_obj = error.GetValue();
    tTJSVariant *param[] = { &param_obj };
    tTJSVariant exec_result;

    exception_handler.AsObjectClosureNoAddRef().FuncCall(0, nullptr, nullptr, &exec_result, 1, param, nullptr);

    return exec_result;
}

ttstr ScriptManager::get_script_engine_version() {
    tjs_char version[32];
    TJS_snprintf(version, sizeof(version)/sizeof(tjs_char), TJS_W("%d.%d.%d"),
        TJSVersionMajor,
        TJSVersionMinor,
        TJSVersionRelease);
    return version;
}