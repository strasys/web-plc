<?php 
include "GPIO.inc.php";

$DIGI = new GPIO();

$OUT = array();
$timeinterval = 1;
$endtime = microtime(true);
$i=0;
$a=0;
$OUT = array (	0 => 0,
		1 => 0,
		2 => 0,
		3 => 0,
		4 => 0,
		5 => 0,
		6 => 0,
		7 => 0
);

while ($a<1){
	//$OUT = $DIGI->getOut();
	
/*	for ($i=0; $i<8; $i++)
	{
	echo "Ausgang ".$i." = ".$OUT[$i]."<br>";
	}
*/
	
	if ($i < 8){
	$OUT[$i] = 1;
	 $DIGI->setOut($OUT);
	 $i++;
	}
	else 
	{
		$OUT = array (	0 => 0,
						1 => 0,
						2 => 0,
						3 => 0,
						4 => 0,
						5 => 0,
						6 => 0,
						7 => 0
					);
		$DIGI->setOut($OUT);
		$i=0;
	}
	usleep(2000000);
}


/*	$IN = $DIGI->getIn();
	
	for ($i=0; $i<4; $i++)
	{
		echo "Eingang ".$i." = ".$IN[$i]."<br>";
	}
	echo "micro time = ".microtime(true)."<br>";
*/

?>