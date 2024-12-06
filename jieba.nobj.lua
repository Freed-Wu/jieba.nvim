-- luacheck: ignore 113
---@diagnostic disable: undefined-global
c_module "jieba" {
    use_globals = true,
    include "stdlib.h",
    include "jieba.h",
    c_function "init" {
        c_call "void" "init" { "jieba_path_t", "jieba_path" },
        c_call "void" "deinit" {},
        c_call "char **" "cut" { "char *", "str", "bool", "hmm" },
    }
}
