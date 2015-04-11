<?php

$arr;
$setgetAnalog = $_POST["setgetAnalog"];
$inout = $_POST["InOut"];
$channelAOUT = $_POST["channelAOUT"];
$get = "g";
$set = "s";
$IN = "I";
$Out = "O";

//get Analog IN values
if ($setgetAnalog == $get){
	if ($inout == $IN){
		for ($i=2; $i<4; $i++){
		//we are looking at AIN channels 2 and 3 
		$channel = $i;
		exec(" /usr/lib/cgi-bin/AINOUThandler g I $channel", $output);
		}
		$arr = array('INvalue1' => $output[0],
				 	'INvalue2' => $output[1]
					);
	}
	elseif ($inout == $Out){
		for ($i=1; $i<3; $i++){
			$channel = $i;
			exec(" /usr/lib/cgi-bin/AINOUThandler g O $channel", $output);
		}
		$arr = array('OUTvalue1' => $output[0],
				'OUTvalue2' => $output[1]
		);
	}	
}

elseif ($setgetAnalog == $set){
	if ($inout == $out){
	exec("flock /tmp/AINOUThandler /usr/lib/cgi-bin/AINOUThandler s O $channelAOUT", $output);
	}
	$arr = array
	
}

echo json_encode($arr);


?>