<?php
$ausgabe;
$arr;
unset($ausgabe);
unset($arr);
$setgetGPIO = $_POST["setgetGPIO"];
$GPIOnum = $_POST["GPIOnum"];
$GPIOvalue = $_POST["GPIOvalue"];
$g = "g";
$s = "s";

if ($setgetGPIO == $g){
		exec("./cgi-bin/GPIOhandler g", &$ausgabe);
		}
		
elseif ($setgetGPIO == $s){
		exec("flock /tmp/flockGPIO ./cgi-bin/GPIOhandler s $GPIOnum $GPIOvalue", &$ausgabe);
		}

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