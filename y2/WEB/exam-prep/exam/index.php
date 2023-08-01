<!DOCTYPE html>
<html>
    <head> 
        <title> Basic frontend login </title>
        <link rel="stylesheet" type="text/css" href="login.css">
        <script src="utils/jquery-3.7.0.js"> </script>
        <script src="utils/constants.js"></script>
        <script src="utils/cookie_util.js"></script>
    </head>
    <body> 
        <h2>Login Question</h2>
        <form method="post" action="index.php" class="login-form">
            <p><?php echo $_COOKIE["question"];?></p>
            <p>
                <label>secret answer</label>
                <input type="password" name="secretAnswer" class="password-input"/>
            </p>
            <p>
                <button type="submit" class="login-button">Check</button>
            </p>
        </form>

<?php
    $var = $_GET["username"];
    header("Access-Control-Allow-Headers: *");
    header("Access-Control-Allow-Origin: *");
    if ($_SERVER['REQUEST_METHOD'] == "POST") {
        $user=$_COOKIE["user"];
        require('connect.php');
        $stmt2 = $connection->prepare("SELECT id FROM Users WHERE user=? AND secretAnswer=?");
        $stmt2->bind_param("ss",  $_COOKIE["user"], $_POST["secretAnswer"]);
        $stmt2->execute();
        $result2 = $stmt2->get_result();
        $uid = $result2->fetch_row()[0];
        if ($uid == 0) {
?>
            <div class="error">Invalid username or password</div>
<?php
        } else {

            //setcookie("user", $_COOKIET["username"], 0, "/");
            //setcookie("userId", $uid, 0, "/");
            header("Location: /exam/sendMessage.php");
        }
        $connection->close();
    }
?>
<p><?php echo $_GET["username"] . " " . strlen($_GET["username"]);?></p>
    </body>
</html>
