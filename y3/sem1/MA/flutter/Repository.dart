
import 'package:flutter_app/Book.dart';

class Repository{
  final List<Book> books = [];

  Repository(){
    books.add(
        Book(
            "Book1",
            "Author1",
            "ebook",
            "read",
            "good"
        )
    );
    books.add(
        Book(
            "Book2",
            "Author2",
            "physical",
            "reading",
            "great"
        )
    );
    books.add(
        Book(
            "Book3",
            "Author3",
            "ebook",
            "not read",
            "amazing"
        )
    );
  }


  bool add(Book book){
    BookId bookId = BookId(book);
    for(var value in books){
      if(BookId(value).is_equal(bookId)){
        return false;
      }
    }
    books.add(book);
    return true;
  }

  bool remove(Book book){
    BookId bookId = BookId(book);
    for(var value in books){
      if(BookId(value).is_equal(bookId)){
        books.remove(book);
        return true;
      }
    }
    return false;
  }

  bool update(Book book){
    BookId bookId = BookId(book);
    for(int i = 0; i < books.length; i++){
      var value = books[i];
      if(BookId(value).is_equal(bookId)){
        books[i] = book;
        return true;
      }
    }
    return false;
  }

  List<Book> getAll(){
    return books;
  }
}