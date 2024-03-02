import 'package:flutter/material.dart';
import 'package:flutter_app/ListScreen.dart';

void main() {
  runApp(const MaterialApp(
      home: Directionality(textDirection: TextDirection.ltr, child: ListScreen())
  ));
}
