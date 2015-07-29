<?php
include_once ('privateplc_php.ini.php');
session_start();
include_once ('authentification.inc.php');

unset($arr);
$setgetAnalog = $_POST["setgetAnalog"];
$inout = $_POST["InOut"];
$AOUTvalue = $_POST["AOUTvalue"]; //0 - 1023
$AOUTchannel = $_POST["AOUTchannel"];//1 or 2
$get = "g";
$set = "s";
$IN = "I";
$Out = "O";

//get Analog IN values
if ($flag)
{
	if (($setgetAnalog == $get) && $loginstatus)
	{
		if (($inout == $IN) && $loginstatus)
		{
			for ($i=2; $i<4; $i++){
			//we are looking at AIN channels 2 and 3 
			$channel = $i;
			exec(" /usr/lib/cgi-bin/AINOUThandler g I $channel", $output);
			}
			$arr = array(	'INvalue1' => $output[0],
					 		'INvalue2' => $output[1],
							'loginstatus' => $loginstatus,
							'adminstatus' => $adminstatus
						);
		}
		elseif (($inout == $Out) && $loginstatus)
		{
			for ($i=1; $i<3; $i++){
				$channel = $i;
				exec(" /usr/lib/cgi-bin/AINOUThandler g O $channel", $output);
			}
			$arr = array('OUTvalue1' => $output[0],
						 'OUTvalue2' => $output[1],
						'loginstatus' => $loginstatus,
						'adminstatus' => $adminstatus
						);
		}	
	}
	elseif (($setgetAnalog == $set) && $loginstatus)
	{
		if ($inout == $Out){
		exec("flock /tmp/AINOUThandler /usr/lib/cgi-bin/AINOUThandler s O $AOUTchannel $AOUTvalue");
		}
	}
}
else
{
	$arr = array(	'loginstatus' => $loginstatus,
					'adminstatus' => $adminstatus
				);
}

echo json_encode($arr);


?>