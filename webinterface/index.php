<?php
include_once ('privateplc_php.ini.php');
session_start();
include_once ('authentification.inc.php');
$getLoginStatus = $_POST['getLoginStatus'];

unset($arr);
$get = "g";

if ($getLoginStatus == $get)
{
	transfer_javascript($loginstatus, $adminstatus);
}


function transfer_javascript($loginstatus, $adminstatus)
{
	$arr = array(	'loginstatus' => $loginstatus ,
					'adminstatus' => $adminstatus
				);

	echo json_encode($arr);
}


?>