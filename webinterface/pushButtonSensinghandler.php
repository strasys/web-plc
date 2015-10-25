<?php 
include_once ('privateplc_php.ini.php');
session_start();
include_once ('authentification.inc.php');
unset($getLoginStatus, $setgetComposerStatus, $runstop, $setrunstopStatus);
$getLoginStatus = $_POST['getLoginStatus'];
$setgetpushButtonSensingProcessStatus = $_POST['setgetpushButtonSensingProcessStatus'];
$setrunstopStatus = $_POST['setrunstopStatus'];
$sensingChannels = $_POST['sensingChannels']; //variable must be transfered "1 1 1 1" with space in between
$sensingCycle = $_POST['sensingCycle'];

unset($arr);
$get = "g";
$set = "s";


if ($getLoginStatus == $get)
{
	transfer_javascript($loginstatus, $adminstatus);
}

if ($setgetpushButtonSensingProcessStatus == $get)
{
	$statusFile = fopen("/tmp/pushButtonSensingRunStop.txt", "r");
	if ($statusFile == false)
	{
		$statusFile = fopen("/tmp/pushButtonSensingRunStop.txt", "w");
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

if ($setgetpushButtonSensingProcessStatus == $set)
{
	$statusFile = fopen("/tmp/pushButtonSensingRunStop.txt", "w");
	if ($statusFile == false)
	{
		$errorMsg = "Error: file could not be opened! ";
	}
	elseif ($statusFile == true)
	{
		
		switch ($setrunstopStatus)
		{
			case 0:
				$statusWord = "stop";
				$runstop = 0;
				break;
			case 1:
				$statusWord = "run";
				$runstop = 1;
				break;
		}

		fwrite($statusFile,'',5);
		rewind($statusFile);
		fwrite($statusFile, $statusWord, 5);
		fclose($statusFile);
		
		if ($statusWord == "run")
		{
			$cmd = " /usr/lib/cgi-bin/pushButtonSensing 0 1 0 1";
			exec($cmd . " > /dev/null &");
		}
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