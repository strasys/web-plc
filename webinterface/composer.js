/**
 * Composer JavaScript code
 * 
 * Johannes Strasser
 * 11.10.2015
 * www.strasys.at
 * 
 */

function setgetServer(setget, url, cfunc, senddata){
	xhttp = new XMLHttpRequest();
	xhttp.onreadystatechange = cfunc;
	xhttp.open(setget,url,true);
	xhttp.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
	xhttp.send(senddata);
}


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

// load functions ad webpage opening
function startatLoad(){
	loadNavbar();
}
window.onload=startatLoad();

//Load the top fixed navigation bar and highlight the 
//active site roots.
//Check if the operater is already loged on the system as admin.
 function loadNavbar(){
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
				if (callback1)
				{
					callback1();
				}
			});
		 }