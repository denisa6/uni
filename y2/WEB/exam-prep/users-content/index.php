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

<!DOCTYPE html>
<html>
    <head> 
        <title> Basic frontend add </title>
        <link rel="stylesheet" type="text/css" href="login.css">
        <script src="utils/jquery-3.7.0.js"> </script>
        <script src="utils/constants.js"></script>
        <script src="utils/cookie_util.js"></script>
    </head>
    <body> 
        <h2>Add new content</h2>
        <form method="post" action="index.php" class="login-form">
            <p>
                <label>title</label>
                <input type="text" name="title" class="username-input"/>
            </p>
            <p>
                <label>description</label>
                <input type="text" name="description" class="username-input"/>
            </p>
            <p>
                <label>url</label>
                <input type="text" name="url" class="username-input"/>
            </p>
            <p>
                <button type="submit" class="login-button">Submit</button>
            </p>
        </form>

<?php
    header("Access-Control-Allow-Headers: *");
    header("Access-Control-Allow-Origin: *");
    if ($_SERVER['REQUEST_METHOD'] == "POST") {
        require('connect.php');
        $stmt = $connection->prepare("INSERT INTO `content`(`title`, `description`, `url`, `userid`) VALUES (?,?,?,?)");
        $stmt->bind_param("sssi", $_POST["title"], $_POST["description"], $_POST["url"], $_COOKIE["userId"]);
        $stmt->execute();
        $connection->close();
    }
?>

