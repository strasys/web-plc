/**
 * Program for start side.
 * 
 * Johannes Strasser
 * 03.10.2016
 * www.strasys.at
 * 
 */

sortoutcache = new Date();

function setgetrequestServer(setget, url, cfunc, senddata){
	xhttp = new XMLHttpRequest();
	xhttp.onreadystatechange = cfunc;
	xhttp.open(setget,url,true);
	xhttp.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
	xhttp.send(senddata);
}


function getStatusLogin(callback1){
	setgetrequestServer("post","index.php",function()
	{
		if (xhttp.readyState==4 && xhttp.status==200)
		{
			var getHomeLogin = JSON.parse(xhttp.responseText); 
		
			LoginStatus = [(getHomeLogin.loginstatus),
		               (getHomeLogin.adminstatus)
		               ];

			if (callback1){
			callback1();
			}
		}
	},"getLoginStatus=g&getData=g");		
}


function getServerData(callback2){
	setgetrequestServer("post","index.php",function()
	{
		if (xhttp.readyState==4 && xhttp.status==200)
		{
			var getStatusInfo = JSON.parse(xhttp.responseText); 
		
			StatusData = [	(getStatusInfo.loginstatus),
					(getStatusInfo.adminstatus),
					(getStatusInfo.pooltemp),
					(getStatusInfo.outsidetemp),
					(getStatusInfo.OperationMode),
					(getStatusInfo.statusMixer),
					(getStatusInfo.statusPump),
					(getStatusInfo.statusPoolLight),
					(getStatusInfo.statusOutLight),
					(getStatusInfo.statusFreshwaterValve),
					(getStatusInfo.statusNiveauSensor),
					(getStatusInfo.statusMixerSolar),
					(getStatusInfo.statusMixerBypass)
						               	];

			if (callback2){
			callback2();
			}
		}
	},"getLoginStatus=g&getData=g");		
}

function setServerData(OutNumber,OutValue,callback5){
	setgetrequestServer("post","index.php",function()
	{
		if (xhttp.readyState==4 && xhttp.status==200)
		{
		if (callback5){
			callback5();
			}
		}

	},"getData=s&setOutNumber="+OutNumber+"&setOutValue="+OutValue);		
}

function getXMLData(callback4){
	var getXMLData;
	setgetrequestServer("GET","VDF.xml?sortoutcache="+sortoutcache.valueOf(),function(){
		
		if (xhttp.readyState==4 && xhttp.status==200){
			var getXMLData = xhttp.responseXML;
			var digiIN = getXMLData.getElementsByTagName("GPIOIN");
			var digiOUT = getXMLData.getElementsByTagName("GPIOOUT");
			var PT1000 = getXMLData.getElementsByTagName("PT1000");

			document.getElementById("labelTempPool").innerHTML = PT1000[0].getElementsByTagName("PT1000Name")[0].childNodes[0].nodeValue;
			document.getElementById("labelTempOutside").innerHTML = PT1000[1].getElementsByTagName("PT1000Name")[0].childNodes[0].nodeValue;
			document.getElementById("buttonOutText2").innerHTML = digiOUT[2].getElementsByTagName("OutputName")[0].childNodes[0].nodeValue;
			document.getElementById("buttonOutText3").innerHTML = digiOUT[3].getElementsByTagName("OutputName")[0].childNodes[0].nodeValue;
			document.getElementById("labelStatusPump").innerHTML = digiOUT[1].getElementsByTagName("OutputName")[0].childNodes[0].nodeValue;
			document.getElementById("labelStatusWaterValve").innerHTML = digiOUT[4].getElementsByTagName("OutputName")[0].childNodes[0].nodeValue;
			document.getElementById("labelStatusNiveauSensor").innerHTML = digiIN[0].getElementsByTagName("InputName")[0].childNodes[0].nodeValue;
			document.getElementById("labelStatusMixer").innerHTML = digiOUT[0].getElementsByTagName("OutputName")[0].childNodes[0].nodeValue;
			
		if (callback4){
			callback4();
			}
		}	
	});
}

function setValues(callback6){
	document.getElementById("badgeTempPool").innerHTML = StatusData[2]+"°C";
	document.getElementById("badgeTempOutside").innerHTML = StatusData[3]+"°C";
	//operation mode indication
	if (StatusData[4] == 1){
		document.getElementById("badgeOperationMode").innerHTML = "AUTO";
		}
	else if (StatusData[4] == 0){
		document.getElementById("badgeOperationMode").innerHTML = "HAND";
	}
	//status Mixer
	if (StatusData[5] == 1){
		document.getElementById("badgeStatusMixer").innerHTML = "HEIZEN";
		}
	else if (StatusData[5] == 0){
		document.getElementById("badgeStatusMixer").innerHTML = "BYPASS";
	}

	var TextOut = new Array();
	var a = 0;
	for (i=6; i<10; i++){	
		if (StatusData[i] == 1){
			TextOut[a] = "EIN"; 
			}
		else if (StatusData[i] == 0){
			TextOut[a] = "AUS";
		}
		a++;
	}
	document.getElementById("badgeStatusPump").innerHTML = TextOut[0];
	document.getElementById("badgeOut2").innerHTML = TextOut[1];
	document.getElementById("badgeOut3").innerHTML = TextOut[2];
	document.getElementById("badgeStatusWaterValve").innerHTML = TextOut[3];
	//status Niveausensor
	if (StatusData[10] == 1){
		document.getElementById("badgeStatusNiveauSensor").innerHTML = "OK";
		}
	else if (StatusData[10] == 0){
		document.getElementById("badgeStatusNiveauSensor").innerHTML = "leer";
	}

	if (callback6){
		callback6();
	}
}

function setOutstatus(Number){
	var OutValue = 0;
	if (Number == 2){
		//check actual status Out2
		if (StatusData[7] == 1){
			OutValue = 0;	
		} else {
			OutValue = 1;
		}
	}
	else if (Number == 3){
		//check actual status Out3
		if (StatusData[8] == 1){
			OutValue = 0;	
		} else {
			OutValue = 1;
		}	
	}
	setServerData(Number,OutValue,function(){
		refresh();
	});	
}

function refresh(){
	getServerData(function(){
		setValues(function(){
			setTimeout(function(){refresh()}, 10000);
		});
	});
}

// load functions ad webpage opening
function startatLoad(){
	loadNavbar(function(){
		getXMLData(function(){
			getServerData(function(){
				refresh();	
			});
		});
	});		
}

window.onload=startatLoad();

//Load the top fixed navigation bar and highlight the 
//active site roots.
//Check of the operater is already loged on the system.
function loadNavbar(callback3){
	getStatusLogin(function(){
		if(LoginStatus[0]){	
			$(document).ready(function(){
				$("#mainNavbar").load("navbar.html", function(){
					$("#navbarHome").addClass("active");
					$("#navbarlogin").hide();
					$("#panelAdditionalFunctions").hide();

					if (!LoginStatus[1])
						{
						$("#navbarSet").hide();
						}
				 });
			});
		}
		else
		{
			$(document).ready(function(){
				$("#mainNavbar").load("navbar.html?ver=0", function(){
					$("#navbarHome").addClass("active");
					$("#navbarlogout").hide();
					$("#navbarFunction").hide();
					$("#navbarSet").hide();
					$("#navbarHelp").hide();
					$("#panelStatusOperation").hide();
					$("#panelStatusActuators").hide();
					$("#panelAdditionalFunctions").hide();
				});
			});

		}
		if (callback3){
			callback3();
		}
	});
}

