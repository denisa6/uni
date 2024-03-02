<?php
    header("Access-Control-Allow-Headers: *");
    header("Access-Control-Allow-Origin: *");
    if ($_SERVER['REQUEST_METHOD'] == "POST") {
        require('connect.php');

        if (str_contains($_POST["receiver"], ';')) {
            $type = "multicast";
            $stmt = $connection->prepare("INSERT INTO `messages`(`sender`, `type`, `text`, `receivers`) VALUES (?,?,?,?)");
            $stmt->bind_param("ssss", $_COOKIE["user"], $type, $_POST["unicastText"], $_POST["receiver"]);
            $stmt->execute();
        }
        else{
            $type = "unicast";
            $stmt = $connection->prepare("INSERT INTO `messages`(`sender`, `type`, `text`, `receivers`) VALUES (?,?,?,?)");
            $stmt->bind_param("ssss", $_COOKIE["user"], $type, $_POST["unicastText"], $_POST["receiver"]);
            $stmt->execute();
        }
        $connection->close();
        header("Location: /exam/sendMessage.php");
    }
?>