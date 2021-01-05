#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <string.h>
#include <lua/lua.h>
#include <lua/lauxlib.h>
#include <lua/lualib.h>

#define LUA_MAX_MEMSIZE 0x10000 // 64k

static const char *prg =
        "local t = {}\n"
        "for i = 1, 10000 do\n"
        "  print(string.format(\"Iteration %d...\", i))\n"
        "  t[i] = string.format(\"Lorem ipsum asklfhskldjf hskljfh slkjfd sdklfjh slkfjh sdkljfjh sdklfjh sdklf %d...\", i)\n"
        "end\n";

static void report(lua_State *L, int status)
{
    if (status == LUA_OK)
        return;

    const char *msg = lua_tostring(L, -1);
    printf("%s\n", msg);
    lua_pop(L, 1);
}

static int lua_mem_size = 0;

static void* l_alloc(void *ud, void *ptr, size_t osize, size_t nsize)
{
    int new_size = lua_mem_size - osize + nsize;
    if (new_size > LUA_MAX_MEMSIZE)
    {
        printf("Error! Lua wants more memory than we can allocate: %u > %u\n", new_size, LUA_MAX_MEMSIZE);
        return NULL;
    }
    //printf("Reallocating: old = %u, new = %u\n", lua_mem_size, new_size);
    lua_mem_size = new_size;

    if (nsize == 0)
    {
        free(ptr);
        return NULL;
    }
    else
        return realloc(ptr, nsize);
}

void test(void *arg)
{
    printf("Program:\n%s\n", prg);

    lua_State *L = lua_newstate(l_alloc, NULL);
    if (!L)
    {
        printf("Could not create state\n");
        while (1) { vTaskDelay(1000); }
    }

    luaL_openlibs(L);

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
