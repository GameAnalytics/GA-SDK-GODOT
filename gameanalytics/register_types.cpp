#include "register_types.h"
#include "core/object/class_db.h"
#include "core/config/engine.h"
#include "GameAnalytics.h"

static GameAnalytics* GAPtr = NULL;

void initialize_gameanalytics_module(ModuleInitializationLevel p_level)
{
    if (p_level == MODULE_INITIALIZATION_LEVEL_CORE) {
        ClassDB::register_class<GameAnalytics>();
        GAPtr = memnew(GameAnalytics);
        Engine::get_singleton()->add_singleton(Engine::Singleton("GameAnalytics", GameAnalytics::get_singleton()));
    }
}

void uninitialize_gameanalytics_module(ModuleInitializationLevel p_level)
{
    if (p_level == MODULE_INITIALIZATION_LEVEL_CORE) {
        memdelete(GAPtr);
    }
}
