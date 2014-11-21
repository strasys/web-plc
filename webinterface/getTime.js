/**
 * Program to get and set the time of
 * the strahome controller
 */

var offsetTime;
	
	function getSystemTime(){
		if (!document.all && !document.getElementById)
		return
	    timeElement=document.getElementById("curTime");
		var SystemTime = new Date();
		var clientTime = new Date();
		var sST = new XMLHttpRequest();
		sST.open("post","setgetTime.php", true);
		sST.send(null);
		sST.onreadystatechange = function(){
	    	
	    	if(sST.readyState == 4 && sST.status == 200)
	    	{
	    		var getTime = JSON.parse(sST.responseText); 
	    		var hh = parseInt(getTime.hh);
	    		var mm = parseInt(getTime.mm);
	    		var ss = parseInt(getTime.ss);
	    		SystemTime.setHours(hh);
	    		SystemTime.setMinutes(mm);
	    		SystemTime.setSeconds(ss);
	    		var system = SystemTime.getTime();
	    		var client = clientTime.getTime();
	    		offsetTime = client - system;
	    		DisplayTime();
	    	}	
	    }
		
		}
	
	function DisplayTime(){
		if (!document.all && !document.getElementById)
		return
		timeElement=document.getElementById("curTime");
		var clientTime = new Date();
		clientTime.setTime(clientTime.getTime() - offsetTime);
		var hours = clientTime.getHours();
		var minutes = clientTime.getMinutes();
		var seconds = clientTime.getSeconds();
		if (hours<=9) hours="0"+hours;
		if (minutes<=9) minutes="0"+minutes;
		if (seconds<=9) seconds="0"+seconds;
		var currentTime=hours+":"+minutes+":"+seconds;
		timeElement.innerHTML=currentTime;
		t = setTimeout(function(){DisplayTime()}, 1000);
		}
	
		function DisplayDate(){
		if (!document.all && !document.getElementById)
		return
		dateElement=document.getElementById("curDate");
		var CurrentDatum=new Date();
		var day=CurrentDatum.getDate();
		var month=CurrentDatum.getMonth() + 1;
		var year=CurrentDatum.getFullYear();
		if (day<=9) day="0"+day;
		if (month<=9) month="0"+month;
		var currentDate=day+"."+month+"."+year;
		dateElement.innerHTML=currentDate;
		}


    function startatLoad(){
				DisplayDate();
				getSystemTime();
				//DisplayTime();
		}
		window.onload=startatLoad;
		
		var sST;
		   
	    function setSystemTime()
	    { 
	    var hh = document.forms["formTime"]["hhinput"].value;
	    var mm = document.forms["formTime"]["mminput"].value;
	    var ss = document.forms["formTime"]["ssinput"].value;
	
	   	sST = new XMLHttpRequest();
	    sST.open("post","setgetTime.php", true);
	    sST.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
	    sST.send("hh="+hh+"&mm="+mm+"&ss="+ss);
	    sST.onreadystatechange = auswerten; 
	    } 
	    
	    function auswerten()
	    {
	      if(sST.readyState == 4 && sST.status == 200)
	        {
	        document.forms["formTime"].reset();
	        getSystemTime();
	        }
	    }

	
		

