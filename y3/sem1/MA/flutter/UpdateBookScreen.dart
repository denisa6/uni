import 'package:flutter/material.dart';
import 'package:flutter_app/Book.dart';

class UpdateBookScreen extends StatefulWidget{
  const UpdateBookScreen({super.key, required this.book});

  final Book book;

  @override
  State<UpdateBookScreen> createState() => UpdateBookScreenState();
}

class UpdateBookScreenState extends State<UpdateBookScreen>{
  final _formKey = GlobalKey<FormState>();

  @override
  Widget build(BuildContext context){
    String title = widget.book.title;
    String author = widget.book.author;
    String format = widget.book.format;
    String status = widget.book.status;
    String review = widget.book.review;

    return Scaffold(
      appBar: AppBar(
        title: const Text("Update a book"),
        backgroundColor: const Color(0xFF244A73),
      ),
      body: Container(
          decoration: const BoxDecoration(
            color: Colors.black,
          ),
          child: Form(
              key: _formKey,
              child: Column(
                children: [
                  Row(
                    children: [
                      const Text("Title:   ", style: TextStyle(color:Colors.white,)),
                      Expanded(child: TextFormField(
                        style: const TextStyle(color:Colors.white,),
                        initialValue: title,
                        onChanged: (value) => title = value,
                        validator: (value){
                          if(value == null || value.isEmpty){
                            return "The title field should have a value";
                          }
                          return null;
                        },
                      ))
                    ],
                  ),
                  Row(
                    children: [
                      const Text("Author:   ", style: TextStyle(color:Colors.white,)),
                      Expanded(child: TextFormField(
                        style: const TextStyle(color:Colors.white,),
                        initialValue: author,
                        onChanged: (value) => author = value,
                        validator: (value){
                          if(value == null || value.isEmpty){
                            return "The buy date field should have a value";
                          }
                          return null;
                        },
                      ))
                    ],
                  ),
                  Row(
                    children: [
                      const Text("Format:   ", style: TextStyle(color:Colors.white,)),
                      Expanded(child: TextFormField(
                        style: const TextStyle(color:Colors.white,),
                        initialValue: format,
                        onChanged: (value) => format = value,
                        validator: (value){
                          if(value == null || value.isEmpty){
                            return "The expiration date field should have a value";
                          }
                          return null;
                        },
                      ))
                    ],
                  ),
                  Row(
                    children: [
                      const Text("Status:   ", style: TextStyle(color:Colors.white,)),
                      Expanded(child: TextFormField(
                        style: const TextStyle(color:Colors.white,),
                        initialValue: status,
                        onChanged: (value) => status = value,
                        validator: (value){
                          if(value == null || value.isEmpty){
                            return "The aliment quantity field should have a value";
                          }
                          return null;
                        },
                      ))
                    ],
                  ),
                  Row(
                    children: [
                      const Text("Review:   ", style: TextStyle(color:Colors.white,)),
                      Expanded(child: TextFormField(
                        style: const TextStyle(color:Colors.white,),
                        initialValue: review,
                        onChanged: (value) => review = value,
                        validator: (value){
                          if(value == null || value.isEmpty){
                            return "The status field should have a value";
                          }
                          return null;
                        },
                      ))
                    ],
                  ), const SizedBox(height: 20),
                  ElevatedButton(onPressed: (){
                    if (_formKey.currentState!.validate()){
                      Navigator.pop(context, Book(
                          title,
                          author,
                          format,
                          status,
                          review
                      ));

                    }
                  }, child: const Text('Update', style: TextStyle(color: Color(0xFF244A73),))),
                ],
              )
          )
      ),

    ) ;

  }
}