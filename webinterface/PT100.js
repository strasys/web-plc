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
//		if (!document.all && !document.getElementById)
//		return
		getPT100Data("post","PT100handler.php",function()
		{
			if (xhttp.readyState==4 && xhttp.status==200)
			{
			var getPT100 = JSON.parse(xhttp.responseText); 
			
			OUT = [parseInt(getPT100.channel1),
		           parseInt(getPT100.channel2),
		           ];
			if (callback1){
				callback1();
			}
			}
		},"setgetGPIO=g");		
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
		$("#navbarItemPT100").addClass("active");
	
	  });
	});
}