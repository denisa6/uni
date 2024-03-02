<?php

use FTP\Connection;
include ('database/connection.php');
if($_SERVER['REQUEST_METHOD'] == 'POST'){
	$con =OpenConnection();
    if(isset($_POST['update'])){
        $bid = $_POST['bid'];
        $title = $con->real_escape_string($_POST['title']);
        $author = $con->real_escape_string($_POST['author']);
        $nrPages = $con->real_escape_string($_POST['nrPages']);
        $genre = $con->real_escape_string($_POST['genre']);
        $borrowed = $con->real_escape_string($_POST['borrowed']);
        $query = "UPDATE book SET title='$title', author='$author', nrPages='$nrPages', genre='$genre', borrowed='$borrowed' WHERE bid='$bid'";
        // $con->query($query);
    }
    CloseConnection($con);
}

?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Books Processing </title>
    <script src="https://code.jquery.com/jquery-3.3.1.js"></script>
    <link rel="stylesheet" type="text/css" href="style.css">
</head>

<body>
<button type="button" onclick="location.href='./index.html'">HOME </button>
<!-- <button type="button" onclick="location.href='./crud_documents.php'">BACK </button> -->
<br>

</body>

<section class="update_form">
    <form class="update" action="update.php" method="post">
        <input id="title" type="text" name="title" placeholder="title" value="<?=$title?>" required/>
        <input id="author" type="text" name="author" placeholder="author" value="<?=$author?>" required/>
        <input id="nrPages" type="text" name="nrPages" placeholder="nrPages" value="<?=$nrPages?>" required/>
        <input id="genre" type="text" name="genre" placeholder="genre" value="<?=$genre?>" required/>
        <input id="borrowed" type="text" name="borrowed" placeholder="borrowed" value="<?=$borrowed?>" required/>
        <input id="update" type="submit" name="update" value="Update book">
    </form>
</section>


</html>