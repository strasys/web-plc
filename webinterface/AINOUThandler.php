<?php

unset($arr);
$setgetAnalog = $_POST["setgetAnalog"];
$inout = $_POST["InOut"];
$AOUTvalue = $_POST["AOUTvalue"]; //0 - 1023
$AOUTchannel = $_POST["AOUTchannel"];//1 or 2
$get = "g";
$set = "s";
$IN = "I";
$Out = "O";

//$inout = "O";
//$setgetAnalog = "g";


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
			exec(" /usr/lib/cgi-bin/AINOUThandler g O $channel", $output1);
		}
		$arr = array('OUTvalue1' => $output1[0],
					'OUTvalue2' => $output1[1]
					);
		//echo  "OUTvalue1 = $output1[0]";
		//echo "Test";
	}	
}

elseif ($setgetAnalog == $set){
	if ($inout == $Out){
	exec("flock /tmp/AINOUThandler /usr/lib/cgi-bin/AINOUThandler s O $AOUTchannel $AOUTvalue");
	}

}

echo json_encode($arr);


?>