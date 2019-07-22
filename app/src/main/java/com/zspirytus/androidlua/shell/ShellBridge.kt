package com.zspirytus.androidlua.shell

import android.support.annotation.Keep
import com.zspirytus.androidlua.engine.LuaExecutor

@Keep
object ShellBridge {

    private val TAG = ShellBridge.javaClass.simpleName

    @Keep
    @JvmStatic
    fun getStringFromKotlinLayer(): String {
        return "Hello World From Kotlin Layer"
    }

    @Keep
    @JvmStatic
    fun getScriptPkgData(dataPath: String): ByteArray {
        return LuaExecutor.getInstance().scriptDataFetcher?.getContentByEntryName(dataPath)
            ?: ByteArray(0)
    }
}