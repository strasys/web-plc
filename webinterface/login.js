/**
 * login handling client
 * Johannes Strasser
 * www.strasys.at
 * 08.06.2015
 * 
 */

 
function setgetuser(setget, url, cfunc, senddata){
	xhttp = new XMLHttpRequest();
	xhttp.onreadystatechange = cfunc;
	xhttp.open(setget,url,true);
	xhttp.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
	xhttp.send(senddata);
}

 function setgetUserPassword(Username, Password, PasswordRepeat,callback1){
		setgetuser("post","login.php",function()
			{
				if (xhttp.readyState==4 && xhttp.status==200)
				{
				var statusUsernamePassword = JSON.parse(xhttp.responseText); 
				
				statusSetUsername = [(statusUsernamePassword.errorFile),
									(statusUsernamePassword.errorUsername),
									(statusUsernamePassword.errorPassword),
									(statusUsernamePassword.username)
									];
					if (callback1){
						callback1();
					}
				}
			},"username="+Username+"&password="+Password);		
}
 

function submitUserData(){
	var inputUsername = document.getElementById("inputUsername").value;
	var inputPassword = document.getElementById("inputPassword").value;
	 
		setgetUserPassword(inputUsername, inputPassword, function()
		{
			 if (statusSetUsername[0] == -1)
				{
					DisplayAlertInformation("danger", 
						"Benutzerverwaltung File !!"); 
				}
				else
				{
					if (statusSetUsername[1] == -1)
					{
						DisplayAlertInformation("warning",
						"Der von Ihnen eingegebene Benutzername bzw. das Passwort sind falsch.");
					
					else
					{
						if (statusSetUsername[2] == -1)
						{
							DisplayAlertInformation("danger",
							"Der von Ihnen eingegebenen Benutzername bzw. das Passwort sind falsch.");
						}
						else
						{
							DisplayAlertInformation("success",
							"Sie haben sich erfolgreich in das System eingelogt.");
						}
					}	
				}
			
		});
 }

//load functions at webpage opening
function startatLoad(){
	loadNavbar();
}
window.onload=startatLoad();

//Load the top fixed navigation bar and highlight the 
//active site roots.
function loadNavbar(){
$(document).ready(function(){
	$("#mainNavbar").load("navbar.html", function(){
		$("#navbarloginout").addClass("active");
	//	$("#navbar").addClass("active");
	  });
	});
}
