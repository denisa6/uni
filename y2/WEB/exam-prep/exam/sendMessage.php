<?php
	header("Access-Control-Allow-Headers: *");
	header("Access-Control-Allow-Origin: *");
    session_start();
    if($_COOKIE["user"] == null) {
        header("Location: /exam/index.php");
        return ;
    }

?>

<!DOCTYPE html>
<html>
    <head> 
        <title> Basic frontend add </title>
        <link rel="stylesheet" type="text/css" href="login.css">
        <script src="utils/jquery-3.7.0.js"> </script>
        <script src="utils/constants.js"></script>
        <script src="utils/cookie_util.js"></script>
    </head>
    <form method="GET" action="logout.php">
        <button type="submit"> Logout </button>
    </form>
    <body> 
        <h2>Add new unicast message</h2>
        <form method="post" action="sendUniMessage.php" class="login-form">
            <p>
                <label>text</label>
                <input type="text" name="unicastText" class="username-input"/>
            </p>
            <p>
                <label>receiver</label>
                <input type="text" name="receiver" class="username-input"/>
            </p>
            <p>
                <button type="submit" class="login-button">Send</button>
            </p>
        </form>

    <form method="GET" action="seeUM.php">
        <button type="submit"> See unicast messages </button>
    </form>
    <form method="GET" action="seeMM.php">
        <button type="submit"> See multicast messages </button>
    </form>