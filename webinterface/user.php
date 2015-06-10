<?php
$username = $_POST["username"];
$password = $_POST["password"];
$password2 = $_POST["passwordRepeat"];

if ($password == $password2)
	{
	$user_existing = array();
	//todo: upgrade to PHP 5.5.x necessary to use 
	//$passwordEncrypt = password_hash($password, PASSWORD_DEFAULT); 
	$passwordEncrypt = md5($password);
	echo "$passwordEncrypt <br>";
	$userfile = fopen("user.txt","r");
	while (!feof($userfile))
		{
		$line = fgets($userfile,500);
		$userdata = explode("|", $line);
		array_push ($user_existing,$userdata[0]);
		}
	fclose($userfile);
	
	if (in_array($username,$user_existing))
		{
		echo "Benutzername $username existiert bereits!";
		}
		
	else
		{
		$userfile = fopen ("user.txt","a");
		fwrite($userfile, $username);
		fwrite($userfile, "|");
		fwrite($userfile, $passwordEncrypt);
		fwrite($userfile, "\n");
		fclose($userfile);
		echo "Benutzer $username erfolgreich angelegt!";
		}
	}
	
	else 
	{
	echo "Die Passwörter stimmen nicht überein!";
	}

?>