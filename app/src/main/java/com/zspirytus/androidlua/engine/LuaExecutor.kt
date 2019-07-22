package com.zspirytus.androidlua.engine

import com.zspirytus.androidlua.utils.ZipFileUtils
import java.io.File
import java.util.zip.ZipFile

object LuaExecutor {

    fun runScriptPkg(scriptPkg: File, configFile: String) {
        val zipFile = ZipFile(scriptPkg)
        val config = ZipFileUtils.getFileContentFromZipFile(zipFile, configFile)
        val luaScriptPaths = config.split("\r\n")
        val luaScript = ZipFileUtils.getFilesContentFromZipFile(zipFile, luaScriptPaths)
        startScript(luaScript)
    }

    fun runScript(script: String) {
        startScript(script)
    }

    private external fun startScript(luaString: String): Boolean
    external fun stopScript(): Boolean
    external fun isScriptRunning(): Boolean

    init {
        System.loadLibrary("luabridge")
    }
}