#include "gpiolib.h"
#include <driver/gpio.h>

static void lua_esp_check_err(lua_State *L, esp_err_t err)
{
    if (err != ESP_OK)
        luaL_error(L, "Error: %s", esp_err_to_name(err));
}

static int lgpio_reset_pin(lua_State *L)
{
    gpio_num_t pin = luaL_checkinteger(L, 1);

    lua_esp_check_err(L, gpio_reset_pin(pin));

    return 0;
}

static int lgpio_set_level(lua_State *L)
{
    gpio_num_t pin = luaL_checkinteger(L, 1);
    int level = luaL_checkinteger(L, 2);

    lua_esp_check_err(L, gpio_set_level(pin, level));

    return 0;
}

static int lgpio_get_level(lua_State *L)
{
    gpio_num_t pin = luaL_checkinteger(L, 1);
    lua_pushinteger(L, gpio_get_level(pin));

    return 1;
}

static int lgpio_set_direction(lua_State *L)
{
    gpio_num_t pin = luaL_checkinteger(L, 1);
    int mode = luaL_checkinteger(L, 2);

    lua_esp_check_err(L, gpio_set_direction(pin, mode));

    return 0;
}

static const struct luaL_Reg lgpio_funcs[] = {
    { "reset_pin", lgpio_reset_pin },
    { "set_direction", lgpio_set_direction },
    { "set_level", lgpio_set_level },
    { "get_level", lgpio_get_level },
    { NULL, NULL }
};

int luaopen_lgpio(lua_State *L)
{
    luaL_newlib(L, lgpio_funcs);

    return 1;
}

