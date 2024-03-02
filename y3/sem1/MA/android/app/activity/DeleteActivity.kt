package com.example.myapp.activity

import android.content.Intent
import android.os.Bundle
import androidx.activity.ComponentActivity
import com.example.myapp.databinding.DeleteBinding
import com.example.myapp.model.BookModel

class DeleteActivity : ComponentActivity(){
    lateinit var deleteBinding: DeleteBinding
    lateinit var initialBook: BookModel

    override fun onCreate(savedInstanceState: Bundle?){
        super.onCreate(savedInstanceState)

        deleteBinding = DeleteBinding.inflate(layoutInflater)
        setContentView(deleteBinding.root)

        val bundle = intent.getBundleExtra("bookBundle")
        val position = bundle?.getInt("position")

        if(position != null){
            deleteBinding.bookId.text = "Delete book at position: $position"

            deleteBinding.yesButton.setOnClickListener{
                val resultBundle = Bundle()
                resultBundle.putInt("toDelete", position)
                val resultIntent = Intent()
                resultIntent.putExtra("deleteResponse", resultBundle)
                setResult(RESULT_OK, resultIntent)
                finish()
            }

            deleteBinding.noButton.setOnClickListener{
                setResult(RESULT_CANCELED)
                finish()
            }
        }
    }
}