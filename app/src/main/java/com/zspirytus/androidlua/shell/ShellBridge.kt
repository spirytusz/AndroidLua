package com.zspirytus.androidlua.shell

import android.support.annotation.Keep

@Keep
object ShellBridge {

    @Keep
    @JvmStatic
    fun getStringFromKotlinLayer(): String {
        return "Hello World From Kotlin Layer"
    }
}