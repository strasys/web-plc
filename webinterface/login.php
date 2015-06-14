<?php
session_start(); 
$username = $_POST["username"]; 
$password = $_POST["password"]; 
$passwordEncrypt = md5($passwort); 
$log=0; 

$userfile = fopen ("user.txt","r"); 
while (!feof($userfile)) 
   { 
   $line = fgets($userdatei,500); 
   $userdata = explode("|", $line); 

   if ($userdata[0]==$username and $passwordEncrypt==trim($userdata[1])) 
      { 
      $_SESSION['username'] = $username; 
        echo "Login war erfolgreich. <a href=\"geheim.php\">Geschützer Bereich</a>"; 
      $log = 1; 
      } 
   } 
fclose($userdatei); 

if ($log==0) 
   { 
   echo "Zugriff verweigert <a href=\"login.html\">Zurück</a>"; 
   } 
?>

?>