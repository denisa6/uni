
class Book {
  String title;
  String author;
  String format;
  String status;
  String review;

  Book(this.title, this.author, this.format, this.status, this.review);
}

class BookId{
  String title;
  String author;

  BookId(Book book): title = book.title, author = book.author;

  bool is_equal(BookId other){
    return title == other.title && author == other.author;
  }
}