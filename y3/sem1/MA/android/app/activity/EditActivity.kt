package com.example.myapp.activity

import android.content.Intent
import android.os.Bundle
import androidx.activity.ComponentActivity
import com.example.myapp.databinding.EditBinding
import com.example.myapp.model.BookModel

class EditActivity : ComponentActivity() {
    private lateinit var editBinding: EditBinding
    private lateinit var initialBook: BookModel

    override fun onCreate(savedInstanceState: Bundle?){
        super.onCreate(savedInstanceState)
        editBinding = EditBinding.inflate(layoutInflater)
        setContentView(editBinding.root)

        val bundle = intent.getBundleExtra("bookBundle")
        val initialBook = bundle?.getSerializable("book", BookModel::class.java) as? BookModel
        if (initialBook != null) {
            editBinding.bookTitle.setText(initialBook.bookTitle)
            editBinding.author.setText(initialBook.author)
            editBinding.format.setText(initialBook.format)
            editBinding.status.setText(initialBook.status)
            editBinding.review.setText(initialBook.review)

            editBinding.editButton.setOnClickListener {
                if (checkInputs()) {
                    val updatedBook = BookModel(
                        bookTitle = editBinding.bookTitle.text.toString(),
                        author = editBinding.author.text.toString(),
                        format = editBinding.format.text.toString(),
                        status = editBinding.status.text.toString(),
                        review = editBinding.review.text.toString()
                    )

                    val resultIntent = Intent()
                    val resultBundle = Bundle()
                    resultBundle.putSerializable("updatedBook", updatedBook)
                    resultBundle.putInt("position", bundle.getInt("position"))
                    resultIntent.putExtra("updateResponse", resultBundle)
                    setResult(RESULT_OK, resultIntent)
                    finish()
                }
            }

            editBinding.noEditButton.setOnClickListener{
                setResult(RESULT_CANCELED)
                finish()
            }
        }
    }

    private fun checkInputs(): Boolean {
        if (
            editBinding.status.text.isEmpty() ||
            editBinding.review.text.isEmpty()
        ) {
            return false
        }
        return true
    }
}