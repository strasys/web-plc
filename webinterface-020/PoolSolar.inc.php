<?php
/*
 * class Pool Solar functionality 
 *
 * Johannes Strasser
 * 31.08.2016
 * www.strasys.at
 *
 */

//include "PT1000.inc.php"; => must be set once in the code
//include "RTC.inc.php"; => must be set once in the code

class Solar
{
	/* 
	 * This function returns true in case of a heating through Solar
	 * true = activate  solar
	 * false = options for solar activation not given
	 */
	function getSolarFlag()
	{			
		$xml = simplexml_load_file("VDF.xml");
		$Temp = new PT1000();
		$RTC = new RTC();
		(bool) $SolarFlag = false;
		(bool) $waitFlag = false;
		
		$setPoolTemp = (int) $xml->SolarSetting[0]->poolTemp;
		$setCyclingWaterTemp = (int) $xml->SolarSetting[0]->backWaterTemp;
		$setDiffTemp = (int) $xml->SolarSetting[0]->diffTemp;

		$PoolTemp = $Temp->getPT1000(0);
		$RoofTemp = $Temp->getPT1000(2);
		$CyclingTemp = $Temp->getPT1000(3);
	//	$PoolTemp = 25;
	//	$RoofTemp = 32;


		//Unix time
		$actualTime = strtoTime($RTC->getstrTimeHHMM()); 

		// In a text file waiting times are stored.
		// waitmintime = UnixTime + x minutes => This is the minimum time the heating cycle is off after switch off.
		// runmintime = UnixTime + x minutes => This is the minimum time the heating cycle is on after switch on.
		// StatusSolar = shows the last status of the system => 0 = off, 1 = on
		$artemp = array();
		$i = 0;
		$TempControlFile = fopen("/tmp/PoolTempControlFile.txt", "r");
		if ($TempControlFile == false){
			$TempControlFile = fopen("/tmp/PoolTempControlFile.txt","w");
			fwrite($TempControlFile,"waitmintime:0\r\n");
			fwrite($TempControlFile,"runmintime:0\r\n");
			fwrite($TempControlFile,"StatusSolar:0\r\n");
			fclose($TempControlFile);
			$TempControlFile = fopen("/tmp/PoolTempControlFile.txt", "r");
		}
		if ($TempControlFile){
			$x=0;
			for($i=0;$i<3;$i++)
			{
				$line = fgets($TempControlFile,200);
				echo $line;
				$line = trim($line);
				list($var,$varval) = explode(":",$line);
				$artemp[$x] = $var;
				$artemp[$x+1] = $varval;
				$x=$x+2;
			}
			fclose($TempControlFile);
		}

		// Check if one of the waiting functions is activ!
		
		if (($artemp[1] > $actualTime) || ($artemp[3] > $actualTime)){
			$waitFlag = true;
		}

		if (($artemp[5] == 1)&&($waitFlag == true)){
			$SolarFlag = true;
		}
		else if (($artemp[5] == 0)&&($waitFlag == true)){
			$SolarFlag = false;
		}

		if ($waitFlag == false){
			if ((($RoofTemp - $PoolTemp) >= $setDiffTemp) && ($PoolTemp <= $setPoolTemp))
			{
				$SolarFlag = true;
			
				if ($artemp[5] == 0){
					$artemp[3] = $actualTime + (60*2);
					$artemp[5] = 1;
				}	
			} else {
				$SolarFlag = false;

				if ($artemp[5] == 1){
					$artemp[1] = $actualTime + (60*2);
					$artemp[5] = 0;	
					$SolarFlag = true;
				}
			}

			$TempControlFile = fopen("/tmp/PoolTempControlFile.txt", "w");
			$i = 0;
			for ($i=0;$i<6;$i=$i+2){
				fwrite($TempControlFile,$artemp[$i].":".$artemp[$i+1]."\r\n");	
			}	
		 	fclose($TempControlFile);	
		}

		return (bool) $SolarFlag;
	}
	/*
	 * This function returns a boolean value. 
	 * true = Operation Mode = AUTO
	 * false = Operation Mode = OFF
	 */
	function getopModeFlag()
	{
		$xml = simplexml_load_file("VDF.xml");		
		(bool) $OperationFlag = false;

		$strOperationMode = (string) $xml->SolarSetting[0]->operationMode;
		if ($strOperationMode == 'AUTO'){
			$OperationFlag = true;
		}
		elseif ($strOperationMode == 'OFF'){
			$OperationFlag = false;
		}

		return (bool) $OperationFlag;
	}


}
?>
