package cc.openframeworks.bapaMockAndroid

import android.content.Context
import android.content.Intent
import android.os.Bundle
import android.support.v7.app.AppCompatActivity
import android.support.v7.widget.LinearLayoutManager
import com.crashlytics.android.Crashlytics
import io.fabric.sdk.android.Fabric
import kotlinx.android.synthetic.main.main_activity.*
import java.util.*

/**
 * Created by Ryota Niinomi on 2016/07/17.
 */
class MainActivity : AppCompatActivity() {

    companion object {
        fun createIntent(context: Context): Intent {
            val intent = Intent(context, MainActivity::class.java)
            return intent
        }
    }

    var adapter : GraphicItemAdapter? = null;

    val listener : GraphicItemAdapter.Listener = object : GraphicItemAdapter.Listener {
        override fun onClick(item: GraphicItem) {
            startActivity(OFActivity.createIntent(this@MainActivity, item.id))
        }
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        Fabric.with(this, Crashlytics())

        setContentView(R.layout.main_activity)

        adapter = GraphicItemAdapter(createDataSet(), listener)

        recyclerView.layoutManager = LinearLayoutManager(this)
        recyclerView.adapter = adapter
    }

    fun createDataSet() : List<GraphicItem> {
        var list : MutableList<GraphicItem> = ArrayList()

        for (i in 0..10) {
            list.add(GraphicItem(i, "example_" + i))
        }

        return list;
    }
}