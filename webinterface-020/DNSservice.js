/**
 *DNSservice JavaScript code
 * 
 * Johannes Strasser
 * 05.02.2016
 * www.strasys.at
 * 
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
		setgetServer("post","DNSservicehandler.php",function()
		{
			if (xhttp.readyState==4 && xhttp.status==200)
			{
			var getDNSserviceLogin = JSON.parse(xhttp.responseText); 
			
			LoginStatus = [(getDNSserviceLogin.loginstatus),
			               (getDNSserviceLogin.adminstatus)
			               ];
				if (callback1){
				callback1();
				}
			}
		},"getLoginStatus=g");		
}
/*
 * This function set's and get's the status of the composer process.
 * If the composer script is running StatusComposerProcess = 1 else 0.
 */
function setgetStatusDNSservice(setget,setrunstopStatus, callback2){
		setgetServer("post","DNSservicehandler.php",function()
			{
				if (xhttp.readyState==4 && xhttp.status==200)
				{
				var setgetDNSserviceStatus = JSON.parse(xhttp.responseText); 
				
				StatusDNSservice = [(setgetDNSserviceStatus.runstop)
				                         ];
					if (callback2){
					callback2();
					}
				}
			},"setgetDNSserviceStatus="+setget+"&setrunstopStatus="+setrunstopStatus);		
}

/*
 * This function sets the color and the badge description of the ComposerProcessStatus button.
 */
function setButtonColorBadge(ButtonNumber){
	 switch (ButtonNumber){
	 case 0:
			if(StatusDNSservice[0] == 1){
				span = document.getElementById("badgebuttonDNSserviceOnOff");
				span.textContent = "RUN";
				button = document.getElementById("buttonDNSserviceOnOff");
				button.getAttributeNode("class").value = "btn btn-success";
			}
			if(StatusDNSservice[0] == 0) {
				span = document.getElementById("badgebuttonDNSserviceOnOff");
				span.textContent = "STOP";
				button = document.getElementById("buttonDNSserviceOnOff");
				button.getAttributeNode("class").value = "btn btn-danger";
			}
			break;
	 }
	 
}

function ButtonDNSserviceAction(ButtonNumber){
	switch (ButtonNumber){
	case 0:
		if(StatusDNSservice[0] == 1){
			setgetStatusDNSservice("s","0", function(){
				setButtonColorBadge(0);
			})
		}
		if(StatusDNSservice[0] == 0){
			setgetStatusDNSservice("s","1", function(){
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
							$("#navbarItemDNSservice").addClass("active");
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
  * Refresh status of composer information's.
  */
 function refreshStatus(){
	 	setgetStatusDNSservice("g","", function(){
			setButtonColorBadge(0);
		});
		setTimeout(function(){refreshStatus()}, 2000);
	}