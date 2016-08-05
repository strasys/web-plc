<?php
include_once ('privateplc_php.ini.php');
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
if (($setgetPT100handler == $get) && ($flag)){
//	for ($i=1; $i<3; $i++){
	
		exec("flock /tmp/PT100handlerlock /usr/lib/cgi-bin/PT100handler 1 g t", $output);
		exec("flock /tmp/PT100handlerlock /usr/lib/cgi-bin/PT100handler 2 g t", $output);
		exec("flock /tmp/PT1000handlerlock /usr/lib/cgi-bin/PT1000handler g 0", $output);
		exec("flock /tmp/PT1000handlerlock /usr/lib/cgi-bin/PT1000handler g 1", $output);
		exec("flock /tmp/PT1000handlerlock /usr/lib/cgi-bin/PT1000handler g 2", $output);
		exec("flock /tmp/PT1000handlerlock /usr/lib/cgi-bin/PT1000handler g 3", $output);

		transfer_javascript($output[0], $output[1], $output[2], $output[3], $output[4], $output[5],  $loginstatus, $adminstatus);
}
else
{
	transfer_javascript('error', 'error', $loginstatus, $adminstatus);
}



function transfer_javascript($temperature1, $temperature2, $temperature11, $temperature12, $temperature13, $temperature14, $loginstatus, $adminstatus)	
{
	$arr = array( 'temperature1' => $temperature1 ,
				  'temperature2' => $temperature2 ,
				  'temperature11' => $temperature11,
				  'temperature12' => $temperature12,
				  'temperature13' => $temperature13,
				  'temperature14' => $temperature14,
				  'loginstatus' => $loginstatus ,
				  'adminstatus' => $adminstatus
				);
	
	echo json_encode($arr);
}

?>