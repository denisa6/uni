
import 'package:flutter/material.dart';
import 'package:flutter_app/AddBookScreen.dart';
import 'package:flutter_app/Book.dart';
import 'package:flutter_app/DeleteBookScreen.dart';
import 'package:flutter_app/Repository.dart';
import 'package:flutter_app/UpdateBookScreen.dart';

class ListScreen extends StatefulWidget{
  const ListScreen({super.key});

  @override
  State<ListScreen> createState() => ListScreenState();

}

class ListScreenState extends State<ListScreen>{
  Repository repository = Repository();
  @override
  Widget build(BuildContext context){
    return Scaffold(
      appBar: AppBar(
        title: const Text("Personal Library App ⭐"),
        backgroundColor: const Color(0xFF244A73),
      ),
      body: Container(
        decoration: const BoxDecoration(
          color: Colors.black,
        ),
        child: Column(
          children: [
            SizedBox(
                width: 600,
                child: TextButton(
                    onPressed: () async{
                      Book book = await Navigator.push(
                          context,
                          MaterialPageRoute(builder: (context) => const AddBookScreen())
                      )as Book;
                      if(!repository.add(book)){
                        ScaffoldMessenger.of(context).showSnackBar(
                          const SnackBar(content: Text('The element you are trying to add already exists')),
                        );
                      }else{
                        setState((){});
                      }
                    },
                    child: const Text("Add", style: TextStyle(color: Color(0xFF244A73),))
                )
            ),
            Expanded(
              child: ListView.builder(
                  itemCount: repository.getAll().length,
                  itemBuilder: (context, index){
                    return bookView(index, repository.getAll()[index]);
                  }),
            )
          ],
        ),
      ),
    );
  }

  Widget bookView(int index, Book book){
    Color statusColor = Colors.black; // Default color

    // Check the status and set the color accordingly
    if (book.status == "not read") {
      statusColor = Colors.red;
    } else if (book.status == "read") {
      statusColor = Colors.green;
    } else if (book.status == "reading") {
      statusColor = Colors.yellow;
    }

    return Card(
        color: const Color(0xFFA0BFF0),
        child: Column(
          children: [
            Text(
              "\n${index + 1}. ${repository.getAll()[index].title}\n${repository.getAll()[index].author}\n${repository.getAll()[index].format}",
              style: const TextStyle(fontSize: 18, color: Colors.black),
              textAlign: TextAlign.center,
            ),
            Text(
              repository.getAll()[index].status,
              style: TextStyle(fontSize: 18, color: statusColor),
              textAlign: TextAlign.center,
            ),
            Text(
              repository.getAll()[index].review,
              style: const TextStyle(fontSize: 18, color: Colors.black),
              textAlign: TextAlign.center,
            ),
            const SizedBox(height: 20),
            Row(
              mainAxisAlignment: MainAxisAlignment.spaceEvenly,
              children: [
                Container(
                  color: Colors.white70,
                  width: 110,
                  height: 35,
                  child: TextButton(
                    onPressed: () async{
                      Book book = await Navigator.push(
                          context,
                          MaterialPageRoute(builder: (context) => UpdateBookScreen(book: repository.getAll()[index]))
                      )as Book;
                      if(!repository.update(book)){
                        ScaffoldMessenger.of(context).showSnackBar(
                          const SnackBar(content: Text('The element you are trying to update does not exist')),
                        );
                      }else{
                        setState(() {});
                      }
                    },
                    child: const Text("Update", style: TextStyle(color: Color(0xFF244A73),)),
                  ),
                ),
                Container(
                  color: Colors.white70,
                  width: 110,
                  height: 35,
                  child: TextButton(
                    onPressed: () async{
                      Book book = await Navigator.push(
                          context,
                          MaterialPageRoute(builder: (context) => DeleteBookScreen(book: repository.getAll()[index]))
                      )as Book;
                      if(!repository.remove(book)){
                        ScaffoldMessenger.of(context).showSnackBar(
                          const SnackBar(content: Text('The element you are trying to delete does not exist')),
                        );
                      }else{
                        setState(() {});
                      }
                    },
                    child: const Text("Delete", style: TextStyle(color: Color(0xFF244A73),)),
                  ),
                )
              ],

            ), const SizedBox(height: 20),
          ],
        )
    );
  }
}
