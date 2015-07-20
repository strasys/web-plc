<?php
session_start();
include_once ('authentification.inc.php');

$arr;
$output;
unset($output);
unset($arr);
$setgetPT100handler = $_POST["setgetPT100handler"];
//$channelPT100handler = $_POST["channelPT100handler"];
//$channel = "1";
$get = "g";

//get temperature from all channels
if ($setgetPT100handler == $get){
//	for ($i=1; $i<3; $i++){
	
		exec("flock /tmp/PT100handlerlock /usr/lib/cgi-bin/PT100handler 1 g t", $output);
		exec("flock /tmp/PT100handlerlock /usr/lib/cgi-bin/PT100handler 2 g t", $output);

		transfer_javascript($output[0], $output[1], $loginstatus, $adminstatus);
}



function transfer_javascript($temperature1, $temperature2, $loginstatus, $adminstatus)	
{
	$arr = array( 'temperature1' => $temperature1 ,
				  'temperature2' => $temperature2 ,
				  'loginstatus' => $loginstatus ,
				  'adminstatus' => $adminstatus
				);
	
	echo json_encode($arr);
}

?>