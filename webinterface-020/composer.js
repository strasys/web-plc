/**
 * Composer JavaScript code
 * 
 * Johannes Strasser
 * 11.10.2015
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
		setgetServer("post","composerhandler.php",function()
		{
			if (xhttp.readyState==4 && xhttp.status==200)
			{
			var getComposerLogin = JSON.parse(xhttp.responseText); 
			
			LoginStatus = [(getComposerLogin.loginstatus),
			               (getComposerLogin.adminstatus)
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
function setgetStatusComposerProcess(setget,setrunstopStatus, callback2){
		setgetServer("post","composerhandler.php",function()
			{
				if (xhttp.readyState==4 && xhttp.status==200)
				{
				var setgetComposerProcessStatus = JSON.parse(xhttp.responseText); 
				
				StatusComposerProcess = [(setgetComposerProcessStatus.runstop)
				                         ];
					if (callback2){
					callback2();
					}
				}
			},"setgetComposerProcessStatus="+setget+"&setrunstopStatus="+setrunstopStatus);		
}

/*
 * This function sets the color and the badge description of the ComposerProcessStatus button.
 */
function setButtonColorBadge(ButtonNumber){
	 switch (ButtonNumber){
	 case 0:
			if(StatusComposerProcess[0] == 1){
				span = document.getElementById("badgebuttonComposerScriptOnOff");
				span.textContent = "RUN";
				button = document.getElementById("buttonComposerOnOff");
				button.getAttributeNode("class").value = "btn btn-success";
			}
			if(StatusComposerProcess[0] == 0) {
				span = document.getElementById("badgebuttonComposerScriptOnOff");
				span.textContent = "STOP";
				button = document.getElementById("buttonComposerOnOff");
				button.getAttributeNode("class").value = "btn btn-danger";
			}
			break;
	 }
	 
}

function ButtonComposerAction(ButtonNumber){
	switch (ButtonNumber){
	case 0:
		if(StatusComposerProcess[0] == 1){
			setgetStatusComposerProcess("s","0", function(){
				setButtonColorBadge(0);
			})
		}
		if(StatusComposerProcess[0] == 0){
			setgetStatusComposerProcess("s","1", function(){
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
							$("#navbarItemComposer").addClass("active");
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
	 	setgetStatusComposerProcess("g","", function(){
			setButtonColorBadge(0);
		});
		setTimeout(function(){refreshStatus()}, 2000);
	}