package com.example.myapp.activity

import android.os.Bundle
import android.widget.Toast
import androidx.activity.ComponentActivity
import com.example.myapp.databinding.AddBinding
import com.example.myapp.model.BookModel

class AddActivity: ComponentActivity(){
    lateinit var addBinding: AddBinding

    override fun onCreate(savedInstanceState: Bundle?){
        super.onCreate(savedInstanceState)

        addBinding = AddBinding.inflate(layoutInflater)
        setContentView(addBinding.root)

        addBinding.addButton.setOnClickListener{
            if(checkInputs()){
                val book = BookModel(
                    bookTitle = addBinding.bookTitle.text.toString(),
                    author = addBinding.author.text.toString(),
                    format = addBinding.format.text.toString(),
                    status = addBinding.status.text.toString(),
                    review = addBinding.review.text.toString()
                )
                val bundle = Bundle()
                bundle.putSerializable("book", book)
                intent.putExtra("bookBundle", bundle)
                setResult(RESULT_OK, intent)
                finish()
            }else{
                Toast.makeText(
                    this,
                    "All fields must be completed",
                    Toast.LENGTH_LONG
                ).show()
            }
        }

        addBinding.noButton.setOnClickListener {
            setResult(RESULT_CANCELED)
            finish()
        }
    }

    private fun checkInputs(): Boolean{
        return !addBinding.bookTitle.text.isNullOrEmpty() &&
                !addBinding.author.text.isNullOrEmpty() &&
                !addBinding.format.text.isNullOrEmpty() &&
                !addBinding.status.text.isNullOrEmpty() &&
                !addBinding.review.text.isNullOrEmpty()
    }
}