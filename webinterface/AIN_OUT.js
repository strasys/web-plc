/**
 * Program to update the AIn and AOut values.
 * 
 * 06.05.2015
 * Johannes Strasser
 * 
 * www.strasys.at
 */

function setgetAnalogue(setget, url, cfunc, senddata){
	xhttp = new XMLHttpRequest();
	xhttp.onreadystatechange = cfunc;
	xhttp.open(setget,url,true);
	xhttp.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
	xhttp.send(senddata);
}

function getAIn(){
		setgetAnalogue("post","AINOUThandler.php",function()
			{
				if (xhttp.readyState==4 && xhttp.status==200)
				{
				var getAIn = JSON.parse(xhttp.responseText); 
				
				AnalogueIN = [	(getAIN.INvalue1),
				              	(getAIN.INvalue2)
				               ];
					if (callback1){
						callback1();
					}
				}
			},"setgetAnalogue=g&InOut=I");		
}

function showAInvalues(){
	getAIn(function(){
		$("#badgeAIN1").text(AnalogueIN[0]);
		$("#badgeAIN2").text(AnalogueIN[1]);
	});
	setTimeout(function(){showPT100values()}, 1000);
}

// load functions ad webpage opening
function startatLoad(){
	loadNavbar();
	
}
window.onload=startatLoad();

//Load the top fixed navigation bar and highlight the 
//active site roots.
function loadNavbar(){
$(document).ready(function(){
	$("#mainNavbar").load("navbar.html", function(){
		$("#navbarFunction").addClass("active");
		$("#navbarItemAIO").addClass("active");
	
	  });
	});
}