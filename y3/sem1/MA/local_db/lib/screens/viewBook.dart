import 'package:local_db/model/Book.dart';
import 'package:flutter/material.dart';

class ViewBook extends StatefulWidget {
  final Book book;

  const ViewBook({Key? key, required this.book}) : super(key: key);

  @override
  State<ViewBook> createState() => _ViewBookState();
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

class _ViewBookState extends State<ViewBook> {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
        appBar: AppBar(
          title: const Text("Full Details"),
        ),
        body: Container(
          padding: EdgeInsets.all(16.0),
          child: Column(
            crossAxisAlignment: CrossAxisAlignment.start,
            children: [
              Row(
                children: [
                  const Text('Title',
                      style: TextStyle(
                          color: Color(0xFF244A73),
                          fontSize: 16,
                          fontWeight: FontWeight.w600)),
                  Padding(
                    padding: const EdgeInsets.only(left: 25),
                    child: Text(widget.book.title ?? '', style: TextStyle(fontSize: 16)),
                  ),
                ],
              ),
              const SizedBox(
                height: 20,
              ),
              Row(
                children: [
                  const Text('Author',
                      style: TextStyle(
                          color: Color(0xFF244A73),
                          fontSize: 16,
                          fontWeight: FontWeight.w600)),
                  Padding(
                    padding: const EdgeInsets.only(left: 25),
                    child: Text(widget.book.author ?? '', style: TextStyle(fontSize: 16)),
                  ),
                ],
              ),
              const SizedBox(
                height: 20,
              ),
              Row(
                crossAxisAlignment: CrossAxisAlignment.start,
                children: [
                  const Text('Format',
                      style: TextStyle(
                          color: Color(0xFF244A73),
                          fontSize: 16,
                          fontWeight: FontWeight.w600)),
                  const SizedBox(
                    height: 20,
                  ),
                  Padding(
                    padding: const EdgeInsets.only(left: 25),
                    child: Text(widget.book.format ?? '', style: TextStyle(fontSize: 16)),
                  ),
                ],
              ),
              const SizedBox(
                height: 20,
              ),
              Row(
                crossAxisAlignment: CrossAxisAlignment.start,
                children: [
                  const Text('Status',
                      style: TextStyle(
                          color: Color(0xFF244A73),
                          fontSize: 16,
                          fontWeight: FontWeight.w600)),
                  const SizedBox(
                    height: 20,
                  ),
                  Padding(
                    padding: const EdgeInsets.only(left: 25),
                    child: Text(widget.book.status ?? '', style: TextStyle(
                        fontSize: 16,
                        color: _getStatusColor(widget.book.status))),
                  ),
                ],
              ),
              const SizedBox(
                height: 20,
              ),
              Column(
                crossAxisAlignment: CrossAxisAlignment.start,
                children: [
                  const Text('Review',
                      style: TextStyle(
                          color: Color(0xFF244A73),
                          fontSize: 16,
                          fontWeight: FontWeight.w600)),
                  const SizedBox(
                    height: 20,
                  ),
                  Text(widget.book.review ?? '', style: const TextStyle(fontSize: 16)),
                ],
              )
            ],
          ),
        ));
  }
}