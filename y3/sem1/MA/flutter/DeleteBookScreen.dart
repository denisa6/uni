import 'package:flutter/material.dart';
import 'package:flutter_app/Book.dart';

class DeleteBookScreen extends StatelessWidget{
  const DeleteBookScreen({super.key, required this.book});

  final Book book;

  @override
  Widget build(BuildContext context){
    return Scaffold(
        appBar: AppBar(
          title: const Text("Delete book"),
          //backgroundColor: Colors.green.shade700,
          backgroundColor: const Color(0xFF244A73),
        ),
        body: Container(
          decoration: const BoxDecoration(
            color: Colors.black,
          ),
          child:Column(
            children: [
              Text(
                  "\nDelete book with\n title: ${book.title}\nauthor: ${book.author} \n\n", style: const TextStyle(color:Colors.white,)
              ),
              Row (
                mainAxisAlignment: MainAxisAlignment.spaceEvenly,
                children: [
                  Container(
                    color: Colors.white,
                    width: 110,
                    height: 35,
                    child: TextButton(
                        onPressed: (){
                          Navigator.pop(context, book);
                        },
                        child: const Text("Delete", style: TextStyle(color: Color(0xFF244A73),))
                    ),
                  ),
                  Container(
                    color: Colors.white,
                    width: 110,
                    height: 35,
                    child: TextButton(
                      onPressed: (){
                        Navigator.pop(context, null);
                      },
                      child: const Text("Cancel", style: TextStyle(color: Color(0xFF244A73),)),
                    ),
                  ),
                ],
              )
            ],
          ),
        )
    );
  }
}