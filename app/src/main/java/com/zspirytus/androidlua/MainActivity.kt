package com.zspirytus.androidlua

import android.content.pm.PackageManager
import android.os.Bundle
import android.os.Environment
import android.support.v4.app.ActivityCompat
import android.support.v7.app.AppCompatActivity
import android.util.Log
import kotlinx.android.synthetic.main.activity_main.*
import java.io.File

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        requestPermission(android.Manifest.permission.WRITE_EXTERNAL_STORAGE)
    }

    private fun requestPermission(vararg permissions: String) {
        ActivityCompat.requestPermissions(this, permissions, REQUEST_CODE)
    }

    override fun onRequestPermissionsResult(requestCode: Int, permissions: Array<out String>, grantResults: IntArray) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults)
        if (requestCode == REQUEST_CODE) {
            if (grantResults.isNotEmpty() && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                start_btn.setOnClickListener {
                    val scriptPkg = File(Environment.getExternalStorageDirectory(), "t.zip")
                    val config = "config"
                    Log.d(TAG, "startScript: ${LuaExecutor.runScriptPkg(scriptPkg, config)} isScriptRunning: ${LuaExecutor.isScriptRunning()}")
                }
                stop_btn.setOnClickListener {
                    Log.d(TAG, "stopScript: ${LuaExecutor.stopScript()} isScriptRunning: ${LuaExecutor.isScriptRunning()}")
                }
            }
        }
    }

    companion object {
        private const val TAG = "MainActivity"
        private const val REQUEST_CODE = 233
    }
}
