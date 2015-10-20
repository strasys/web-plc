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
function setgetStatuspushButtonSensingProcess(setget,setrunstopStatus, callback2){
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
			},"setgetpushButtonSensingProcessStatus="+setget+"&setrunstopStatus="+setrunstopStatus);		
}



/*
 * This function sets the color and the badge description of the pushButtonSensing button.
 */
function setButtonColorBadge(ButtonNumber){
	 switch (ButtonNumber){
	 case 0:
			if(StatuspushButtonSensingProcess[0] == 1){
				span = document.getElementById("badgebuttonpushButtonSesningScriptOnOff");
				span.textContent = "RUN";
				button = document.getElementById("buttonpushButtonSesningOnOff");
				button.getAttributeNode("class").value = "btn btn-success";
			}
			if(StatuspushButtonSensingProcess[0] == 0) {
				span = document.getElementById("badgebuttonpushButtonSesningScriptOnOff");
				span.textContent = "STOP";
				button = document.getElementById("buttonpushButtonSesningOnOff");
				button.getAttributeNode("class").value = "btn btn-danger";
			}
			break;
	 }
	 
}

function ButtonpushButtonSensingAction(ButtonNumber){
	switch (ButtonNumber){
	case 0:
		if(StatuspushButtonSensingProcess[0] == 1){
			setgetStatuspushButtonSensingProcess("s","0", function(){
				setButtonColorBadge(0);
			})
		}
		if(StatuspushButtonSensingProcess[0] == 0){
			setgetStatuspushButtonSensingProcess("s","1", function(){
				setButtonColorBadge(0);
			})
		}
		break;
	}
}

// load functions ad webpage opening
function startatLoad(){
	loadNavbar(function(){
			refreshStatus();
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
	 	setgetStatuspushButtonSensingProcess("g","", function(){
			setButtonColorBadge(0);
		});
		setTimeout(function(){refreshStatus()}, 5000);
	}