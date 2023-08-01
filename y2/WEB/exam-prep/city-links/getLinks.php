<!DOCTYPE html>
<html>
<head>
    <title>City Links</title>
</head>
<table id="browse-table" class="browse-table">
    <thead id>
        <th>City 1</th>
        <th>City 2</th>
        <th>Duration</th>
        <th>Distance</th>
    </thead>
    <tbody id="browse-tbody">
        <?php
            require('connect.php');
        	if (isset($_GET['cityId']) and isset($_GET['cityName'])) {
        	$cityId = $_GET['cityId'];
        	$cityName = $_GET['cityName'];
        	$stmt = $connection->prepare("SELECT idCity1, idCity2, duration, distance FROM Link WHERE idCity1=? OR idCity2=? ORDER BY 0.6*duration + 0.4*distance");
        	$stmt->bind_param("ii", $cityId, $cityId);
        	$stmt->execute();
        	$result = $stmt->get_result();          

            while($row = mysqli_fetch_array($result)){
            	// row[0] - idCity1 row[1] - idCity2
            	if($row[0] == $cityId){
            		$stmt2 = $connection->prepare("SELECT name FROM City WHERE id=?");
        			$stmt2->bind_param("i", $row[1]);
        			$stmt2->execute();
        			$result2 = $stmt2->get_result();
        			$cityName2 = $result2->fetch_row()[0];

        			echo " <tr>";
                	echo  "<td>" . $cityName . "</td>";
                	echo  "<td>" . $cityName2 . "</td>";
                	echo  "<td>" . $row[2] . "</td>";
                	echo  "<td>" . $row[3] . "</td>";
                	echo   "</tr>";
            	} 
            	else{
            		$stmt2 = $connection->prepare("SELECT name FROM City WHERE id=?");
        			$stmt2->bind_param("i", $row[0]);
        			$stmt2->execute();
        			$result2 = $stmt2->get_result();
        			$cityName2 = $result2->fetch_row()[0];

        			echo " <tr>";
                	echo  "<td>" . $cityName2 . "</td>";
                	echo  "<td>" . $cityName . "</td>";
                	echo  "<td>" . $row[2] . "</td>";
                	echo  "<td>" . $row[3] . "</td>";
                	echo   "</tr>";
            	} 
            }}
        ?>
    </tbody>
</table>
</html>