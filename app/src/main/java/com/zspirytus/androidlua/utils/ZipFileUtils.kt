package com.zspirytus.androidlua.utils

import java.io.InputStream
import java.util.zip.ZipFile

object ZipFileUtils {

    fun getFileContentFromZipFile(zipFile: ZipFile, targetFile: String): String {
        var ins: InputStream? = null
        try {
            val ze = zipFile.getEntry(targetFile)
            return if (ze != null) {
                ins = zipFile.getInputStream(ze)
                FileUtils.readInputStream(ins)
            } else {
                ""
            }
        } finally {
            ins?.close()
        }
    }

    fun getFilesContentFromZipFile(zipFile: ZipFile, targetFiles: List<String>): String {
        val stringBuilder = StringBuilder()
        targetFiles.filter { it.isNotEmpty() and it.isNotBlank() }.forEach {
            val content = getFileContentFromZipFile(zipFile, it)
            stringBuilder.append(content).append('\n')
        }
        return stringBuilder.toString()
    }
}