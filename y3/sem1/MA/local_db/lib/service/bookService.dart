import 'dart:async';
import 'package:local_db/repository/repository.dart';
import 'package:local_db/model/Book.dart';

class BookService
{
  late Repository _repository;
  BookService(){
    _repository = Repository();
  }
  //Save Book
  saveBook(Book user) async{
    return await _repository.insertData('books', user.userMap());
  }
  //Read All Books
  readAllBooks() async{
    return await _repository.readData('books');
  }
  //Edit Book
  updateBook(Book user) async{
    return await _repository.updateData('books', user.userMap());
  }

  deleteBook(userId) async {
    return await _repository.deleteDataById('books', userId);
  }

}