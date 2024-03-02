import 'package:local_db/model/Book.dart';
import 'package:local_db/screens/editBook.dart';
import 'package:local_db/screens/addBook.dart';
import 'package:local_db/screens/viewBook.dart';
import 'package:local_db/service/bookService.dart';
import 'package:flutter/material.dart';

void main() {
  runApp(const MyApp());
}

void showFlashError(BuildContext context, String message) {
  ScaffoldMessenger.of(context).showSnackBar(
    SnackBar(
      content: Text(message),
    ),
  );
}

Color _getStatusColor(String? status) {
  switch (status) {
    case 'read':
      return Colors.green;
    case 'reading':
      return Colors.orangeAccent;
    case 'not read':
      return Colors.red;
    default:
      return Colors.black; // Set a default color or handle other cases as needed
  }
}

class MyApp extends StatelessWidget {
  const MyApp({Key? key}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Flutter Demo',
      debugShowCheckedModeBanner: false,
      theme: ThemeData(
        primarySwatch: Colors.indigo,
      ),
      home: const MyHomePage(),
    );
  }
}

class MyHomePage extends StatefulWidget {
  const MyHomePage({Key? key}) : super(key: key);

  @override
  State<MyHomePage> createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  late List<Book> _bookList = <Book>[];
  final _bookService = BookService();

  getAllBookDetails() async {
    try{
      var books = await _bookService.readAllBooks();
      _bookList = <Book>[];
      books.forEach((book) {
        setState(() {
          var bookModel = Book();
          bookModel.id = book['id'];
          bookModel.title = book['title'];
          bookModel.author = book['author'];
          bookModel.format = book['format'];
          bookModel.status = book['status'];
          bookModel.review = book['review'];
          _bookList.add(bookModel);
        });
      });} catch(error) {
      showFlashError(context, error.toString());
    }
  }

  @override
  void initState() {
    getAllBookDetails();
    super.initState();
  }

  _showSuccessSnackBar(String message) {
    ScaffoldMessenger.of(context).showSnackBar(
      SnackBar(
        content: Text(message),
      ),
    );
  }

  _deleteFormDialog(BuildContext context, userId) {
    return showDialog(
        context: context,
        builder: (param) {
          return AlertDialog(
            title: const Text(
              'Are You Sure You Want To Delete',
              style: TextStyle(color: Color(0xFF244A73), fontSize: 20),
            ),
            actions: [
              TextButton(
                  style: TextButton.styleFrom(
                      primary: Colors.white, // foreground
                      backgroundColor: Colors.red),
                  onPressed: ()  async{
                    try {
                      var result = await _bookService.deleteBook(userId);
                      if (result != null) {
                        Navigator.pop(context);
                        getAllBookDetails();
                        _showSuccessSnackBar(
                            'Book Detail Deleted Success');
                      }
                    } catch (error) {
                      showFlashError(context, error.toString());
                    }
                  },
                  child: const Text('Delete')),
              TextButton(
                  style: TextButton.styleFrom(
                      primary: Colors.white, // foreground
                      backgroundColor: const Color(0xFF244A73)),
                  onPressed: () {
                    Navigator.pop(context);
                  },
                  child: const Text('Close'))
            ],
          );
        });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text("Virtual Library ⭐", style: TextStyle(color: Colors.white)),
        backgroundColor: const Color(0xFF244A73),
      ),
      body: ListView.builder(
          itemCount: _bookList.length,
          itemBuilder: (context, index) {
            return Card(
              child: ListTile(
                onTap: () {
                  Navigator.push(
                      context,
                      MaterialPageRoute(
                          builder: (context) => ViewBook(
                            book: _bookList[index],
                          )));
                },
                title: Text(_bookList[index].title ?? ''),
                subtitle:
                Column(
                  crossAxisAlignment: CrossAxisAlignment.start,
                  children: [
                    Text(_bookList[index].author ?? ''),
                    Text(_bookList[index].status ?? '', style: TextStyle(
                        color: _getStatusColor(_bookList[index].status)))
                  ],
                ),
                trailing: Row(
                  mainAxisSize: MainAxisSize.min,
                  children: [
                    IconButton(
                        onPressed: () {
                          Navigator.push(
                              context,
                              MaterialPageRoute(
                                  builder: (context) => EditBook(
                                    book: _bookList[index],
                                  ))).then((data) {
                            if (data != null) {
                              getAllBookDetails();
                              _showSuccessSnackBar(
                                  'Book Detail Updated Success');
                            }
                          }).catchError((error) {
                            showFlashError(context, error.toString());
                          });
                          ;
                        },
                        icon: const Icon(
                          Icons.edit,
                          color: Color(0xFF244A73),
                        )),
                    IconButton(
                        onPressed: () {
                          _deleteFormDialog(context, _bookList[index].id);
                        },
                        icon: const Icon(
                          Icons.delete,
                          color: Colors.red,
                        ))
                  ],
                ),
              ),
            );
          }),
      floatingActionButton: FloatingActionButton(
        onPressed: () {
          Navigator.push(context,
              MaterialPageRoute(builder: (context) => const AddBook()))
              .then((data) {
            if (data != null) {
              getAllBookDetails();
              _showSuccessSnackBar('Book Detail Added Success');
            }
          }).catchError((error) {
            showFlashError(context, error.toString());
          });
        },
        backgroundColor: const Color(0xFF244A73),
        child: const Icon(
          Icons.add,
          color: Colors.white,
        ),
      ),
    );
  }
}