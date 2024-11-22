#include <lauxlib.h>

#include "jieba.h"

static int _init(lua_State *L) {
  struct jieba_path jieba_path;
  lua_getfield(L, 1, "dict_path");
  jieba_path.dict_path = lua_tostring(L, -1);
  lua_getfield(L, 1, "model_path");
  jieba_path.model_path = lua_tostring(L, -1);
  lua_getfield(L, 1, "user_dict_path");
  jieba_path.user_dict_path = lua_tostring(L, -1);
  lua_getfield(L, 1, "idf_path");
  jieba_path.idf_path = lua_tostring(L, -1);
  lua_getfield(L, 1, "stop_word_path");
  jieba_path.stop_word_path = lua_tostring(L, -1);
  init(jieba_path);
  return 0;
}

static int _cut(lua_State *L) {
  lua_newtable(L);
  char **results = cut(lua_tostring(L, 1), lua_toboolean(L, 2));
  int i = 1;
  while (*results) {
    lua_pushstring(L, *results++);
    lua_rawseti(L, -2, i++);
  }
  return 1;
}

static const luaL_Reg functions[] = {
    {"init", _init},
    {"cut", _cut},
    {NULL, NULL},
};

int luaopen_jieba(lua_State *L) {
#if LUA_VERSION_NUM == 501
  luaL_register(L, "jieba", functions);
#else
  luaL_newlib(L, functions);
#endif
  return 1;
}