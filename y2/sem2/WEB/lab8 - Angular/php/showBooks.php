<?php
header("Access-Control-Allow-Origin: *");
require_once 'utils/configuration.php';
$sql_query = "SELECT * FROM book;";
global $connection;
$result = mysqli_query($connection, $sql_query);

if ($result) {
    $number_of_rows = mysqli_num_rows($result);
    $requested_books = array();
    $genre = $_GET["genre"];
    //$name = $_GET["name"];
    for ($i = 0; $i < $number_of_rows; $i++) {
        $row = mysqli_fetch_array($result);
        if (str_contains($row["genre"], $genre))
            array_push($requested_books, array(
                "id" => (int)$row['bid'],
                "title" => $row['title'],
                "author" => $row['author'],
                "nrPages" => $row['nrPages'],
                "genre" => $row['genre'],
                "borrowed" => $row['borrowed']));
    }
    mysqli_free_result($result);
    echo json_encode($requested_books);
}
mysqli_close($connection);