package com.zspirytus.androidlua.engine

import com.zspirytus.androidlua.utils.ZipFileUtils
import java.io.File
import java.util.zip.ZipFile

class ScriptPkgDataFetcher(private var scriptPkg: File) {

    fun getContentByEntryName(entryName: String): ByteArray {
        return ZipFileUtils.getFileContentFromZipFile(ZipFile(scriptPkg), entryName).toByteArray()
    }
}