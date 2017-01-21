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
$getLogData = $_POST["getLogData"];

$get = "g";
$set = "s";
$write = "w";
$check = "c";

$error_Log = array (
	'databaseconnection' => 0,
	'owner_reg' => 0
);

//get Log status
if ($getLogData == $get){
	transfer_javascript($loginstatus, $adminstatus);
}

if (($_POST['CheckVeryCode'] == $check) && ($adminstatus)){ 

	unset ($data_string, $data, $deviceIDval);
	$deviceIDval = trim(getDeviceID());

	$data = array(
		'deviceID' => $deviceIDval,
		'veriCode' => $_POST['veryCode'],
		'email' => $_POST['email'],
		'progkey' => "V"
	);

	$data_string="";
	foreach($data as $key=>$value) 
	{
	 $data_string = $data_string.'&'.$key.'='.$value; 
	}
	$ch = curl_init();
	curl_setopt($ch, CURLOPT_URL, 'https://www.strasys.at/dns/getRegistrationData.php');
	curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
	curl_setopt($ch, CURLOPT_FOLLOWLOCATION, true);
	curl_setopt($ch, CURLOPT_POST, count($data));
	//curl_setopt($ch, CURLOPT_CUSTOMREQUEST, "POST");
	curl_setopt($ch, CURLOPT_POSTFIELDS, $data_string);
	curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, 0);
	curl_setopt($ch, CURLOPT_TIMEOUT, 5);
	curl_setopt($ch, CURLOPT_CONNECTTIMEOUT, 5);
	$return = curl_exec($ch);
	curl_close($ch);

	Verification_return($return,$_POST['email'],$_POST['username']);	
}

function Verification_return($return,$email,$username){

	$returnData = explode("&", $return);
	$returnDataValues = array();
	for ($i=0;$i<2;$i++){
		$temp = explode(":", $returnData[$i]);
		$returnDataValues[$i] = $temp[1];
	}

	$returnDataFinal = array(
		'writeVeryData' => $returnDataValues[0],
		'veryCodeVerification' => $returnDataValues[1],
		'email' => $email,
		'username' => $username
		);

	echo json_encode($returnDataFinal);	
}


if (($_POST['OwnerRegistration'] == $set) && ($adminstatus)){
	databaseIfAlreadyRegistered();
	echo json_encode($error_Log);
}

if (($_POST['OwnerRegistration'] == $write) && $adminstatus){
	databaseTransferOwnerRegistration();
}

function getDeviceID (){
	$xml = simplexml_load_file("VDF.xml");
	$deviceIDinfo = (string) $xml->DeviceInfo[0]->DeviceID;
	return $deviceIDinfo;
}

function databaseTransferOwnerRegistration(){
	$deviceIDval = trim(getDeviceID());
	unset ($data_string, $data);

	$data = array(
		'deviceID' => $deviceIDval,
		'gender' => $_POST['gender'],
		'firstName' => $_POST['firstName'],
		'FamilyName' => $_POST['FamilyName'],
		'street' => $_POST['street'],
		'number' => $_POST['number'],
		'PLZ' => $_POST['PLZ'],
		'City' => $_POST['City'],
		'Country' => $_POST['Country'],
		'email' => $_POST['email'],
		'password' => $_POST['password'],
		'progkey' => "R"
		);
	$data_string="";
	foreach($data as $key=>$value) 
	{
	 $data_string = $data_string.'&'.$key.'='.$value; 
	}
	$ch = curl_init();
	curl_setopt($ch, CURLOPT_URL, 'https://www.strasys.at/dns/getRegistrationData.php');
	curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
	curl_setopt($ch, CURLOPT_FOLLOWLOCATION, true);
	curl_setopt($ch, CURLOPT_POST, count($data));
	//curl_setopt($ch, CURLOPT_CUSTOMREQUEST, "POST");
	curl_setopt($ch, CURLOPT_POSTFIELDS, $data_string);
	curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, 0);
	curl_setopt($ch, CURLOPT_TIMEOUT, 5);
	curl_setopt($ch, CURLOPT_CONNECTTIMEOUT, 5);
	$return = curl_exec($ch);
	curl_close($ch);

	DatabaseRegistration_return($return);
}

function DatabaseRegistration_return($return){

	$returnData = explode("&", $return);
	$returnDataValues = array();
	for ($i=0;$i<9;$i++){
		$temp = explode(":", $returnData[$i]);
		$returnDataValues[$i] = $temp[1];
	}

	$returnDataFinal = array(
		'product_registered' => $returnDataValues[0],
		'product_registerID_exist' => $returnDataValues[1],
		'customer_register_email' => $returnDataValues[2],
		'customer_exists_flag' => $returnDataValues[3],
		'database_write' => $returnDataValues[4],
		'write_ID_customer' => $returnDataValues[5],
		'send_email_verification' => $returnDataValues[6],
		'email' => $returnDataValues[7],
		'username' => $returnDataValues[8]
	);
	// if database write is true => set email and username local
	if ($returnDataValues[4] == 1){
		writeRegXML($returnDataValues[7], $returnDataValues[8]);
	}


	echo json_encode($returnDataFinal);	
}

function writeRegXML($email, $username){
	$xml=simplexml_load_file("VDF.xml") or die("Error: Cannot create object");
	$xml->Owner[0]-> email = $email;
	$xml->Owner[0]-> userName = $username;
	$xml->asXML("VDF.xml");
}


function databaseIfAlreadyRegistered(){
	//open mySQL - Database
	/* Open a connection */
/*	$db = mysqli_init();
	$db->ssl_set(NULL, NULL, '../sql/sqlca.pem', NULL, NULL);
	$link = mysqli_real_connect ($db, 'sql458.your-server.de', 'strajoha_r', '3lCwz58UW6wN00RK', 'product_database', 3306, NULL, MYSQLI_CLIENT_SSL);
//	$customer_r = new mysqli("https://sql458.strasys.at", "strajoha_r", "3lCwz58UW6wN00RK", "product_database");
	/* check connection */
/*
	echo  "hier";
	if (mysqli_connect_errno()) {
		$error_Log['databaseconnection'] = "Connect failed: ".mysqli_connect_error;
	    exit();
	} else {
		$error_Log['databaseconnection'] = 0;
	}
	echo "hier1";
	$email = $_POST['email'];
	$result = $link->query("SELECT * FROM customer_registration WHERE e-mail='$email'");
	$row = $result->fetch_array(MYSQL_ASSOC);
	//$row["password"]."<br>";
	if (!(isset($row))){

		$error_Log['owner_reg'] = "owner not registered";
	}

	$result->close();
	$link->close();
*/
}

/*
	"gender="+gender+
	"&firstName="+firstName_str+
	"&FamilyName="+FamilyName_str+
	"&street="+street_str+
	"&number="+number_str+
	"&PLZ="+PLZ_str+
	"&City="+City_str+
	"&Country="+Country_str+
	"&email="+email_str+
	"&OwnerRegistration=set"
 */
function transfer_javascript($loginstatus, $adminstatus)	
{
	$arr = array(
			'loginstatus' => $loginstatus,
			'adminstatus' => $adminstatus
			);
	
	echo json_encode($arr);
}

?>
