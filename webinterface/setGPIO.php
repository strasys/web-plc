<?php

$ausgabe;
$arr;
$ButtonFlag = 0;
unset($ausgabe);
unset($arr);
unset($ButtonText);
$setgetGPIO = $_POST["setgetGPIO"];
$GPIOnum = $_POST["GPIOnum"];
$GPIOvalue = $_POST["GPIOvalue"];
$ButtonFlag = $_POST["ButtonFlag"];
$g = "g";
$s = "s";
$Bf = 1;

$ButtonText = array( 0 => 	$_POST["ButtonText0"],
					 1 => 	$_POST["ButtonText1"],
					 2 =>	$_POST["ButtonText2"],
					 3 =>	$_POST["ButtonText3"],
					 4 =>	$_POST["ButtonText4"],
					 5 =>	$_POST["ButtonText5"],
					 6 =>	$_POST["ButtonText6"],
					 7 =>	$_POST["ButtonText7"]
);

if ($setgetGPIO == $g){
		exec("./cgi-bin/GPIOhandler g", &$ausgabe);
		}
		
elseif ($setgetGPIO == $s){
		exec("flock /tmp/flockGPIO ./cgi-bin/GPIOhandler s $GPIOnum $GPIOvalue", &$ausgabe);
		}
	
if ($ButtonFlag == $Bf){
$xml=simplexml_load_file("GPIOout.xml") or die("Error: Cannot create object");
	for ($i=0; $i<8; $i++){
	$xml->OUT[$i]->ButtonName = $ButtonText[$i];
	}
	echo $xml->asXML("GPIOout.xml");
}
/*
for ($i=0; $i<8; $i++){
	$ausgabe[i] = utf8_encode($ausgabe[i]);
}
*/

$arr = array(	'OUT1' => $ausgabe[0],
				'OUT2' => $ausgabe[1],
				'OUT3' => $ausgabe[2],
				'OUT4' => $ausgabe[3],
				'OUT5' => $ausgabe[4],
				'OUT6' => $ausgabe[5],
				'OUT7' => $ausgabe[6],
				'OUT8' => $ausgabe[7]
			);


echo json_encode($arr);

?>