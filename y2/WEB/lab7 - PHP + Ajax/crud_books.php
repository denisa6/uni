<?php

use FTP\Connection;
include ('database/connection.php');
if($_SERVER['REQUEST_METHOD'] == 'POST'){
	$con = OpenConnection();
	if(isset($_POST['add'])){
        $bid = $_POST['bid'];
        $title = $_POST['title'];
        $author = $_POST['author'];
        $nrPages = $_POST['nrPages'];
        $genre = $_POST['genre'];
        $borrowed = $_POST['borrowed'];
        $query = "INSERT INTO book VALUES('$bid', '$title', '$author', '$nrPages', '$genre', '$borrowed')";
        $con->query($query);
    }
    else if(isset($_POST['update'])){
        $bid = $_POST['bid'];
        $title = $_POST['title'];
        $author = $_POST['author'];
        $nrPages = $_POST['nrPages'];
        $genre = $_POST['genre'];
        $borrowed = $_POST['borrowed'];
        $query = "UPDATE book SET title='$title', author='$author', nrPages='$nrPages', genre='$genre', borrowed='$borrowed' WHERE bid='$bid'";
        $con->query($query);
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
    <script type="text/javascript" src="script.js"></script>
</head>

<body>
<button class="home" type="button" onclick="location.href='./index.html'">HOME </button>
<br>

<section class="add_form">
    <form action="crud_documents.php" method="post">
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

<section class="update_form">
    <form action="crud_documents.php" method="post">
        <input id="bid" type="text" name="bid" placeholder="bid">
        <input id="title" type="text" name="title" placeholder="title">
        <input id="author" type="text" name="author" placeholder="author">
        <input id="nrPages" type="text" name="nrPages" placeholder="nrPages">
        <input id="genre" type="text" name="genre" placeholder="genre">
        <input id="borrowed" type="text" name="borrowed" placeholder="borrowed">
        <input id="update" type="submit" name="update" value="Update book">
    </form>
</section>

<section class="display">
    <br>
    <table class="display-table">
        <thead>
            <th>ID</th>
            <th>Title</th>
            <th>Author</th>
            <th>NumberPages</th>
            <th>Genre</th>
            <th>Borrowed</th>
            <th> </th>
        </thead>
        <tbody>

            <?php
            $con = OpenConnection();
            $result_set = mysqli_query($con, "SELECT * FROM book");
            
            while($row = mysqli_fetch_array($result_set)){
                echo "<tr>";
                echo  "<td>" . $row['bid'] . "</td>";
                echo  "<td>" . $row['title'] . "</td>";
                echo  "<td>" . $row['author'] . "</td>";
                echo  "<td>" . $row['nrPages'] . "</td>";
                echo  "<td>" . $row['genre'] . "</td>";
                echo  "<td>" . $row['borrowed'] . "</td>";
                echo  "<td> 
                            <button class='btnUpdate' type='button'>Update</button>
                            <button class='btnDelete' type='button'>Delete</button>
                      </td>
                      </tr>";
            }
            CloseConnection($con);
            ?>

        </tbody>
    </table>
</section>


<!-- <button class='btnUpdate' id='edit' name='edit' type='button' value= ". $row['id'] . " onclick=\"location.href='./update.php'\">Update</button> -->
</body>

</html>