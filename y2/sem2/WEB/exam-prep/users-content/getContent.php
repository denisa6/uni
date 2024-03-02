<?php
	header("Access-Control-Allow-Headers: *");
	header("Access-Control-Allow-Origin: *");
    session_start();
    if($_COOKIE["user"] == null) {
        header("Location: /users-content/login.php");
        return ;
    }

?>
<link rel="stylesheet" type="text/css" href="login.css">
<form method="GET" action="logout.php">
    <button type="submit"> Logout </button>
</form>

<form method="GET" action="getNewContent.php">
    <button type="submit"> Get new content </button>
</form>

<table id="browse-table" class="browse-table">
            <thead id>
                <th>Date</th>
                <th>Title</th>
                <th>Description</th>
                <th>URL</th>
            </thead>
            <tbody id="browse-tbody">
                <?php
                    require('connect.php');
        			$stmt = $connection->prepare("SELECT * FROM Content");
        			$stmt->execute();
        			$result = $stmt->get_result();                    
                    while($row = mysqli_fetch_array($result)){  
                    	echo " <tr>";
                        echo  "<td>" . $row[1] . "</td>";
                        echo  "<td>" . $row[2] . "</td>";
                        echo  "<td>" . $row[3] . "</td>";
                        echo  "<td>" . $row[4] . "</td>";
                        echo   "</tr>";
                        setcookie("lastContentId", $row[0], 0, "/");
                    }
                ?>
            </tbody>
        </table>

