<?php 
error_reporting(E_ALL | E_STRICT);
// Um die Fehler auch auszugeben, aktivieren wir die Ausgabe
ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
//

include "GPIO.inc.php";
include "composerloopcontrol.inc.php";
include "PT1000.inc.php";
include "RTC.inc.php";
$DIGI = new GPIO();
$PT1000 = new PT1000();
$loopstatuscontrol = new composerloopcontrol();
$RTC = new RTC();
$xml = simplexml_load_file("VDF.xml");
date_default_timezone_set('CET');


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

//while ($loopstatus){
	/*
	 * Loop control function.
	 * Attention: Without the implementation of the 
	 * composerloopcontrol class the loop can not be operated
	 * in a defined and controlled mode.
	 * => run = true/ stop = false
	 */
	$loopstatus = $loopstatuscontrol->runstop();
	echo $loopstatus."<br>";

//	$loopstatus = true;
	//TODO: Add log file function.
	/*
	 * Without setting a time limit the loop will stop after a while.
	 *Further this function should secure the run of the system.
	 */
	set_time_limit(5); //Set to 5 seconds.
	
	
	/*
	 * Following block controls the Cleaning intervals
	 */
	$CleaningFlag = (string) $xml->CleaningSetting[0]->OperationMode;
	$SolarFlag = (string) $xml->SolarSetting[0]->operationMode;
	$PumpONOFFflag = false;

	if ($CleaningFlag == 'AUTO'){
		unset($PumpStatus);
		$PumpStatus = $DIGI->getOutSingle(1);
	//	echo "Status Pin 1 = ".$PumpStatus."<br>";
		$actualTime = (int) strtoTime($RTC->getstrTimeHHMM());
	//	echo "actualTime =".$actualTime."<br>";
		$NumberNodes = (int) $xml->CleaningInterval->count();
		for ($i=0;$i<$NumberNodes;$i++)
		{
			$CStart = (int) strtoTime($xml->CleaningInterval[$i]->Start);
			$CStop = (int) strtoTime($xml->CleaningInterval[$i]->Stop);
			echo "actualTime =".$actualTime."<br>";

		//	echo "CStart = ".$CStart."<br>";
		//	echo "CStop = ".$CStop."<br>";
		//	echo "Status: ".($CStart > $actualTime)."<br>";
		//	echo "Status: ".($CStop < $actualTime)."<br>";

			if (!($CStart > $actualTime)  && !($CStop < $actualTime)){
				$PumpONOFFflag = true;
		//		echo "PumpONOFFflag = true<br>";
				break 1;
			}
		}
	//	echo "Ein / Aus - Pumpe logik: ".($PumpONOFFflag = true)."<br>";
	//	echo "Ein / Aus - Pumpe logik: ".($PumpStatus == 0)."<br>";

		if (($PumpONOFFflag = true) && ($PumpStatus == 0)){
			$DIGI->setOutsingle(1,1);
		//	echo "Logik 1<br>";
		//	echo "Logik 1_1".($PumpONOFFflag = true)."Logik 1_2".($PumpStatus == 0)."<br>"; 	
		}
		elseif (($PumpONOFFflag = false)){
			$DIGI->setOutsingle(1,0);
			echo "Logik 2<br>";
			}
	}
	elseif ($CleaningFlag == 'OFF'){
		$DIGI->setOutsingle(1,0);
		//echo "Logik 3<br>";		
	}

/*	
	if ($SolarFlag == 'AUTO'){
		$TempRoof = $PT1000->getPT1000(3);
		$TempTank = $PT1000->getPT1000(0);
		$TempbackFlow = $PT1000->getPT1000(1);		
		$XMLbackWaterTemp = (int) ($xml->SolarSetting[0]->backWaterTemp);
		$XMLdiffTemp = (int) ($xml->SolarSetting[0]->diffTemp);
		$XMLpoolTemp = (int) ($xml->SolarSetting[0]->poolTemp);
		$StatusINmixerBypass = $DIGI->getInSingle(1);
		$StatusINmixerSolar = $DIGI->getInSingle(2);
		$StatusPump = $DIGI->getOutSingle(1);
		echo "StatusINmixer = ".$StatusINmixerBypass."<br>";
		echo "StatusINmixer = ".$StatusINmixerSolar."<br>";
		$TempRoof = 40;
		$TempbackFlow = 20;
		if ((($TempbackFlow + $XMLdiffTemp) < $TempRoof) && ($TempbackFlow <= $XMLbackWaterTemp)){
			if ($StatusINmixerBypass == 0){
				$DIGI->setOutsingle(0,1);
			}

			if ($StatusINmixerSolar == 0){
				if ($StatusPump == 0){
					//Position Mixer to Solar
					$DIGI->setOutsingle(0,1);
				}
			}
		}
		elseif(!($PumpONOFFflag = false)){
				//Switch off Pump
				$DIGI->setOutsingle(1,0);
			}
	}
	
	elseif($SolarFlag == 'OFF'){
		$StatusINmixerBypass = $DIGI->getInSingle(1);
		$StatusINmixerSolar = $DIGI->getInSingle(2);
		$StatusPump = $DIGI->getOutSingle(1);

		if ($StatusINmixerSolar == 0){
			$DIGI->setOutsingle(0,0);
			}
		if (($StatusPump == 1) && ($PumpONOFFflag = false)){
			$DIGI->setOutsingle(1,0);
 			}
	}
 */		

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
 
//}

?>
