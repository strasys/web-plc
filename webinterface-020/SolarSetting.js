/**
 * Program to set the Solar heating system
 *   
 * 03.08.2016
 * Johannes Strasser
 * 
 * www.strasys.at
 */

var sortoutcache = new Date();

function getData(setget, url, cfunc, senddata){
	xhttp = new XMLHttpRequest();
	xhttp.onreadystatechange = cfunc;
	xhttp.open(setget,url,true);
	xhttp.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
	xhttp.send(senddata);
}


function getloginstatus(callback1){
		getData("post","SolarSetting.php",function()
		{
			if (xhttp.readyState==4 && xhttp.status==200)
			{
			var getLogData = JSON.parse(xhttp.responseText); 
			
			LogData = [
					(getLogData.loginstatus),
					(getLogData.adminstatus)
			                          ];
				if (callback1){
				callback1();
				}
			}
		},"getLogData=g");		
}

function getSetXMLData(callback4){
	getData("GET","VDF.xml?sortoutcache="+sortoutcache.valueOf(),function(){
		if (xhttp.readyState==4 && xhttp.status==200){
			var getXMLData = xhttp.responseXML;
			var w = getXMLData.getElementsByTagName("CleaningInterval");
			var z = w.length;
			var i=0;
			for (i=0; i<z; i++){
				j=i+1
				document.getElementById("StartTime"+j).value = w[i].getElementsByTagName("Start")[0].childNodes[0].nodeValue;
				document.getElementById("StopTime"+j).value = w[i].getElementsByTagName("Stop")[0].childNodes[0].nodeValue;
				document.getElementById("CleanTimePeriode"+j).innerHTML = w[i].getElementsByTagName("Periode")[0].childNodes[0].nodeValue;				
			}
			if (callback4){
				callback4();
			}
		}
		});
	}	

// Write cleaning interval time to XML - file.
function setCleaningIntervalTimeXML(interval,start,stop,ButtonCleanTime){
	
	var CleanInterval = interval;
	var StartTime = document.getElementById(start).value;	
	var StopTime = document.getElementById(stop).value;
		calcTimePeriode(start,stop,function(){
		getData("post","CleaningInterval.php",function()
		{
			if (xhttp.readyState==4 && xhttp.status==200)
			{
				document.getElementById(ButtonCleanTime).setAttribute("class","btn btn-success");
				setTimeout(function(){document.getElementById(ButtonCleanTime).setAttribute("class","btn btn-default")},500);	
			}
		},
		"CleanInterval="+CleanInterval+
		"&StartTime="+StartTime+
		"&StopTime="+StopTime+
		"&CleanIntervalPeriode="+TimeDifference+
		"&setCleanTime=s");
		});
}

function setSelectFieldsTemp(idName,StartTemp,StopTemp,interval){
	var x = 0;	
	for(x=StartTemp;x<=StopTemp;x=x+interval){
		var y = document.getElementById(idName);
		var option1 = document.createElement("option");
		option1.text = x;
		y.options.add(option1);
	}
}

function setSelectMenuesValues(callback5){
	setSelectFieldsTemp("SolarBackWaterTemp",18,36,1);
	setSelectFieldsTemp("SolarDifferenceTemp",1,12,1);
	setSelectFieldsTemp("SolarPoolTemp",18,36,1);		
	
	if (callback5){
		callback5();
	}
}

// load functions ad webpage opening
function startatLoad(){
	loadNavbar(function(){
		setSelectMenuesValues(function(){
				getSetXMLData(function(){
					getOperationMode();
				});
			});
		});
}
window.onload=startatLoad();

//Load the top fixed navigation bar and highlight the 
//active site roots.
//Check of the operater is already loged on the system.
function loadNavbar(callback1){
	getloginstatus(function(){
		if (LogData[0])
		{
			$(document).ready(function(){
				$("#mainNavbar").load("navbar.html", function(){
					$("#navbarFunction").addClass("active");
					$("#navbarItemSolarSetting").addClass("active");
					$("#navbarlogin").hide();
					$("#navbarSet").hide();
					$("#inputhh").prop("disabled", true);
				
					
					if (LogData[1])
					{
						$("#navbarSet").show();
						$("#showSetTime").show();
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

