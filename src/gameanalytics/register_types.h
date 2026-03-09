#pragma once

#include "gdextension_interface.h"
#include "godot_cpp/core/defs.hpp"
#include "godot_cpp/godot.hpp"

void gdextension_init(godot::ModuleInitializationLevel p_level);
void gdextension_terminate(godot::ModuleInitializationLevel p_level);