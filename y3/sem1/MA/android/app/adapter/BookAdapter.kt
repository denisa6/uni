package com.example.myapp.adapter

import android.annotation.SuppressLint
import android.content.Intent
import android.os.Bundle
import android.text.Spannable
import android.text.SpannableString
import android.text.style.ForegroundColorSpan
import android.view.LayoutInflater
import android.view.ViewGroup
import androidx.activity.result.ActivityResultLauncher
import androidx.compose.ui.graphics.Color
import androidx.core.content.ContextCompat
import androidx.recyclerview.widget.RecyclerView
import com.example.myapp.MainActivity
import com.example.myapp.R
import com.example.myapp.activity.DeleteActivity
import com.example.myapp.activity.EditActivity
import com.example.myapp.databinding.ListItemBinding
import com.example.myapp.model.BookModel
import com.example.myapp.ui.theme.Purple80

class BookAdapter(
    private val context: MainActivity,
    private val books: MutableList<BookModel>,
    private val editActivityLauncher: ActivityResultLauncher<Intent>,
    private val deleteActivityLauncher: ActivityResultLauncher<Intent>
): RecyclerView.Adapter<BookAdapter.BookViewHolder>(){
    inner class BookViewHolder(val itemBinding: ListItemBinding) : RecyclerView.ViewHolder(itemBinding.root){
        /*
        @SuppressLint("SetTextI18n")
        fun bind(book : BookModel, position: Int){
            itemBinding.description.text = (position + 1).toString() + ". " +
                    book.bookTitle + "\n" + book.author +
                    "\n" + book.format + "\n" + book.status. +
                    "\n" + book.review
        }
        @SuppressLint("SetTextI18n")
        fun bind(book: BookModel, position: Int) {
            val status = book.status
            val statusText = "${position + 1}. " +
                    "${book.bookTitle}\n${book.author}\n${book.format}\n${book.review}"

            val statusColor = if (status == "read") {
                ContextCompat.getColor(context, android.R.color.holo_green_dark) // Replace R.color.green with your green color resource
            } else if (status == "not read") {
                ContextCompat.getColor(context, android.R.color.holo_red_dark) // Replace R.color.red with your red color resource
            } else {
                ContextCompat.getColor(context, android.R.color.black) // Default to black color
            }

            itemBinding.apply {
                description.text = statusText
                description.setTextColor(statusColor)
            }
        }*/
        @SuppressLint("SetTextI18n")
        fun bind(book: BookModel, position: Int) {
            val status = book.status
            val statusText = "${position + 1}. " +
                    "${book.bookTitle}\n${book.author}\n${book.format}\n${book.status}\n${book.review}"

            val statusColor = when (status) {
                "read" -> ContextCompat.getColor(context, android.R.color.holo_green_dark)
                "not read" -> ContextCompat.getColor(context, android.R.color.holo_red_dark)
                else -> ContextCompat.getColor(context, android.R.color.holo_orange_light)
            }

            val spannableString = SpannableString(statusText)
            val statusIndex = statusText.indexOf(status)

            if (statusIndex != -1) {
                spannableString.setSpan(ForegroundColorSpan(statusColor), statusIndex, statusIndex + status.length, Spannable.SPAN_EXCLUSIVE_EXCLUSIVE)
            }

            itemBinding.description.text = spannableString
        }
    }

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): BookViewHolder {
        val itemBinding = ListItemBinding.inflate(LayoutInflater.from(parent.context), parent, false)
        return BookViewHolder(itemBinding)
    }

    override fun onBindViewHolder(holder: BookViewHolder, position: Int) {
        holder.bind(books[position], position)

        holder.itemBinding.update.setOnClickListener() {
            val bundle = Bundle();
            val intent = Intent(context, EditActivity::class.java)
            bundle.putSerializable("book", books[position])
            bundle.putInt("position", position)
            intent.putExtra("bookBundle", bundle)
            editActivityLauncher.launch(intent)
        }

        holder.itemBinding.delete.setOnClickListener() {
            val bundle = Bundle();
            val intent = Intent(context, DeleteActivity::class.java)
            bundle.putSerializable("book", books[position])
            bundle.putInt("position", position)
            intent.putExtra("bookBundle", bundle)
            deleteActivityLauncher.launch(intent)
        }
    }

    override fun getItemCount(): Int {
        return books.size
    }
}