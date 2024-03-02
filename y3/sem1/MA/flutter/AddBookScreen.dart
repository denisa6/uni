import 'package:flutter/material.dart';
import 'package:flutter_app/Book.dart';

class AddBookScreen extends StatefulWidget {
  const AddBookScreen({super.key});

  @override
  State<AddBookScreen> createState() => AddBookScreenState();
}

class AddBookScreenState extends State<AddBookScreen>{
  final _formKey = GlobalKey<FormState>();

  String title = "";
  String author = "";
  String format = "";
  String status = "";
  String review = "";

  @override
  Widget build(BuildContext context){
    return Scaffold(
      appBar: AppBar(
        title: const Text("Add a book"),
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
                      onChanged: (value) => author = value,
                      validator: (value){
                        if(value == null || value.isEmpty){
                          return "The author field should have a value";
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
                }, child: const Text('Submit', style: TextStyle(color: Color(0xFF244A73),)),),
              ],
            )
        ),
      ),
    );
  }
}