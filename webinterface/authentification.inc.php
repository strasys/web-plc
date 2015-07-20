<?php
unset($loginstatus);
if(!isset($_SESSION['username']))
{
	$loginstatus = false;
	$adminstatus = false;
	transfer_javascript("error", "error", $loginstatus, $adminstatus );
	exit;
}
else
{
	$adminstatus = false;
	$loginstatus = true;
	if(isset($_SESSION['admin']))
	{
		$adminstatus = true;
		break 1;
	}
}

?>