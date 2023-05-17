<?php
header("Access-Control-Allow-Headers: *");
header("Access-Control-Allow-Origin: *");
require_once "utils/configuration.php";
if (isset($_POST['title']) && !empty(trim($_POST['title']))) {
    $title = $_POST['title'];
    $author = $_POST['author'];
    $nrPages = $_POST['nrPages'];
    $genre = $_POST['genre'];
    $borrowed = $_POST['borrowed'];
    $sql_query = "insert into book(title, author, nrPages, genre, borrowed) values ('$title', '$author', '$nrPages', $genre, '$borrowed')";
    global $connection;
    $result = mysqli_query($connection, $sql_query);
    mysqli_close($connection);
    
} else {
    $postdata = file_get_contents("php://input");
    $request = json_decode($postdata);
    $title = $request->title;
    $author = $request->author;
    $nrPages = $request->nrPages;
    $genre = $request->genre;
    $borrowed = $request->borrowed;
    global $connection;
    $statement = $connection->prepare("insert into book(title, author, nrPages, genre, borrowed) values (?, ?, ?, ?, ?)");
    $statement->bind_param("ssiss", $title, $author, $nrPages, $genre, $borrowed);
    $statement->execute();
}
?>
