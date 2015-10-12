<?php 
include "GPIO.inc.php";

$DIGI = new GPIO();

/*
 * Write the word "run" in a text file.
 * Store it under /tmp/composerstatus.txt
 * If the file text is changed to "stop".
 * It will be read within the while loop of the composer.
 * This stops the composer.php process.
 */
/*
$statusFile = fopen("/tmp/composerstatus.txt", "w");
fwrite($status,"run");
fclose($status);
*/
$OUT = array();
$i=0;
$a=true;
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
$stop = "stop";

while ($a){
	$statusFile = fopen("/tmp/composerstatus.txt","r");
	$statusWord = trim(fgets($statusFile,5));
	fclose($statusFile);
	
	if ($statusWord == $stop)
	{
		$a = false;
	}
	
	set_time_limit(5);
	if ($i == 0){
	 $DIGI->setOutsingle(1,5);
	 $DIGI->setOutsingle(0,6);
	 $i++;
	}
	else 
	{
		$DIGI->setOutsingle(0,5);
		$DIGI->setOutsingle(1,6);
		$i=0;
	}
	usleep(20000);
}

?>