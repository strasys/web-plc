/**
 * user and user rights management
 * 
 * 10.06.2015
 * Johannes Strasser
 * 
 * www.strasys.at
 */

 
function setgetuser(setget, url, cfunc, senddata){
	xhttp = new XMLHttpRequest();
	xhttp.onreadystatechange = cfunc;
	xhttp.open(setget,url,true);
	xhttp.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
	xhttp.send(senddata);
}

 function setgetUserPassword(Username, Password, PasswordRepeat, Adminright, callback1){
		setgetuser("post","user.php",function()
			{
				if (xhttp.readyState==4 && xhttp.status==200)
				{
				var statusUsernamePassword = JSON.parse(xhttp.responseText); 
				
				statusSetUsername = [(statusUsernamePassword.errorFile),
									(statusUsernamePassword.errorUsername),
									(statusUsernamePassword.errorPasswordRepeat),
									(statusUsernamePassword.username)
									];
					if (callback1){
						callback1();
					}
				}
			},"username="+Username+"&password="+Password+"&passwordRepeat="+
			PasswordRepeat+"&adminright="+Adminright);		
}
 

function submitUserData(){
	var inputUsername = document.getElementById("forminputusername").value;
	var inputPassword = document.getElementById("forminputpassword").value;
	var inputPasswordRepeat = document.getElementById("forminputpasswordrepeat").value;
	var inputAdminright = document.getElementById("forminputcheckboxadmin").checked;
	 
		setgetUserPassword(inputUsername, inputPassword, inputPasswordRepeat, inputAdminright, function()
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
						"Der von Ihnen eingegebene Benutzername existiert bereits.");
					}
					else
					{
						if (statusSetUsername[2] == -1)
						{
							DisplayAlertInformation("danger",
							"Ihre eingegebenen Passwörter stimmen nicht Überein.");
						}
						else
						{
							DisplayAlertInformation("success",
							"Neuer Benutzer wurde angelegt.");
							setTimeout(function() {
								window.location.replace("user.html");
							}, 2000);
						}
					}	
				}
			
		});
 }


 
 //Alert information
 function DisplayAlertInformation(status, statusText){
	var statusClass, strongText;
	switch (status){
		case "success":
			statusClass = "alert alert-success";
			strongText = "Erfolgreich: ";
			break;
		case "warning":
			statusClass = "alert alert-warning";
			strongText = "Warnung: ";
			break;
		case "danger":
			statusClass = "alert alert-danger";
			strongText = "Fehler: ";
			break;
	}
	
		var setgetalertusername = document.getElementById("alertusername");
		setgetalertusername.getAttributeNode("class").value = statusClass;
		
		var addparagraph = document.createElement("p");
		var addstrong = document.createElement("strong");
		var addtextnode = document.createTextNode(statusText);
		var addtextstrong = document.createTextNode(strongText);
		
		addparagraph.appendChild(addtextnode);
		addstrong.appendChild(addtextstrong);
		setgetalertusername.appendChild(addstrong);
		setgetalertusername.appendChild(addparagraph);
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
		$("#navbarSet").addClass("active");
		$("#navbarItemUser").addClass("active");
	  });
	});
}