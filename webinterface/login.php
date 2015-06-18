<?php
session_start(); 
$username = $_POST["username"]; 
$password = $_POST["password"]; 
$passwordEncrypt = md5($passwort); 
unset($arr);
unset($errorFile, $errorUsername, $errorPasswordRepeat);
$errorFile = 0; //If errorFile variable = -1 than fopen is False
$errorUsername = 0; //If username does not exist variable = -1
$errorPassword = 0; //If password is wrong value = -1

$userfile = fopen ("user.txt","r"); 
	if ($userfile == FALSE)
	{
		$errorFile = -1;
	}
	else
	{
	while (!feof($userfile)) 
	{ 
	$line = fgets($userdatei,500); 
	$userdata = explode("|", $line); 

	if ($userdata[0]==$username)
		{
			$errorUsername = 0;
			
			if $passwordEncrypt==trim($userdata[1])
			{
				$errorPassword = 0;
				$_SESSION['username'] = $username; 
			}
			else
			{
				$errorPassword = -1;
			}
		}
		else
		{
			$errorUsername = -1;
		}
   }
	fclose($userdatei); 
	} 
	$arr = array( 	'errorFile' => $errorFile,
					'errorUsername' => $errorUsername,
					'errorPassword' => $errorPassword,
					'username' => $username
				);
	
	echo json_encode($arr);
?>