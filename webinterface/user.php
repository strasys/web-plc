<?php
$username = $_POST["username"];
$password = $_POST["password"];
$password2 = $_POST["passwordRepeat"];
$adminright = $_POST["adminright"];
unset($arr);
unset($errorFile, $errorUsername, $errorPasswordRepeat);
$errorFile = 0; //If errorFile variable = -1 than fopen is False
$errorUsername = 0; //If username exists already value = -1
$errorPasswordRepeat = 0; //If password and password2 are not equal value = -1

if ($adminright == "true")
{
	$adminmarker = "admin";
}
else 
{
	$adminmarker = "user";	
}

if ($password == $password2)
	{
	$user_existing = array();
	//TODO: upgrade to PHP 5.5.x necessary to use $passwordEncrypt = password_hash($password, PASSWORD_DEFAULT); 
	$passwordEncrypt = md5($password);
	
	$userfile = fopen("user.txt","r");
	if ($userfile == FALSE)
	{
		$errorFile = -1;
	}
	else
	{
	while (!feof($userfile))
		{
		$line = fgets($userfile,500);
		$userdata = explode("|", $line);
		array_push ($user_existing,$userdata[0]);
		}
	fclose($userfile);
	
	if (in_array($username,$user_existing))
		{
		$errorUsername = -1;
		}
		
	else
		{
		$userfile = fopen ("user.txt","a");
		fwrite($userfile, $username);
		fwrite($userfile, "|");
		fwrite($userfile, $passwordEncrypt);
		fwrite($userfile, "|");
		fwrite($userfile, $adminmarker);
		fwrite($userfile, "\n");
		fclose($userfile);
		}
	}
	}
	else 
	{
	$errorPasswordRepeat = -1;
	}
	
	$arr = array( 	'errorFile' => $errorFile,
					'errorUsername' => $errorUsername,
					'errorPasswordRepeat' => $errorPasswordRepeat,
					'username' => $username
				);
	
	echo json_encode($arr);
?>