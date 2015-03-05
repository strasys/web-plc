<?php

$ausgabe;
$arr;
$ButtonFlag = 0;
$InputFlag = 0;
unset($ausgabe);
unset($arr);
unset($ButtonText);
$setgetGPIO = $_POST["setgetGPIO"];
$InOut = $_POST["InOut"];
$GPIOnum = $_POST["GPIOnum"];
$GPIOvalue = $_POST["GPIOvalue"];
$ButtonFlag = $_POST["ButtonFlag"];
$InputFlag = $_POST["InputFlag"];
$g = "g";
$s = "s";
$I = "i";
$O = "o";
$Bf = 1;
$If = 1;

$ButtonText = array( 0 => 	$_POST["ButtonText0"],
					 1 => 	$_POST["ButtonText1"],
					 2 =>	$_POST["ButtonText2"],
					 3 =>	$_POST["ButtonText3"],
					 4 =>	$_POST["ButtonText4"],
					 5 =>	$_POST["ButtonText5"],
					 6 =>	$_POST["ButtonText6"],
					 7 =>	$_POST["ButtonText7"]
);

$InputText = array( 0 => $_POST["InputText0"],
					1 => $_POST["InputText1"],
					2 => $_POST["InputText2"],
					3 => $_POST["InputText3"]
);

if ($setgetGPIO == $g){
	if ($InOut == $O){
		exec("./cgi-bin/GPIOhandler g O", &$ausgabe);
		
		$arr = array(	'OUT1' => $ausgabe[0],
						'OUT2' => $ausgabe[1],
						'OUT3' => $ausgabe[2],
						'OUT4' => $ausgabe[3],
						'OUT5' => $ausgabe[4],
						'OUT6' => $ausgabe[5],
						'OUT7' => $ausgabe[6],
						'OUT8' => $ausgabe[7]
					);
		}
	elseif ($InOut == $I){
		exec("./cgi-bin/GPIOhandler g I", &$ausgabe);
		
		$arr = array(	'IN1' => $ausgabe[0],
						'IN2' => $ausgabe[1],
						'IN3' => $ausgabe[2],
						'IN4' => $ausgabe[3],
					);
		}
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

elseif ($InputFlag == $If){
	$xml=simplexml_load_file("GPIOin.xml") or die("Error: Cannot create object");
	for ($i=0; $i<4; $i++){
	$xml->IN[$i]->InputName = $InputText[$i];
	}
	echo $xml->asXML("GPIOin.xml");
}
/*
for ($i=0; $i<8; $i++){
	$ausgabe[i] = utf8_encode($ausgabe[i]);
}
*/

echo json_encode($arr);

?>