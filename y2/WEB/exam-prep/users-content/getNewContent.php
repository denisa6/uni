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
        			$stmt = $connection->prepare("SELECT * FROM Content WHERE id>?");
                    $stmt->bind_param("i", $_COOKIE["lastContentId"]);
        			$stmt->execute();
        			$result = $stmt->get_result();                    
                    while($row = mysqli_fetch_array($result)){  
                    	echo " <tr>";
                        echo  "<td>" . $row[1] . "</td>";
                        echo  "<td>" . $row[2] . "</td>";
                        echo  "<td>" . $row[3] . "</td>";
                        echo  "<td>" . $row[4] . "</td>";
                        echo   "</tr>";
                    }
                ?>
            </tbody>
        </table>