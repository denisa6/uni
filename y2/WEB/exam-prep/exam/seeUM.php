<link rel="stylesheet" type="text/css" href="login.css">
<table id="browse-table" class="browse-table">
            <thead id>
                <th>Sender</th>
                <th>Text</th>
            </thead>
            <tbody id="browse-tbody">
                <?php
                    require('connect.php');
        			$stmt = $connection->prepare("SELECT * FROM Messages WHERE receivers=? AND type='unicast'");
        			$stmt->bind_param("s", $_COOKIE["user"]);
        			$stmt->execute();
        			$result = $stmt->get_result();                    
                    while($row = mysqli_fetch_array($result)){   
                    	echo " <tr>";
                        echo  "<td>" . $row[1] . "</td>";
                        echo  "<td>" . $row[3] . "</td>";
                        echo   "</tr>";
                    }
                ?>
            </tbody>
        </table>
