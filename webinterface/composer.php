<?php 
include "GPIO.inc.php";
include "composerloopcontrol.inc.php";
$DIGI = new GPIO();
$loopstatuscontrol = new composerloopcontrol();

/*
 * To initially start the process of the 
 * composer loop $loopstatus must be set to true.
 */  
$loopstatus = true;

/*
 * Define basic settings.
 */

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

while ($loopstatus){
	/*
	 * Loop control function.
	 * Attention: Without the implementation of the 
	 * composerloopcontrol class the loop can not be operated
	 * in a defined and controlled mode.
	 * => run = true/ stop = false
	 */
	$loopstatus = $loopstatuscontrol->runstop();
	//TODO: Add log file function.
	/*
	 * Without setting a time limit the loop will stop after a while.
	 *Further this function should secure the run of the system.
	 */
	set_time_limit(5); //Set to 5 seconds.
	
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
	usleep(150000); //Time set in µs!
	
	/*
	 * Define privatePLC status if $status = false.
	 * Clarify what the DigiOut and Analogue Out settings should be
	 * in case of a stop of the script.
	 */
	
	if ($loopstatus == false)
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
	}
}

?>