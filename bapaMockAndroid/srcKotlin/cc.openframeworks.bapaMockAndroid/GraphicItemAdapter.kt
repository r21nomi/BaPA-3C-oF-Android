package cc.openframeworks.bapaMockAndroid

import android.support.v7.widget.RecyclerView
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.ImageView
import butterknife.bindView
import com.bumptech.glide.Glide
import com.bumptech.glide.load.engine.DiskCacheStrategy

/**
 * Created by Ryota Niinomi on 2016/07/18.
 */
class GraphicItemAdapter(val dataSet : List<GraphicItem>, val listener : Listener) : RecyclerView.Adapter<GraphicItemAdapter.ViewHolder>() {

    override fun getItemCount(): Int {
        return dataSet.size
    }

    override fun onBindViewHolder(holder: ViewHolder, position: Int) {
        holder.bindItem(dataSet[position])
    }

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): ViewHolder? {
        val view = LayoutInflater.from(parent.context).inflate(R.layout.graphic_item_viewholder, parent, false)
        return ViewHolder(view, listener)
    }

    class ViewHolder(view: View, val listener : Listener) : RecyclerView.ViewHolder(view) {

        val image: ImageView by bindView(R.id.image)
        var graphicItem: GraphicItem = GraphicItem(-1, "")

        fun bindItem(item : GraphicItem) {
            val context = image.context
            Glide.with(context)
                    .load(ResourceUtil.getGrapicItemDrawableAsUri(context, item.id.toString()))
                    .diskCacheStrategy(DiskCacheStrategy.NONE)
                    .into(image)

            graphicItem = item
        }

        init {
            image.setOnClickListener {
                listener.onClick(graphicItem)
            }
        }
    }

    interface Listener {
        fun onClick(item : GraphicItem)
    }
}