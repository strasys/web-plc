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
unset($ValueTyp, $Value);
$getLogData = $_POST["getLogData"];
$Value = $_POST["Value"];
$ValueTyp = $_POST["ValueTyp"];
$get = "g";
$set = "s";
$NiveauOvertraveltime = "NiveauOvertraveltime";
$operationMode = "operationMode";

//get Log status
if ($getLogData == $get){
	transfer_javascript($loginstatus, $adminstatus);
}

if (($ValueTyp == $NiveauOvertraveltime) && ($adminstatus)){
	$xml=simplexml_load_file("VDF.xml") or die("Error: Cannot create object");
	$xml->LevelControl[0]->Overtraveltime = $_POST["Value"];
	echo $xml->asXML("VDF.xml");
}

if (($ValueTyp == $operationMode) && ($adminstatus)){
	$xml=simplexml_load_file("VDF.xml") or die("Error: Cannot create object");
	$xml->LevelControl[0]->operationMode = $_POST["Value"];
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
