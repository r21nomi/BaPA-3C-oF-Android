package cc.openframeworks.bapaMockAndroid

import android.content.Context
import android.net.Uri

/**
 * Created by Ryota Niinomi on 2016/07/18.
 */
class ResourceUtil {
    companion object {
        fun getRoot(context: Context): String {
            return context.getResources().getString(R.string.resource_root, context.getPackageName())
        }

        fun getResourceAsUri(context: Context, res: Int): Uri {
            return Uri.parse(getRoot(context) + res);
        }

        fun getGrapicItemDrawableAsUri(context: Context, identifier: String) : Uri {
            val res = getDrawableRes(context, "graphic_item_", identifier)
            return getResourceAsUri(context, res)
        }

        fun getDrawableRes(context: Context, prefix: String, identifier: String) : Int {
            return context.getResources().getIdentifier(prefix + identifier, "drawable", context.getPackageName());
        }
    }
}