<?php
header("Access-Control-Allow-Headers: *");
header("Access-Control-Allow-Origin: *");
require_once "utils/configuration.php";
if (isset($_POST['title']) && !empty(trim($_POST['title']))) {
    $bid = $_POST['id'];
    $title = $_POST['title'];
    $author = $_POST['author'];
    $nrPages = $_POST['nrPages'];
    $genre = $_POST['genre'];
    $borrowed = $_POST['borrowed'];
    $sql_query = "update book set title='$title', author = '$author', nrPages = '$nrPages', genre = '$genre', borrowed = '$borrowed' where bid = $bid";
    global $connection;
    $result = mysqli_query($connection, $sql_query);
    mysqli_close($connection);
} else {
    $postdata = file_get_contents("php://input");
    $request = json_decode($postdata);
    $bid = $request->id;
    $title = $request->title;
    $author = $request->author;
    $nrPages = $request->nrPages;
    $genre = $request->genre;
    $borrowed = $request->borrowed;
    $sql_query = "update book set title='$title', author = '$author', nrPages = '$nrPages', genre = '$genre', borrowed = '$borrowed' where bid = $bid";
    global $connection;
    $result = mysqli_query($connection, $sql_query);
    mysqli_close($connection);
}