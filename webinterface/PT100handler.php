<?php
$arr;
$output;
unset($output);
unset($arr);
$setgetPT100handler = $_POST["setgetPT100handler"];
//$channelPT100handler = $_POST["channelPT100handler"];
$channel = "1";
$get = "g";

//get temperature from all channels
if ($setgetPT100handler == $get){
	for ($i=1; $i<3; $i++){
		$channel = "$i";
		exec("./cgi-bin/PT100handler $channel g t", &$output);
	}
	$arr = array( 	'temperature1' => $output[0],
			'temperature2' => $output[1]
	);
}

						
echo json_encode($arr);

?>