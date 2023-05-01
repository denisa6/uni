<?php

use FTP\Connection;
session_start();
include ('database/connection.php');
if($_SERVER['REQUEST_METHOD'] == 'POST'){
	$con = OpenConnection();
	if(isset($_POST['add'])){
		$bid = $con->mysql_real_escape_string($_POST['bid']);
		$title = $con->mysql_real_escape_string($_POST['title']);
		$author = $con->mysql_real_escape_string($_POST['author']);
		$nrPages = $con->mysql_real_escape_string($_POST['nrPages']);
		$genre = $con->mysql_real_escape_string($_POST['genre']);
		$borrowed = $con->mysql_real_escape_string($_POST['borrowed']);
		// $query = "INSERT INTO books VALUES('$bid', '$title', '$author', '$nrPages', '$genre', '$borrowed')";
        // $con->query($query);


		$stmt = $con->prepare("INSERT INTO books(bid, title, author, nrPages, genre, borrowed) VALUES(?, ?, ?, ?, ?, ?)");
        $stmt->bind_param("ississ", $bid, $title, $author, $nrPages, $genre, $borrowed);
        $stmt->execute();
	}
	CloseConnection($con);
}

?>

<!DOCTYPE html>
<html lang="en">
<head>
	<meta charset="UTF-8">
	<title>Books Processing</title>
	<script type="https://code.jquery.com/jquery-3.3.1.js"></script>
	<link rel="stylesheet" type="text/css" href="style.css">
    <script type="text/javascript" src="script.js"></script>
</head>

<body>
<button class="home" type="button" onclick="location.href='./index.html'">HOME </button>
<br>

<section class="add_form">
    <form action="add.php" method="post">
        <input id="bid" type="text" name="bid" placeholder="bid">
        <input id="title" type="text" name="title" placeholder="title">
        <input id="author" type="text" name="author" placeholder="author">
        <input id="nrPages" type="text" name="nrPages" placeholder="nrPages">
        <input id="genre" type="text" name="genre" placeholder="genre">
        <input id="borrowed" type="text" name="borrowed" placeholder="borrowed">
        <input id="add" type="submit" name="add" value="Add new book">
        <!-- <input id="update" type="submit" name="update" value="Update document"> -->
    </form>
</section>

<section class="display_add">
    <br>
    <table class="display-table">
        <thead>
            <th>ID</th>
            <th>Title</th>
            <th>Author</th>
            <th>NumberPages</th>
            <th>Genre</th>
            <th>Borrowed</th>
        </thead>
        <tbody>

            <?php
            $con = OpenConnection();
            $result_set = mysqli_query($con, "SELECT * FROM document");
            
            while($row = mysqli_fetch_array($result_set)){
                echo "<tr>";
                echo  "<td>" . $row['bid'] . "</td>";
                echo  "<td>" . $row['title'] . "</td>";
                echo  "<td>" . $row['author'] . "</td>";
                echo  "<td>" . $row['nrPages'] . "</td>";
                echo  "<td>" . $row['genre'] . "</td>";
                echo  "<td>" . $row['borrowed'] . "</td>";
                echo   "</tr>";
            }
            CloseConnection($con);
            ?>

        </tbody>
    </table>
</section>


<!-- <button class='btnUpdate' id='edit' name='edit' type='button' value= ". $row['id'] . " onclick=\"location.href='./update.php'\">Update</button> -->
</body>

</html>