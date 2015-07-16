<?php
session_start(); 
unset ($username, $password);
$username = $_POST["username"]; 
$password = $_POST["password"]; 
$passwordEncrypt = md5($password); 
unset($arr);
unset($errorFile, $errorUsername, $errorPasswordRepeat);
$errorFile = 0; //If errorFile variable = -1 than fopen is False
$errorUsername = 0; //If username does not exist variable = -1
$errorPassword = 0; //If password is wrong value = -1

$userfile = fopen ("user.txt","r"); 
	if ($userfile == FALSE)
	{
		$errorFile = -1;
		transfer_javascript($errorFile, $errorUsername, $errorPassword, $username);
		exit;
	}

//search user file if username matches
	while (!feof($userfile)) 
	{ 
	$line = fgets($userfile,500); 
	$userdata = explode("|", $line); 
	
		if ($userdata[0]==$username)
		{
			if ($passwordEncrypt==trim($userdata[1]))
			{
				$_SESSION['username'] = $username;
				if (trim($userdata[2])=="admin")
				{
					$_SESSION['admin'] = "admin";
					
				}
			}
			else
			{
				$errorPassword = -1;
			}
			transfer_javascript($errorFile, $errorUsername, $errorPassword, $username);
			fclose($userfile);
			break 1;
		}
		
		if (($userdata[0]!=$username) && (feof($userfile)))
		{
			$errorUsername = -1;
			$errorPassword = -1;
			transfer_javascript($errorFile, $errorUsername, $errorPassword, $username);
			fclose($userfile);
			break 1;
		}	
	}
	
function transfer_javascript($errorFile, $errorUsername, $errorPassword, $username)	
{
	$arr = array( 	'errorFile' => $errorFile,
					'errorUsername' => $errorUsername,
					'errorPassword' => $errorPassword,
					'username' => $username
				);
	
	echo json_encode($arr);
}
	?>