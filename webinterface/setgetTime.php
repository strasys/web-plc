<?php
	$hh = $_POST["hh"];
	$mm = $_POST["mm"];
	$ss = $_POST["ss"];
	$ausgabe;
	unset($ausgabe);
	
	if ($hh == !null){
		exec("./cgi-bin/RTChandler s t $hh $mm $ss", &$ausgabe);
		$arr = array('hh' => $ausgabe[4],'mm' => $ausgabe[5],'ss' => $ausgabe[6]);
		echo json_encode($arr);
	}
	
	exec("./cgi-bin/RTChandler", &$ausgabe);
		$arr = array('hh' => $ausgabe[4],'mm' => $ausgabe[5],'ss' => $ausgabe[6]);
		echo json_encode($arr);
?>
