<?php
     session_start(); 
?>

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
        <h2>Login</h2>
        <form method="post" action="login.php" class="login-form">
            <p>
                <label>username</label>
                <input type="text" name="username" class="username-input"/>
            </p>
            <p>
                <label>password</label>
                <input type="password" name="password" class="password-input"/>
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
        $stmt = $connection->prepare("SELECT COUNT(*) FROM Users WHERE username=? AND password=?");
        $stmt->bind_param("ss", $_POST["username"], $_POST["password"]);
        $stmt->execute();
        $result = $stmt->get_result();
        $count = $result->fetch_row()[0];
        if ($count == 0) {
?>
            <div class="error">Invalid username or password</div>
<?php
        } else {
            $stmt2 = $connection->prepare("SELECT id, role FROM Users WHERE username=? AND password=?");
            $stmt2->bind_param("ss", $_POST["username"], $_POST["password"]);
            $stmt2->execute();
            $result2 = $stmt2->get_result();
            $row = mysqli_fetch_array($result2);
            $uid = $row[0];
            $role = $row[1];

            setcookie("user", $_POST["username"], 0, "/");
            setcookie("userId", $uid, 0, "/");
            //setcookie("role", $role, 0, "/");
            if($role == 1)
                //creator = 1
                header("Location: /users-content/index.php");
            else
                //reader = 2
                header("Location: /users-content/getContent.php");
        }
        $connection->close();
    }
?>

    </body>
</html>