package com.zspirytus.androidlua

import android.content.pm.PackageManager
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.os.Environment
import android.support.v4.app.ActivityCompat
import android.util.Log
import kotlinx.android.synthetic.main.activity_main.*
import java.io.File
import java.io.FileInputStream

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        requestPermission(android.Manifest.permission.WRITE_EXTERNAL_STORAGE)
    }

    private fun readScript(): String {
        val sb = StringBuilder()
        val fis = FileInputStream(File(Environment.getExternalStorageDirectory(), "test.lua"))
        var len: Int
        val buf = ByteArray(512)
        while (true) {
            len = fis.read(buf)
            if (len != -1) {
                sb.append(String(buf, 0, len))
            } else {
                break
            }
        }
        return sb.toString()
    }

    private fun requestPermission(vararg permissions: String) {
        ActivityCompat.requestPermissions(this, permissions, REQUEST_CODE)
    }

    override fun onRequestPermissionsResult(requestCode: Int, permissions: Array<out String>, grantResults: IntArray) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults)
        if (requestCode == REQUEST_CODE) {
            if (grantResults.isNotEmpty() && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                start_btn.setOnClickListener {
                    Thread(Runnable { Log.d(TAG, "startScript: ${startScript(readScript())} isScriptRunning: ${isScriptRunning()}") }).start()
                }
                stop_btn.setOnClickListener {
                    Thread(Runnable { Log.d(TAG, "stopScript: ${stopScript()} isScriptRunning: ${isScriptRunning()}") }).start()
                }
            }
        }
    }

    private external fun startScript(luaString: String): Boolean
    private external fun stopScript(): Boolean
    private external fun isScriptRunning(): Boolean

    companion object {
        private const val TAG = "MainActivity"
        private const val REQUEST_CODE = 233

        init {
            System.loadLibrary("luabridge")
        }
    }
}
