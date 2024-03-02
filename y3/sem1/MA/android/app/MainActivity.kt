package com.example.myapp

import android.app.Activity
import android.content.Intent
import android.os.Bundle
import android.widget.Toast
import androidx.activity.ComponentActivity
import androidx.activity.result.ActivityResultLauncher
import androidx.activity.result.contract.ActivityResultContracts
import com.example.myapp.activity.AddActivity
import com.example.myapp.adapter.BookAdapter
import com.example.myapp.model.BookModel
import androidx.recyclerview.widget.LinearLayoutManager
import com.example.myapp.databinding.MainListBinding

class MainActivity : ComponentActivity() {
    private val books = mutableListOf<BookModel>()

    private fun initBooks() {
        books.add(
            BookModel(
                bookTitle = "book1",
                author = "author1",
                format = "ebook",
                status = "read",
                review = "good"
            )
        )

        books.add(
            BookModel(
                bookTitle = "book2",
                author = "author2",
                format = "physical",
                status = "reading",
                review = "great"
            )
        )

        books.add(
            BookModel(
                bookTitle = "book3",
                author = "author3",
                format = "ebook",
                status = "not read",
                review = "amazing"
            )
        )
    }

    lateinit var addActivityLauncher: ActivityResultLauncher<Intent>
    lateinit var editActivityLauncher: ActivityResultLauncher<Intent>
    lateinit var deleteActivityLauncher: ActivityResultLauncher<Intent>

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        initBooks()
        val listBindings = MainListBinding.inflate(layoutInflater)

        addActivityLauncher = registerForActivityResult(ActivityResultContracts.StartActivityForResult()) { result ->
            if (result.resultCode == Activity.RESULT_OK) {
                val book = result.data?.getBundleExtra("bookBundle")?.getSerializable("book", BookModel::class.java)
                if (book != null) {
                    if (books.find { repoBook -> repoBook.getId() == book.getId() } != null) {
                        Toast.makeText(
                            this,
                            "Book already exists",
                            Toast.LENGTH_LONG
                        ).show()
                    } else {
                        books.add(book)
                        listBindings.recyclerView.adapter?.notifyItemInserted(books.size - 1)
                    }
                }
            }
        }

        editActivityLauncher = registerForActivityResult(ActivityResultContracts.StartActivityForResult()) { result ->
            if (result.resultCode == Activity.RESULT_OK) {
                var book = result.data?.getBundleExtra("updateResponse")?.getSerializable("updatedBook", BookModel::class.java)
                val position = result.data?.getBundleExtra("updateResponse")?.getInt("position")


                if (book != null && position != null){
                    books[position] = book
                    listBindings.recyclerView.adapter?.notifyItemChanged(position)
                }
            }
        }

        deleteActivityLauncher = registerForActivityResult(ActivityResultContracts.StartActivityForResult()) { result ->
            if(result.resultCode == Activity.RESULT_OK) {
                val bundle = result.data?.getBundleExtra("deleteResponse")!!

                if (bundle.containsKey("toDelete")) {
                    val position = bundle.getInt("toDelete")
                    books.removeAt(position)
                    listBindings.recyclerView.adapter?.notifyItemRemoved(position)
                }
            }
        }

        listBindings.addButton.setOnClickListener {
            val intent = Intent(applicationContext, AddActivity::class.java)
            addActivityLauncher.launch(intent)
        }
        val adapter = BookAdapter(this, books, editActivityLauncher, deleteActivityLauncher)
        listBindings.recyclerView.layoutManager = LinearLayoutManager(this)
        listBindings.recyclerView.adapter = adapter

        setContentView(listBindings.root)
    }
}