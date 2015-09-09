#ifndef __LUA_SCRIPT_H_
#define __LUA_SCRIPT_H_

#include "lua.hpp"

namespace Advanced2D
{
class LuaScript
{
private:
	lua_State* mLuaState;
public:
	LuaScript();
	virtual ~LuaScript();

	bool loadScript(const char* szScriptFile);

	const char* getGlobalString(const char* szName);
	void setGlobalString(const char* szName, const char* szValue);

	double getGlobalNumber(const char* szName);
	void setGlobalNumber(const char* szName, double dValue);

	bool getGlobalBoolean(const char* szName);
	void setGlobalBoolean(const char* szName, bool bValue);

	void runFunction(const char* szName);
};
}

#endif
