/**
 * Program to update the PT100 values and
 * to set the wire length offset.
 * 
 * 15.01.2015
 * Johannes Strasser
 * 
 * www.strasys.at
 */

// send request to server and
// receive status of digital outputs
function getPT100status(){
		if (!document.all && !document.getElementById)
		return
		var gPT100stat = new XMLHttpRequest();
		gPT100stat.open("post","PT100handler.php", true);
		gPT100stat.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
	    gPT100stat.send("setgetGPIO=g");
		gPT100stat.onreadystatechange = function(){
	    	
	    	if(gOUTstat.readyState == 4 && gOUTstat.status == 200)
	    	{
	    		var getOUT = JSON.parse(gOUTstat.responseText); 
	    		OUT = [parseInt(getOUT.OUT1),
	    		           parseInt(getOUT.OUT2),
	    		           parseInt(getOUT.OUT3),
	    		           parseInt(getOUT.OUT4),
	    		           parseInt(getOUT.OUT5),
	    		           parseInt(getOUT.OUT6),
	    		           parseInt(getOUT.OUT7),
	    		           parseInt(getOUT.OUT8)];
	   
	    		setButtonOut();	    		
	    	}	
	    }
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