<?php
	header("Access-Control-Allow-Headers: *");
	header("Access-Control-Allow-Origin: *");
    session_start();
    if($_COOKIE["user"] == null) {
        header("Location: /family-rel/login.php");
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
            </thead>
            <tbody id="browse-tbody">
                <?php
                    require('connect.php');
        			$stmt = $connection->prepare("SELECT userid FROM FamilyRelations WHERE (mother=? OR father=?) AND userid<>?");
        			$stmt->bind_param("ssi", $_COOKIE["mother"], $_COOKIE["father"], $_COOKIE["userId"]);
        			$stmt->execute();
        			$result = $stmt->get_result();                    
                    while($row = mysqli_fetch_array($result)){
                        $stmt2 = $connection->prepare("SELECT username FROM Users WHERE id=?");
                        $stmt2->bind_param("i", $row[0]);
                        $stmt2->execute();
                        $result2 = $stmt2->get_result();
                        $name = $result2->fetch_row()[0];   
                    	echo " <tr>";
                        echo  "<td>" . $name . "</td>";
                        echo   "</tr>";
                    }
                ?>
            </tbody>
        </table>

Succesfully logged in as <?php echo $_COOKIE["user"]?>.