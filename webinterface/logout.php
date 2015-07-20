<?php 
session_start();
unset($_SESSION['username']);
unset($_SESSION['admin']);
session_destroy();
$file = file_get_contents('index.html');
echo $file;
?>