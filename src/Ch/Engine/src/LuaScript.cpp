
#include "LuaScript.h"

namespace Advanced2D
{

LuaScript::LuaScript()
{
#if LUA_VERSION_NUM < 501
	mLuaState = lua_open();
#else
	mLuaState = luaL_newstate();
#endif
	luaL_openlibs(mLuaState);
}

LuaScript::~LuaScript()
{
	lua_close(mLuaState);
}

bool LuaScript::loadScript(const char* szScriptFile)
{
	return luaL_dofile(mLuaState, szScriptFile) ? false : true;
}

const char* LuaScript::getGlobalString(const char* szName)
{
	lua_getglobal(mLuaState, szName);
	const char* szValue = lua_tostring(mLuaState, -1);
	lua_pop(mLuaState, 1);
	return szValue;
}

void LuaScript::setGlobalString(const char* szName, const char* szValue)
{
	lua_pushstring(mLuaState, szValue);
	lua_setglobal(mLuaState, szName);
}

double LuaScript::getGlobalNumber(const char* szName)
{
	lua_getglobal(mLuaState, szName);
	double dValue = lua_tonumber(mLuaState, -1);
	lua_pop(mLuaState, 1);
	return dValue;
}

void LuaScript::setGlobalNumber(const char* szName, double dValue)
{
	lua_pushnumber(mLuaState, dValue);
	lua_setglobal(mLuaState, szName);
}

bool LuaScript::getGlobalBoolean(const char* szName)
{
	lua_getglobal(mLuaState, szName);
	bool bValue = lua_toboolean(mLuaState, -1) ? true : false;
	lua_pop(mLuaState, 1);
	return bValue;
}

void LuaScript::setGlobalBoolean(const char* szName, bool bValue)
{
	lua_pushboolean(mLuaState, static_cast<int>(bValue));
	lua_setglobal(mLuaState, szName);
}

void LuaScript::runFunction(const char* szName)
{
	lua_getglobal(mLuaState, szName);
	lua_call(mLuaState, 0, 0);
}

}
