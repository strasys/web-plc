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
			                          (getPT100.temperature2)
			                          ];
				if (callback1){
				callback1();
				}
			}
		},"setgetPT100handler=g");		
}

function showPT100values(){
	getPT100values(function(){
		$("#badgePT1001").text(PT100temperaturevalues[0]+" °C");
		$("#badgePT1002").text(PT100temperaturevalues[1]+" °C");
	});
	setTimeout(function(){showPT100values()}, 10000);
}

// load functions ad webpage opening
function startatLoad(){
	loadNavbar();
	showPT100values();
}
window.onload=startatLoad();

//Load the top fixed navigation bar and highlight the 
//active site roots.
function loadNavbar(){
$(document).ready(function(){
	$("#mainNavbar").load("navbar.html", function(){
		$("#navbarFunction").addClass("active");
		$("#navbarItemPT100").addClass("active");
	
	  });
	});
}