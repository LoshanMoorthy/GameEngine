/**
   @brief Purpose of config.h:
   This header file defines the configuration structure and functions for the game engine.
   It includes the configuration state, key bindings, and functions to initialize and
   modify configuration settings.
*/

#pragma once

#include <stdlib.h>
#include "input.h"
#include "types.h"

typedef struct config
{
    u8 keybinds[5];
} Config_State;

void config_init(void);
void config_key_bind(Input_Key key, const char *key_name);