#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <string.h>
#include <lua/lua.h>
#include <lua/lauxlib.h>
#include <lua/lualib.h>

#include "gpiolib.h"
#include "rtoslib.h"

#define GPIO_PIN "5"

static void load_custom_libs(lua_State *L)
{
    luaL_requiref(L, "gpio", luaopen_lgpio, 1);
    lua_pop(L, 1);

    luaL_requiref(L, "rtos", luaopen_lrtos, 1);
    lua_pop(L, 1);
}

static const char *prg =
        "gpio.set_direction(" GPIO_PIN ", 2)\n"
        "level = 1\n"
        "for i = 1, 100 do\n"
        "  print(string.format(\"Iteration %d..., GPIO5=%d\", i, level))\n"
        "  gpio.set_level(" GPIO_PIN ", level)\n"
        "  level = 1 - level\n"
        "  rtos.delay(500)\n"
        "end\n";

static void report(lua_State *L, int status)
{
    if (status == LUA_OK)
        return;

    const char *msg = lua_tostring(L, -1);
    printf("%s\n", msg);
    lua_pop(L, 1);
}

void test(void *arg)
{
    printf("Program:\n%s\n", prg);

    lua_State *L = luaL_newstate();
    if (!L)
    {
        printf("Could not create state\n");
        while (1) { vTaskDelay(1000); }
    }

    luaL_openlibs(L);
    load_custom_libs(L);

    int r = luaL_loadstring(L, prg);
    if (r)
    {
        report(L, r);
        while (1) { vTaskDelay(1000); }
    }

    r = lua_pcall(L, 0, 0, 0);
    if (r)
        report(L, r);

    lua_close(L);

    printf("State closed, heap: %d\n", xPortGetFreeHeapSize());
    while (1)
    {
        printf(".");
        fflush(stdout);
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void app_main()
{
    xTaskCreate(test, "test", 0x10000, NULL, 5, NULL);
}
