/**
 * Program to set and get the status of
 * the Outputs
 * 
 * Johannes Strasser
 * www.strasys.at
 * 24.01.2015
 */

var OUT;
// send request to server and
// receive status of digital outputs
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

// Function is called by click of a GPIO button
// based on status 1 or 0 the value will be send to the server
// after that function getOutstatus() is called to check the result.
function setOutstatus(numOut){
	if (!document.all && !document.getElementById)
	return
	if(OUT[parseInt(numOut)] == 1){
		valOut = 0;
	}
	if(OUT[parseInt(numOut)] == 0) {
		valOut = 1;
	}
	var gOUTstat = new XMLHttpRequest();
	gOUTstat.open("post","setGPIO.php", true);
	gOUTstat.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
    gOUTstat.send("setgetGPIO=s&GPIOnum="+numOut+"&GPIOvalue="+valOut);
	gOUTstat.onreadystatechange = function(){
    	
    	if(gOUTstat.readyState == 4 && gOUTstat.status == 200)
    	{	
    		getOutstatus();
    	}	
    }
	}

// This function sets the color and status (ein / aus) 
// of the button.
function setButtonOut(){
	for (i=0; i<8; i++){
		var status = OUT[i];
		if(status == 1){
			span = document.getElementById("badgeOut"+(i));
			span.textContent = "EIN";
			button = document.getElementById("buttonOut"+(i));
			button.getAttributeNode("class").value = "btn btn-success";
		}
		if(status == 0) {
			span = document.getElementById("badgeOut"+(i));
			span.textContent = "AUS";
			button = document.getElementById("buttonOut"+(i));
			button.getAttributeNode("class").value = "btn btn-danger";
		}
	}
}

// This function will be called once at start and after
// set of the button naming.
// The names of the button are stored in a XML file on the server.
function getGPIOoutXMLData(){
	xhttp = new XMLHttpRequest();
	xhttp.open("GET","GPIOout.xml",false);
	xhttp.send();
	getGPIOoutXML =  xhttp.responseXML;
	var x = getGPIOoutXML.getElementsByTagName("ButtonName");
	var y = getGPIOoutXML.getElementsByTagName("ButtonName");
	var i=0;
	for (i=0; i<y.length; i++){
		document.getElementById("buttonOutText"+i).innerHTML=x[i].childNodes[0].nodeValue;	
	}
}

// This function is called after pressing the "Button Beschriftung ändern" button.
// The function loads the actual button naming form the XML - file on the server
// into the input fields.
function getGPIOoutXMLDataInput(){
	xhttp = new XMLHttpRequest();
	xhttp.open("GET","GPIOout.xml",false);
	xhttp.send();
	getGPIOoutXML = xhttp.responseXML;
	var x = getGPIOoutXML.getElementsByTagName("ButtonName");
	var y = getGPIOoutXML.getElementsByTagName("ButtonName");
	var i=0;
	for (i=0; i<y.length; i++){
		document.getElementById("setButtonNameInputOut"+i).value=x[i].childNodes[0].nodeValue;	
	}
}

// After pressing the button "Änderungen speichern" in the button name change menue.
// This function transfers the data to the server where it will be saved with the 
// help of a php function.
function setGPIOoutXMLDataInput(){
	if (!document.all && !document.getElementById)
		return
	var ButtonNameSave = new XMLHttpRequest();
	ButtonNameSave.open("post","setGPIO.php", true);
	ButtonNameSave.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
		
	var ButtonText = [document.getElementById("setButtonNameInputOut0").value,
	                  document.getElementById("setButtonNameInputOut1").value,
	                  document.getElementById("setButtonNameInputOut2").value,
	                  document.getElementById("setButtonNameInputOut3").value,
	                  document.getElementById("setButtonNameInputOut4").value,
	                  document.getElementById("setButtonNameInputOut5").value,
	                  document.getElementById("setButtonNameInputOut6").value,
	                  document.getElementById("setButtonNameInputOut7").value
	                  ];
	                  
	

	ButtonNameSave.onreadystatechange = function(){
			
    	if(ButtonNameSave.readyState == 4 && ButtonNameSave.status == 200)
    	{	
    		getGPIOoutXMLData();
  
    	}
    }
	
	
	ButtonNameSave.send("ButtonText0="+ButtonText[0]+
			"&ButtonText1="+ButtonText[1]+
			"&ButtonText2="+ButtonText[2]+
			"&ButtonText3="+ButtonText[3]+
			"&ButtonText4="+ButtonText[4]+
			"&ButtonText5="+ButtonText[5]+
			"&ButtonText6="+ButtonText[6]+
			"&ButtonText7="+ButtonText[7]+
			"&ButtonFlag=1");
	
}

//Show input fields to change Button Names
function SetButtonName(){
	 $(document).ready(function(){
		$("#setButtonNameDiv").load("setButtonName.html?ver=2", function(){
			getGPIOoutXMLDataInput();
			$("#setButtonNameDiv").show();
			$("#showSetButtonName").hide();
			
		});
	 });
}

function SaveSetButtonName(){
		  setGPIOoutXMLDataInput();
}

function CancelSetButtonName(){
		  getGPIOoutXMLDataInput();
}

function CollapseSetButtonName(){
		  $("#setButtonNameDiv").hide();
		  $("#showSetButtonName").show();
		  reload();
}

// JQUERY functions.

//Load the top fixed navigation bar and highlight the 
//active site roots.
function loadNavbar(){
	 $(document).ready(function(){
	 	$("#mainNavbar").load("navbar.html?ver=0", function(){
	 		$("#navbarFunction").addClass("active");
	 		$("#navbarItemDigiOut").addClass("active");
	 	  });
	 	});
	 }

function reload(){
	location.reload();
}

//load functions ad webpage opening
window.onload=function(){
	loadNavbar();
	getGPIOoutXMLData();
	getOutstatus();
};

