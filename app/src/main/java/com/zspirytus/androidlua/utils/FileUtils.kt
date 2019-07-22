package com.zspirytus.androidlua.utils

import java.io.BufferedReader
import java.io.File
import java.io.FileInputStream
import java.io.InputStream

object FileUtils {

    fun readInputStream(ins: InputStream): String {
        return ins.bufferedReader().use(BufferedReader::readText)
    }

    fun readFile(file: File): String {
        return readInputStream(FileInputStream(file))
    }
}