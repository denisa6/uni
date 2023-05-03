<?php

use FTP\Connection;
include ('database/connection.php');

?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Books Browser</title>
    <script type="text/javascript" src="browse.js"></script>
    <link rel="stylesheet" type="text/css" href="style.css">
</head>
<body>

<button class="home" type="button" onclick="location.href='./index.html'">HOME </button>

<div id="previous-filter">

</div>

<center>
    <div id="main">

        <h1> Books </h1>
        <div" style="float: left";>

            <select id="select-genre" name="Select Filter" onchange="get_filtered_by_genre()">
                <?php
                    $con = OpenConnection();
                    $sql = "SELECT DISTINCT genre FROM book";
                    $result_set = $con->query($sql);

                    if(mysqli_num_rows($result_set) > 0){
                        while($row = mysqli_fetch_array($result_set)){
                            $type = ''. $row['genre'] .'';
                            echo '<option>' . $type . '</option>';
                        }
                    }
                    CloseConnection($con);
                ?>

            </select>

        </div>


        <br />
        <br />


        <table id="browse-table" class="browse-table">
            <thead id>
                <th>ID</th>
                <th>Title</th>
                <th>Author</th>
                <th>NumberPages</th>
                <th>Genre</th>
                <th>Borrowed</th>
            </thead>
            <tbody id="browse-tbody">
                <?php
                    $con = OpenConnection();
                    $result_set = mysqli_query($con, "SELECT * FROM book");
                    
                    while($row = mysqli_fetch_array($result_set)){
                        echo " <tr>";
                        echo  "<td>" . $row['bid'] . "</td>";
                        echo  "<td>" . $row['title'] . "</td>";
                        echo  "<td>" . $row['author'] . "</td>";
                        echo  "<td>" . $row['nrPages'] . "</td>";
                        echo  "<td>" . $row['genre'] . "</td>";
                        echo  "<td>" . $row['borrowed'] . "</td>";
                        echo   "</tr>";
                    }
                    CloseConnection($con)
                ?>
            </tbody>
        </table>

        <label>
        </label>

    </div>
</center>
</body>
</html>