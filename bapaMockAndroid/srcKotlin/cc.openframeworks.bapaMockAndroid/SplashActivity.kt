package cc.openframeworks.bapaMockAndroid

import android.os.Bundle
import android.os.Handler
import android.support.v7.app.AppCompatActivity

/**
 * Created by Ryota Niinomi on 2016/08/23.
 */
class SplashActivity : AppCompatActivity() {

    companion object {
        val LAUNCH_DELAY : Long = 1000
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        setContentView(R.layout.splash_activity)

        Handler().postDelayed({
            startActivity(MainActivity.createIntent(this@SplashActivity))
            finish()
        }, LAUNCH_DELAY)
    }
}