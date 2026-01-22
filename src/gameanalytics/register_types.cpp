#include "register_types.h"

#include "godot_cpp/godot.hpp"
#include "godot_cpp/core/class_db.hpp"
#include <godot_cpp/classes/engine.hpp>
#include "GameAnalytics.h"

static GameAnalytics* GAPtr = nullptr;

void gdextension_init(godot::ModuleInitializationLevel p_level)
{
    if (p_level == godot::MODULE_INITIALIZATION_LEVEL_CORE) {
        godot::ClassDB::register_class<GameAnalytics>();
        GAPtr = memnew(GameAnalytics);
        godot::Engine::get_singleton()->register_singleton("GameAnalytics", GAPtr);
    }
}

void gdextension_terminate(godot::ModuleInitializationLevel p_level)
{
    if (p_level == godot::MODULE_INITIALIZATION_LEVEL_CORE) {
        memdelete(GAPtr);
    }
}

extern "C" {

    GDExtensionBool GDE_EXPORT gameanalytics_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization) {
        godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

        init_obj.register_initializer(gdextension_init);
        init_obj.register_terminator(gdextension_terminate);
        init_obj.set_minimum_library_initialization_level(godot::MODULE_INITIALIZATION_LEVEL_CORE);

        return init_obj.init();
    }
}
