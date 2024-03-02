class Book {
  int? id;
  String? title;
  String? author;
  String? format;
  String? status;
  String? review;

  userMap() {
    var mapping = Map<String, dynamic>();
    mapping['id'] = id ?? null;
    mapping['title'] = title!;
    mapping['author'] = author!;
    mapping['format'] = format!;
    mapping['status'] = status;
    mapping['review'] = review;
    return mapping;
  }
}