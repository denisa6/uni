<?php
    session_start();
?>
<link rel="stylesheet" type="text/css" href="login.css">

<table id="browse-table" class="browse-table">
            <thead id>
                <th>ID</th>
                <th>Name</th>
                <th>Country</th>
            </thead>
            <tbody id="browse-tbody">
                <?php
                    require('connect.php');
                    $stmt = $connection->prepare("SELECT * FROM City");
                    $stmt->execute();
                    $result = $stmt->get_result();                    
                    while($row = mysqli_fetch_array($result)){ 
                        setcookie("cid", $row[0], 0, "/");
                        echo " <tr>";
                        echo  "<td>" . $row[0] . "</td>";
                        echo  "<td>" . $row[1] . "</td>";
                        echo  "<td>" . $row[2] . "</td>";
                        echo  "<td> 
                            <form method='GET' action='getLinks.php'>
                                <input type='hidden' name='cityId' value='" . $row[0] . "'>
                                <input type='hidden' name='cityName' value='" . $row[1] . "'>
                                <button type='submit'> Show </button>
                            </form>
                        </td>";
                        echo   "</tr>";
                    }
                ?>
            </tbody>
        </table>