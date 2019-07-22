package com.zspirytus.androidlua.engine

import com.zspirytus.androidlua.utils.ZipFileUtils
import java.io.File
import java.util.zip.ZipFile

class LuaExecutor {

    init {
        System.loadLibrary("luabridge")
    }

    var scriptDataFetcher: ScriptPkgDataFetcher? = null

    fun runScriptPkg(scriptPkg: File, configFile: String) {
        initScriptPkg(scriptPkg)
        val zipFile = ZipFile(scriptPkg)
        val config = ZipFileUtils.getFileContentFromZipFile(zipFile, configFile)
        val luaScriptPaths = config.split("\r\n")
        val luaScript = ZipFileUtils.getFilesContentFromZipFile(zipFile, luaScriptPaths)
        startScript(luaScript)
    }

    fun runScript(script: String) {
        startScript(script)
    }

    private fun initScriptPkg(scriptPkg: File) {
        scriptDataFetcher = ScriptPkgDataFetcher(scriptPkg)
    }

    private external fun startScript(luaString: String): Boolean
    external fun stopScript(): Boolean
    external fun isScriptRunning(): Boolean

    companion object {
        private val INSTANCE = LuaExecutor()

        fun getInstance(): LuaExecutor {
            return INSTANCE
        }
    }
}