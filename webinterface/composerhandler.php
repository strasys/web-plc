<?php
include_once ('privateplc_php.ini.php');
session_start();
include_once ('authentification.inc.php');
unset($getLoginStatus, $setgetComposerStatus, $runstop, $setrunstopStatus);
$getLoginStatus = $_POST['getLoginStatus'];
$setgetComposerProcessStatus = $_POST['setgetComposerProcessStatus'];
$setrunstopStatus = $_POST['setrunstopStatus'];
//$getLoginStatus = "g";
unset($arr);
$get = "g";
$set = "s";

if ($getLoginStatus == $get)
{
	transfer_javascript($loginstatus, $adminstatus);
}

if ($setgetComposerProcessStatus == $get)
{
	$statusFile = fopen("/tmp/composerstatus.txt", "r");
	if ($statusFile == false)
	{
		$statusFile = fopen("/tmp/composerstatus.txt", "w");
		fwrite($statusFile, "stop");
		fclose($statusFile);
		$statusWord = "stop";
	}
	elseif ($statusFile)
	{
		$statusWord = trim(fgets($statusFile, 5));
		fclose($status);
	}
	
	switch ($statusWord){
		case "stop":
			$runstop = 0;
			break;
		case "run":
			$runstop = 1; 
			break;
	}
	transfer_javascript($loginstatus, $adminstatus, $runstop);
}

if ($setgetComposerProcessStatus == $set)
{
	$statusFile = fopen("/tmp/composerstatus.txt", "w");
	if ($statusFile == false)
	{
		$errorMsg = "Error: fopen\"/tmp/composerstatus.txt\", \"w\" ";
		break;
	}
	elseif ($statusFile)
	{
		switch ($setrunstopStatus){
			case 0:
				$statusWord = "stop";
				$runstop = 0;
				break;
			case 1:
				$statusWord = "run";
				$runstop = 1;
				$cmd = "php /var/www/composer.php";
				exec($cmd . " > /dev/null &");
			
				//todo: Add script start composer.php!
				break;
		}
		
		fwrite($statusFile,'',5);
		rewind($statusFile);
		fwrite($statusFile, $statusWord, 5);
		fclose($statusFile);
	}
	transfer_javascript($loginstatus, $adminstatus, $runstop, $errorMsg);
}



function transfer_javascript($loginstatus, $adminstatus, $runstop, $errorMsg)
{
	$arr = array(	'loginstatus' => $loginstatus ,
					'adminstatus' => $adminstatus ,
					'runstop' => $runstop,
					'errorMsg' => $errorMsg
				);

	echo json_encode($arr);
}

?>