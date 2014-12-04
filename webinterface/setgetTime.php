<?php
	$td;
	$ausgabe;
	$arr;
	unset($td);
	unset($ausgabe);
	unset($arr);
	$td = 0;
	$td = $_POST["td"];
	$hh = $_POST["hh"];
	$mm = $_POST["mm"];
	$ss = $_POST["ss"];
	$Day = $_POST["Day"];
	$Month = $_POST["Month"];
	$Year = $_POST["Year"];
	$t = "t";
	$d = "d";
	
	if ($td == $t){
		exec("flock /tmp/flockRTChandler ./cgi-bin/RTChandler s t $hh $mm $ss", &$ausgabe);
		}
	elseif ($td == $d){
		exec("flock /tmp/flockRTChandler ./cgi-bin/RTChandler s d $Day $Month $Year", &$ausgabe);
		}
	elseif ($td == 0) {
	exec("./cgi-bin/RTChandler", &$ausgabe);	
	}
	
	$arr = array(	'Day' => $ausgabe[0],
					'Month' => $ausgabe[1],
					'Year' => $ausgabe[2],
					'hh' => $ausgabe[3],
					'mm' => $ausgabe[4],
					'ss' => $ausgabe[5]);
	echo json_encode($arr);
?>
