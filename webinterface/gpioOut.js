/**
 * Program to set and get the status of
 * the Outputs
 * 
 * Johannes Strasser
 * www.strasys.at
 * 30.11.2014
 */

function getOutstatus(){
		if (!document.all && !document.getElementById)
		return
		
		var gOUTstat = new XMLHttpRequest();
		gOUTstat.open("post","setGPIO.php", true);
		gOUTstat.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
	    gOUTstat.send("setgetGPIO=g");
		gOUTstat.onreadystatechange = function(){
	    	
	    	if(gOUTstat.readyState == 4 && gOUTstat.status == 200)
	    	{
	    		var getOUT = JSON.parse(gOUTstat.responseText); 
	    		var OUT1 = parseInt(getOUT.OUT1);
	    		var OUT2 = parseInt(getOUT.OUT2);
	    		var OUT3 = parseInt(getOUT.OUT3);
	    		var OUT4 = parseInt(getOUT.OUT4);
	    		var OUT5 = parseInt(getOUT.OUT5);
	    		var OUT6 = parseInt(getOUT.OUT6);
	    		var OUT7 = parseInt(getOUT.OUT7);
	    		var OUT8 = parseInt(getOUT.OUT8);
	    		document.getElementById("test").innerHTML = OUT1 + " " + OUT2 + " " + OUT3 + " " + OUT4 + " " + OUT5 + " " + OUT6 + " " + OUT7 + " " + OUT8;
	    		
	    	}	
	    }
		}

function startatLoad(){
	getOutstatus();
	
}
window.onload=startatLoad;

$(document).ready(function(){
	  $("#buttonOut1").click(function(){
		  
	    $("#badgeOut1").text("Test");
	  });
	});