<?php
	header("Access-Control-Allow-Headers: *");
	header("Access-Control-Allow-Origin: *");
    session_start();
    if($_COOKIE["user"] == null) {
        header("Location: /assets-users/login.php");
        return ;
    }

?>
<link rel="stylesheet" type="text/css" href="login.css">
<form method="GET" action="logout.php">
    <button type="submit"> Logout </button>
</form>

<table id="browse-table" class="browse-table">
            <thead id>
                <th>Name</th>
                <th>Description</th>
                <th>Value</th>
            </thead>
            <tbody id="browse-tbody">
                <?php
                    require('connect.php');
        			$stmt = $connection->prepare("SELECT name, description, value FROM Assets WHERE userid=?");
        			$stmt->bind_param("i", $_COOKIE["userId"]);
        			$stmt->execute();
        			$result = $stmt->get_result();                    
                    while($row = mysqli_fetch_array($result)){
                    	if ($row[2] <= 10){
                        	echo " <tr>";
                        	echo  "<td>" . $row[0] . "</td>";
                        	echo  "<td>" . $row[1] . "</td>";
                        	echo  "<td>" . $row[2] . "</td>";
                        	echo   "</tr>";
                        }
                        else{
                        	echo " <tr>";
                        	echo  "<td id='change-to-red'>" . $row[0] . "</td>";
                        	echo  "<td id='change-to-red'>" . $row[1] . "</td>";
                        	echo  "<td id='change-to-red'>" . $row[2] . "</td>";
                        	echo   "</tr>";
                        }
                    }
                ?>
            </tbody>
        </table>

Succesfully logged in as <?php echo $_COOKIE["user"]?>.