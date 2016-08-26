package cc.openframeworks.bapaMockAndroid

import android.content.Context

/**
 * Created by Ryota Niinomi on 2016/08/27.
 */
class PrefUtil {
    companion object {
        val DRAWER = "drawer_pref"
        val DRAWER_KEY_IS_DEBUG_MODE = "is_debug_mode"

        fun isDebugMode(context: Context): Boolean {
            val pref = context.getSharedPreferences(DRAWER, Context.MODE_PRIVATE)
            return pref.getBoolean(DRAWER_KEY_IS_DEBUG_MODE, false)
        }

        fun setDebugMode(context: Context, isDebugMode: Boolean) {
            val pref = context.getSharedPreferences(DRAWER, Context.MODE_PRIVATE)
            pref.edit().putBoolean(DRAWER_KEY_IS_DEBUG_MODE, isDebugMode).commit()
        }
    }
}