/**
 * pushButtonSensing.js
 * The pushButtonSensing function is the
 * front end for the definition of the digital inputs 
 * which should be actuated by a push button.
 * Further, the run stop signales are handled.
 * 
 * Johannes Strasser
 * 19.10.2015
 * www.strasys.at
 */

/*
 * Asynchron server send function.
 */
function setgetServer(setget, url, cfunc, senddata){
	xhttp = new XMLHttpRequest();
	xhttp.onreadystatechange = cfunc;
	xhttp.open(setget,url,true);
	xhttp.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
	xhttp.send(senddata);
}
/*
 * This function get's the login status.
 */

function getStatusLogin(callback1){
		setgetServer("post","pushButtonSensinghandler.php",function()
		{
			if (xhttp.readyState==4 && xhttp.status==200)
			{
			var getpushButtonSensingLogin = JSON.parse(xhttp.responseText); 
			
			LoginStatus = [(getpushButtonSensingLogin.loginstatus),
			               (getpushButtonSensingLogin.adminstatus)
			               ];
				if (callback1){
				callback1();
				}
			}
		},"getLoginStatus=g");		
}
/*
 * This function set's and get's the status of the push button sensing process.
 * If the sensing function is running st = 1 else 0.
 */
function setgetStatuspushButtonSensingProcess(setget,setrunstopStatus,inputActivationStatus, callback2){
		setgetServer("post","pushButtonSensinghandler.php",function()
			{
				if (xhttp.readyState==4 && xhttp.status==200)
				{
				var setgetpushButtonSensingProcessStatus = JSON.parse(xhttp.responseText); 
				
				StatuspushButtonSensingProcess = [(setgetpushButtonSensingProcessStatus.runstop)
				                         ];
					if (callback2){
					callback2();
					}
				}
			},"setgetpushButtonSensingProcessStatus="+setget+"&setrunstopStatus="+setrunstopStatus+
			"&sensingChannels="+inputActivationStatus);		
}



/*
 * This function sets the color and the badge description of the pushButtonSensing button.
 */
function setButtonColorBadge(ButtonNumber){
	 switch (ButtonNumber){
	 case 0:
			if(StatuspushButtonSensingProcess[0] == 1){
				span = document.getElementById("badgebuttonpushButtonSensingScriptOnOff");
				span.textContent = "EIN";
				button = document.getElementById("buttonpushButtonSensingOnOff");
				button.getAttributeNode("class").value = "btn btn-success";
			}
			if(StatuspushButtonSensingProcess[0] == 0) {
				span = document.getElementById("badgebuttonpushButtonSensingScriptOnOff");
				span.textContent = "AUS";
				button = document.getElementById("buttonpushButtonSensingOnOff");
				button.getAttributeNode("class").value = "btn btn-danger";
			}
			break;
	 }
	 
}

sortoutcache = new Date();

//This function will be called once on start.
//The names of the inputs are stored in a XML file on the server.
function getNamingXMLData(callback3){
	setgetServer("GET","GPIOin.xml?sortoutcache="+sortoutcache.valueOf(),function()
			{
				if (xhttp.readyState==4 && xhttp.status==200)
					{
					var getXMLData = xhttp.responseXML;
					var w = getXMLData.getElementsByTagName("InputName");
					var z = getXMLData.getElementsByTagName("InputName");
					var i = 0;
					for (i=0; i<w.length; i++){
						document.getElementById("checkboxTextpushButtonSensing"+i).innerHTML=z[i].childNodes[0].nodeValue;	
						}
					if (callback3){
						callback3();
					}
					
					}
			});		
}
/*
 * Get and set either an input is set for push button sensing.
 */

function setgetpushButtonSensingActivation(setget, callback4){
	inputActivationStatus = new Array();
	if (setget == "set"){
		for (i=0;i<4;i++){
			if (document.getElementById("checkboxpushButtonSensing"+i).checked){
			inputActivationStatus[i] = 1;
			}
			else
			{
				inputActivationStatus[i] = 0;
			}
		}
	}
	if(setget == "get"){
		
	}
	if (callback4){
		callback4();
	}
	
}

function ButtonpushButtonSensingAction(ButtonNumber){
	switch (ButtonNumber){
	case 0:
		if(StatuspushButtonSensingProcess[0] == 1){
			setgetStatuspushButtonSensingProcess("s","0","", function(){
				setButtonColorBadge(0);
			});
		}
		if(StatuspushButtonSensingProcess[0] == 0){
			setgetpushButtonSensingActivation("set", function(){
				setgetStatuspushButtonSensingProcess("s","1", inputActivationStatus, function(){
					setButtonColorBadge(0);
				});
			});
		}
		break;
	}
}

// load functions ad webpage opening
function startatLoad(){
	loadNavbar(function(){
		getNamingXMLData(function(){
			refreshStatus();
		});	
	});
}
window.onload=startatLoad();

//Load the top fixed navigation bar and highlight the 
//active site roots.
//Check if the operater is already loged on the system as admin.
 function loadNavbar(callback1){
			getStatusLogin(function(){
				if (LoginStatus[0])
				{
					$(document).ready(function(){
						$("#mainNavbar").load("navbar.html", function(){
							$("#navbarSet").addClass("active");
							$("#navbarItempushButtenSensing").addClass("active");
							$("#navbarlogin").hide();
							$("#navbarSet").hide();
							
							if (LoginStatus[1])
							{
								$("#navbarSet").show();
							}
						});
					});
				}
				else
				{
					window.location.replace("login.html");
				}
				if (callback1){
					callback1();
				}
			});
		 }
 /*
  * Refresh status of pushButtonSensing information's.
  */
 function refreshStatus(){
	 	setgetStatuspushButtonSensingProcess("g","","", function(){
			setButtonColorBadge(0);
		});
		setTimeout(function(){refreshStatus()}, 5000);
	}