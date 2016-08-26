package com.nomi.artwatch.ui.activity

import android.content.res.Configuration
import android.os.Bundle
import android.support.v4.widget.DrawerLayout
import android.support.v7.app.ActionBarDrawerToggle
import android.support.v7.app.AppCompatActivity
import android.support.v7.widget.Toolbar
import android.view.Menu
import android.view.MenuItem
import android.view.View
import android.view.ViewGroup
import butterknife.bindView
import cc.openframeworks.bapaMockAndroid.PrefUtil
import cc.openframeworks.bapaMockAndroid.R
import kotlinx.android.synthetic.main.drawer_activity.*

/**
 * Created by Ryota Niinomi on 16/08/27.
 */
abstract class DrawerActivity : AppCompatActivity() {

    private var mDrawerToggle: ActionBarDrawerToggle? = null

    val mDrawerLayout: DrawerLayout by bindView(R.id.drawer_layout)
    val mContainer: ViewGroup by bindView(R.id.container)

    protected abstract val layout: Int
    protected abstract val toolbarName: Int

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.drawer_activity)

        if (layout != 0) {
            layoutInflater.inflate(layout, mContainer)
        }

        initDrawer()
    }

    override fun onPostCreate(savedInstanceState: Bundle?) {
        super.onPostCreate(savedInstanceState)

        mDrawerToggle!!.syncState()
    }

    override fun onConfigurationChanged(newConfig: Configuration) {
        super.onConfigurationChanged(newConfig)

        mDrawerToggle!!.onConfigurationChanged(newConfig)
    }

    override fun onCreateOptionsMenu(menu: Menu): Boolean {
        return super.onCreateOptionsMenu(menu)
    }

    override fun onOptionsItemSelected(item: MenuItem): Boolean {
        if (mDrawerToggle!!.onOptionsItemSelected(item)) {
            return true
        }

        return super.onOptionsItemSelected(item)
    }

    private fun initDrawer() {
        val toolbar = findViewById(R.id.toolbar) as Toolbar
        setSupportActionBar(toolbar)

        mDrawerToggle = object : ActionBarDrawerToggle(
                this,
                mDrawerLayout,
                toolbarName,
                toolbarName) {
            override fun onDrawerClosed(view: View?) {
                super.onDrawerClosed(view)
            }

            override fun onDrawerOpened(drawerView: View?) {
                super.onDrawerOpened(drawerView)
            }
        }

        mDrawerLayout.setDrawerListener(mDrawerToggle)
        mDrawerToggle!!.isDrawerIndicatorEnabled = true

        supportActionBar!!.setDisplayHomeAsUpEnabled(true)
        supportActionBar!!.setHomeButtonEnabled(true)

        debugBtn.isChecked = PrefUtil.isDebugMode(applicationContext)
        debugBtn.setOnClickListener {
            PrefUtil.setDebugMode(applicationContext, debugBtn.isChecked)
        }
    }
}
