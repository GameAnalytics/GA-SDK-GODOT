#include "register_types.h"
#include "core/class_db.h"
#include "core/engine.h"
#include "GameAnalytics.h"

static GameAnalytics* GAPtr = NULL;

void register_gameanalytics_types()
{
    ClassDB::register_class<GameAnalytics>();
    GAPtr = memnew(GameAnalytics);
    Engine::get_singleton()->add_singleton(Engine::Singleton("GameAnalytics", GameAnalytics::get_singleton()));
}

void unregister_gameanalytics_types()
{
    memdelete(GAPtr);
}
