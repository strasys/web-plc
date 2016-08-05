<?php
//error_reporting(E_ALL | E_STRICT);
// Um die Fehler auch auszugeben, aktivieren wir die Ausgabe
//ini_set('display_errors', 1);
//ini_set('display_startup_errors', 1);
//
include_once ('privateplc_php.ini.php');
session_start();
include_once ('authentification.inc.php');
$arr;
unset($arr);
unset($TempTyp, $TempValue);
$getLogData = $_POST["getLogData"];
$TempValue = $_POST["TempValue"];
$TempTyp = $_POST["TempTyp"];
$get = "g";
$set = "s";
$TempBackWater = "TempBackWater";
$DifferenceTemp = "DifferenceTemp";
$PoolTemp = "PoolTemp";
$operationMode = "operationMode";

//get Log status
if ($getLogData == $get){
	transfer_javascript($loginstatus, $adminstatus);
}

if (($TempTyp == $TempBackWater) && ($adminstatus)){
	$xml=simplexml_load_file("VDF.xml") or die("Error: Cannot create object");
	$xml->SolarSetting[0]->backWaterTemp = $_POST["TempValue"];
	echo $xml->asXML("VDF.xml");
}

if (($TempTyp == $DifferenceTemp) && ($adminstatus)){
	$xml=simplexml_load_file("VDF.xml") or die("Error: Cannot create object");
	$xml->SolarSetting[0]->diffTemp = $_POST["TempValue"];
	echo $xml->asXML("VDF.xml");
}

if (($TempTyp == $PoolTemp) && ($adminstatus)){
	$xml=simplexml_load_file("VDF.xml") or die("Error: Cannot create object");
	$xml->SolarSetting[0]->poolTemp = $_POST["TempValue"];
	echo $xml->asXML("VDF.xml");
}

if (($TempTyp == $operationMode) && ($adminstatus)){
	$xml=simplexml_load_file("VDF.xml") or die("Error: Cannot create object");
	$xml->SolarSetting[0]->operationMode = $_POST["TempValue"];
	echo $xml->asXML("VDF.xml");
}


function transfer_javascript($loginstatus, $adminstatus)	
{
	$arr = array(
			'loginstatus' => $loginstatus,
			'adminstatus' => $adminstatus
			);
	
	echo json_encode($arr);
}

?>
