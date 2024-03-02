import 'package:local_db/model/Book.dart';
import 'package:local_db/service/bookService.dart';
import 'package:flutter/material.dart';
class EditBook extends StatefulWidget {
  final Book book;
  const EditBook({Key? key,required this.book}) : super(key: key);

  @override
  State<EditBook> createState() => _EditBookState();
}

class _EditBookState extends State<EditBook> {
  var _bookTitleController = TextEditingController();
  var _bookAuthorController = TextEditingController();
  var _bookFormatController = TextEditingController();
  var _bookStatusController = TextEditingController();
  var _bookReviewController = TextEditingController();
  bool _validateTitle = false;
  bool _validateAuthor = false;
  bool _validateFormat = false;
  bool _validateStatus = false;
  var _bookService=BookService();

  @override
  void initState() {
    setState(() {
      _bookTitleController.text=widget.book.title??'';
      _bookAuthorController.text=widget.book.author??'';
      _bookFormatController.text=widget.book.format??'';
      _bookStatusController.text=widget.book.status??'';
      _bookReviewController.text=widget.book.review??'';
    });
    super.initState();
  }
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text("Edit Book Details"),
      ),
      body: SingleChildScrollView(
        child: Container(
          padding: const EdgeInsets.all(16.0),
          child: Column(
            crossAxisAlignment: CrossAxisAlignment.start,
            children: [
              TextField(
                  controller: _bookTitleController,
                  decoration: InputDecoration(
                    border: const OutlineInputBorder(),
                    hintText: 'Enter Title',
                    labelText: 'Title',
                    errorText:
                    _validateTitle ? 'Title Value Can\'t Be Empty' : null,
                  )),
              const SizedBox(
                height: 20.0,
              ),
              TextField(
                  controller: _bookAuthorController,
                  decoration: InputDecoration(
                    border: const OutlineInputBorder(),
                    hintText: 'Enter Author',
                    labelText: 'Author',
                    errorText: _validateAuthor
                        ? 'Contact Author Can\'t Be Empty'
                        : null,
                  )),
              const SizedBox(
                height: 20.0,
              ),
              TextField(
                  controller: _bookFormatController,
                  decoration: InputDecoration(
                    border: const OutlineInputBorder(),
                    hintText: 'Enter Format',
                    labelText: 'Format',
                    errorText: _validateFormat
                        ? 'Format Value Can\'t Be Empty'
                        : null,
                  )),
              const SizedBox(
                height: 20.0,
              ),
              TextField(
                  controller: _bookStatusController,
                  decoration: InputDecoration(
                    border: const OutlineInputBorder(),
                    hintText: 'Enter Status',
                    labelText: 'Status',
                    errorText: _validateStatus
                        ? 'Status Value Can\'t Be Empty'
                        : null,
                  )),
              const SizedBox(
                height: 20.0,
              ),
              TextField(
                  controller: _bookReviewController,
                  decoration: const InputDecoration(
                    border: OutlineInputBorder(),
                    hintText: 'Enter Review',
                    labelText: 'Review',
                  )),
              const SizedBox(
                height: 20.0,
              ),
              Row(
                children: [
                  TextButton(
                      style: TextButton.styleFrom(
                          primary: Colors.white,
                          backgroundColor: const Color(0xFF244A73),
                          textStyle: const TextStyle(fontSize: 15)),
                      onPressed: () async {
                        setState(() {
                          _bookTitleController.text.isEmpty
                              ? _validateTitle = true
                              : _validateTitle = false;
                          _bookAuthorController.text.isEmpty
                              ? _validateAuthor = true
                              : _validateAuthor = false;
                          _bookFormatController.text.isEmpty
                              ? _validateFormat = true
                              : _validateFormat = false;
                          _bookStatusController.text.isEmpty
                              ? _validateStatus = true
                              : _validateStatus = false;
                        });
                        if (_validateTitle == false &&
                            _validateAuthor == false &&
                            _validateFormat == false &&
                            _validateStatus == false) {
                          // print("Good Data Can Save");
                          var _book = Book();
                          _book.id=widget.book.id;
                          _book.title = _bookTitleController.text;
                          _book.author = _bookAuthorController.text;
                          _book.format = _bookFormatController.text;
                          _book.status = _bookStatusController.text;
                          _book.review = _bookReviewController.text;
                          var result=await _bookService.updateBook(_book);
                          Navigator.pop(context,result);
                        }
                      },
                      child: const Text('Update Details')),
                  const SizedBox(
                    width: 10.0,
                  ),
                  TextButton(
                      style: TextButton.styleFrom(
                          primary: Colors.white,
                          backgroundColor: Colors.red,
                          textStyle: const TextStyle(fontSize: 15)),
                      onPressed: () {
                        _bookTitleController.text = '';
                        _bookAuthorController.text = '';
                        _bookFormatController.text = '';
                        _bookStatusController.text = '';
                        _bookReviewController.text = '';
                      },
                      child: const Text('Clear Details'))
                ],
              )
            ],
          ),
        ),
      ),
    );
  }
}