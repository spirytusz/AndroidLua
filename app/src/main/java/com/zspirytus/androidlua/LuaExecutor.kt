package com.zspirytus.androidlua

object LuaExecutor {

    external fun startScript(luaString: String): Boolean
    external fun stopScript(): Boolean
    external fun isScriptRunning(): Boolean

    init {
        System.loadLibrary("luabridge")
    }
}