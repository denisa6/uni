package com.example.myapp.model

import java.io.Serializable

data class BookModel(
    var bookTitle: String,
    var author: String,
    var format: String,
    var status: String,
    var review: String
) : Serializable {

    fun getId(): Pair<String, String> {
        return Pair(bookTitle, author)
    }
}