package com.zspirytus.androidlua.ui

import android.content.pm.PackageManager
import android.os.Bundle
import android.os.Environment
import android.support.v4.app.ActivityCompat
import android.support.v7.app.AppCompatActivity
import android.util.Log
import android.widget.Toast
import com.zspirytus.androidlua.engine.LuaExecutor
import com.zspirytus.androidlua.R
import com.zspirytus.zspermission.PermissionFragment
import kotlinx.android.synthetic.main.activity_main.*
import java.io.File

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        val permissions = arrayOf(
            android.Manifest.permission.WRITE_EXTERNAL_STORAGE
        )
        PermissionFragment.getInstance(this).requestPermission(permissions) { isGranted, deniedPermissions, _ ->
            when {
                isGranted -> onGranted()
                else -> deniedPermissions.forEach {
                    Log.e(TAG, "not grant: $it")
                }
            }
        }
    }

    private fun onGranted() {
        start_btn.setOnClickListener {
            if (!LuaExecutor.getInstance().isScriptRunning()) {
                val scriptPkg = File(Environment.getExternalStorageDirectory(), "script.zip")
                val config = "config"
                Log.d(TAG, "startScript: ${LuaExecutor.getInstance().runScriptPkg(scriptPkg, config)}" +
                    " isScriptRunning: ${LuaExecutor.getInstance().isScriptRunning()}")
            }
        }
        stop_btn.setOnClickListener {
            if (LuaExecutor.getInstance().isScriptRunning()) {
                Log.d(TAG, "stopScript: ${LuaExecutor.getInstance().stopScript()} " +
                    "isScriptRunning: ${LuaExecutor.getInstance().isScriptRunning()}")
            }
        }
    }

    companion object {
        private const val TAG = "MainActivity"
    }
}
