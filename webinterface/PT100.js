/**
 * Program to update the PT100 values and
 * to set the wire length offset.
 * 
 * 15.01.2015
 * Johannes Strasser
 * 
 * www.strasys.at
 */

function getPT100Data(setget, url, cfunc, senddata){
	xhttp = new XMLHttpRequest();
	xhttp.onreadystatechange = cfunc;
	xhttp.open(setget,url,true);
	xhttp.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
	xhttp.send(senddata);
}


function getPT100values(callback1){
		getPT100Data("post","PT100handler.php",function()
		{
			if (xhttp.readyState==4 && xhttp.status==200)
			{
			var getPT100 = JSON.parse(xhttp.responseText); 
			
			PT100temperaturevalues = [(getPT100.temperature1),
			                          (getPT100.temperature2),
									  (getPT100.temperature11),
									  (getPT100.temperature12),
									  (getPT100.temperature13),
									  (getPT100.temperature14),
			                          (getPT100.loginstatus),
			                          (getPT100.adminstatus)
			                          ];
				if (callback1){
				callback1();
				}
			}
		},"setgetPT100handler=g");		
}


function showPT100values(){
	getPT100values(function(){
		if (PT100temperaturevalues[2])
			{
			$("#badgePT1001").text(PT100temperaturevalues[0]+" °C");
			$("#badgePT1002").text(PT100temperaturevalues[1]+" °C");
		//	$"#badgePT10001).text(PT100temperaturevalues[2]+" °C");
			for(i=0;i<5;i++){
				$("#badgePT1000"+(i+1)).text(PT100temperaturevalues[i+2]+" °C");
			}
			}
		else
			{
			window.location.replace("login.html");
			}
	});
	setTimeout(function(){showPT100values()}, 10000);
}

// load functions ad webpage opening
function startatLoad(){
		loadNavbar(function(){
			showPT100values();
		});
}
window.onload=startatLoad();

//Load the top fixed navigation bar and highlight the 
//active site roots.
//Check of the operater is already loged on the system.
function loadNavbar(callback1){
	getPT100values(function(){
		if (PT100temperaturevalues[2])
		{
			$(document).ready(function(){
				$("#mainNavbar").load("navbar.html", function(){
					$("#navbarFunction").addClass("active");
					$("#navbarItemPT100").addClass("active");
					$("#navbarlogin").hide();
					$("#navbarSet").hide();
					
					if (PT100temperaturevalues[3])
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

