package com.zspirytus.androidlua.engine

import android.os.Handler
import android.os.Looper
import android.util.Log
import com.zspirytus.androidlua.utils.ZipFileUtils
import java.io.File
import java.util.concurrent.ExecutorService
import java.util.concurrent.Executors
import java.util.zip.ZipFile

class LuaExecutor {

    var scriptDataFetcher: ScriptPkgDataFetcher? = null
    private var mHandler: Handler? = null
    private var mThreadPool: ExecutorService? = null

    init {
        System.loadLibrary("luabridge")
        mThreadPool = Executors.newSingleThreadExecutor()
        mHandler = Handler(Looper.getMainLooper())
    }

    fun runScriptPkg(scriptPkg: File, configFile: String) {
        mThreadPool?.execute {
            val start = System.currentTimeMillis()
            initScriptPkg(scriptPkg)
            val zipFile = ZipFile(scriptPkg)
            val config = ZipFileUtils.getFileContentFromZipFile(zipFile, configFile)
            val luaScriptPaths = config.split("\r\n")
            val luaScript = ZipFileUtils.getFilesContentFromZipFile(zipFile, luaScriptPaths)
            Log.d("USE_TIME", "${System.currentTimeMillis() - start} ms")
            mHandler?.post {
                startScript(luaScript)
            }
        }
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