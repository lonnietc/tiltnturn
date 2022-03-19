// myextension.cpp
// Extension lib defines
#define LIB_NAME "MyExtension"
#define MODULE_NAME "myextension"

// include the Defold SDK
#include <dmsdk/sdk.h>

static int MyToken(lua_State* L)
{
    // The number of expected items to be on the Lua stack
    // once this struct goes out of scope
    DM_LUA_STACK_CHECK(L, 1);

    // Put the string on the stack
    lua_pushstring(L, "THIS_IS_32_BYTES_LONG_STRINGGGGG");

    // Return 1 item
    return 1;
}

// Functions exposed to Lua
static const luaL_reg Module_methods[] =
{
    {"my_token", MyToken},
    {0, 0}
};

static void LuaInit(lua_State* L)
{
    int top = lua_gettop(L);

    // Register lua names
    luaL_register(L, MODULE_NAME, Module_methods);

    lua_pop(L, 1);
    assert(top == lua_gettop(L));
}

static dmExtension::Result InitializeMyExtension(dmExtension::Params* params)
{
    // Init Lua
    LuaInit(params->m_L);
    return dmExtension::RESULT_OK;
}

static dmExtension::Result FinalizeMyExtension(dmExtension::Params* params)
{
    return dmExtension::RESULT_OK;
}

// Defold SDK uses a macro for setting up extension entry points:
//
// DM_DECLARE_EXTENSION(symbol, name, app_init, app_final, init, update, on_event, final)

// MyExtension is the C++ symbol that holds all relevant extension data.
// It must match the name field in the `ext.manifest`
DM_DECLARE_EXTENSION(MyExtension, LIB_NAME, 0, 0, InitializeMyExtension, 0, 0, FinalizeMyExtension)
