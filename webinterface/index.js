/**
 * Program for start side.
 * 
 * Johannes Strasser
 * 15.01.2015
 * www.strasys.at
 * 
 */

function setgetHomeLogin(setget, url, cfunc, senddata){
	xhttp = new XMLHttpRequest();
	xhttp.onreadystatechange = cfunc;
	xhttp.open(setget,url,true);
	xhttp.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
	xhttp.send(senddata);
}


function getStatusLogin(callback1){
		setgetHomeLogin("post","index.php",function()
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
		},"getLoginStatus=g");		
}

// load functions ad webpage opening
function startatLoad(){
	loadNavbar();
}
window.onload=startatLoad();

//Load the top fixed navigation bar and highlight the 
//active site roots.
//Check of the operater is already loged on the system.
function loadNavbar(){
	getStatusLogin(function(){
		if(LoginStatus[0]){
			
			$(document).ready(function(){
				$("#mainNavbar").load("navbar.html", function(){
					$("#navbarHome").addClass("active");
					$("#navbarlogin").hide();
					
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
				$("#mainNavbar").load("navbar.html", function(){
					$("#navbarHome").addClass("active");
					$("#navbarlogout").hide();
					$("#navbarFunction").hide();
					$("#navbarSet").hide();
					$("#navbarHelp").hide();
				});
			});

		}
	});
}

