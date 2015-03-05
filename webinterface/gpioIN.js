sortoutcache = new Date();

// This function will be called once at start and after
// set of the button naming.
// The names of the button are stored in a XML file on the server.
function getGPIOinXMLData(callback2){
	getGPIOinXMLDa("GET","GPIOin.xml?sortoutcache="+sortoutcache.valueOf(),function()
			{
				if (xhttp.readyState==4 && xhttp.status==200)
					{
					var getGPIOinXML = xhttp.responseXML;
					var w = getGPIOinXML.getElementsByTagName("ButtonName");
					var z = getGPIOinXML.getElementsByTagName("ButtonName");
					var i = 0;
					for (i=0; i<w.length; i++){
						document.getElementById("InputInText"+i).innerHTML=z[i].childNodes[0].nodeValue;	
						}
					if (callback2){
						callback2();
					}
					
					}
			});		
}

// This function is called after pressing the "Button Beschriftung ändern" button.
// The function loads the actual button naming form the XML - file on the server
// into the input fields.

function getGPIOinXMLDataInput(){
	getGPIOoutXMLDa("GET", "GPIOin.xml?sortoutcache="+sortoutcache.valueOf(),function()
	{
		if (xhttp.readyState==4 && xhttp.status==200)
			{
				var getGPIOoutXML = xhttp.responseXML;
				var x = getGPIOinXML.getElementsByTagName("InputName");
				var y = getGPIOinXML.getElementsByTagName("InputName");
		
				for (i=0; i<y.length; i++){
				document.getElementById("setInputNameInputIn"+i).value=x[i].childNodes[0].nodeValue;	
				}
			}
	});
	
}


// After pressing the button "Änderungen speichern" in the button name change menue.
// This function transfers the data to the server where it will be saved with the 
// help of a php function.
function setGPIOinXMLDataInput(callback3){
	
		var ButtonText = [document.getElementById("setInputNameInputIn0").value,
		                  document.getElementById("setInputNameInputIn1").value,
		                  document.getElementById("setInputNameInputIn2").value,
		                  document.getElementById("setInputNameInputIn3").value
		                  ];
			
		getGPIOinXMLDa("post","setGPIO.php",function()
		{
			if (xhttp.readyState==4 && xhttp.status==200)
			{
				callback3();
			}
		},
		"InputText0="+InputText[0]+
		"&InputText1="+InputText[1]+
		"&InputText2="+InputText[2]+
		"&InputText3="+InputText[3]+
		"&InputFlag=1");
	
//	ButtonNameSave.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
}

//Show input fields to change Button Names
function SetButtonName(){
	 $(document).ready(function(){
		$("#setInputNameDiv").load("setInputName.html?ver=0", function(){
			//getGPIOoutXMLDataInput();
			$("#setInputNameDiv").show();
			$("#showSetInputName").hide();	
		});
	 });
}

function SaveSetButtonName(){
		  setGPIOoutXMLDataInput(function(){
				getGPIOoutXMLData();
		  });
}

function CancelSetButtonName(){
		  getGPIOoutXMLDataInput();
}

function CollapseSetButtonName(){
		  $("#setButtonNameDiv").hide();
		  $("#showSetButtonName").show();
		 
}


//load functions ad webpage opening
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
		$("#navbarItemDigiIn").addClass("active");
	
	  });
	});
}