package com.zspirytus.androidlua

object ShellBridge {

    @JvmStatic
    fun getStringFromKotlinLayer(): String {
        return "Hello World From Kotlin Layer"
    }
}