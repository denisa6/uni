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
                <label>mother</label>
                <input type="mother" name="mother" class="username-input"/>
            </p>
            <p>
                <label>father</label>
                <input type="father" name="father" class="username-input"/>
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
        $stmt2 = $connection->prepare("SELECT id FROM Users WHERE username=?");
        $stmt2->bind_param("s", $_POST["username"]);
        $stmt2->execute();
        $result2 = $stmt2->get_result();
        $uid = $result2->fetch_row()[0];


        $stmt = $connection->prepare("SELECT COUNT(*) FROM FamilyRelations WHERE userid=? AND (mother=? OR father=?)");
        $stmt->bind_param("iss", $uid, $_POST["mother"], $_POST["father"]);
        $stmt->execute();
        $result = $stmt->get_result();
        $count = $result->fetch_row()[0];
        if ($count == 0) {
?>
            <div class="error">Invalid username or password</div>
<?php
        } else {

            setcookie("user", $_POST["username"], 0, "/");
            setcookie("mother", $_POST["mother"], 0, "/");
            setcookie("father", $_POST["father"], 0, "/");
            setcookie("userId", $uid, 0, "/");
            header("Location: /family-rel/index.php");
        }
        $connection->close();
    }
?>

    </body>
</html>