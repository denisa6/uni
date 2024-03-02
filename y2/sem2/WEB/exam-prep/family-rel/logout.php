<?php
	header("Access-Control-Allow-Headers: *");
	header("Access-Control-Allow-Origin: *");
    setcookie("user", "", time() - 300);
    header("Location: /family-rel/login.php");
?>