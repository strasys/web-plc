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

 function setgetUserPassword(Username, Password, PasswordRepeat, callback1){
		setgetuser("post","user.php",function()
			{
				if (xhttp.readyState==4 && xhttp.status==200)
				{
				var statusUsernamePassword = JSON.parse(xhttp.responseText); 
				
				statusSetUsername = [(statusUsernamePassword.errorFile),
									(statusUsernamePassword.errorUsername),
									(statusUsernamePassword.errorPasswordRepeat),
									(statusUsernamePassword.username)
									]
					if (callback1){
						callback1();
					}
				}
			},"username="+Username+"&password="+Password+"&passwordRepeat="+
			PasswordRepeat);		
}
 

 $("#formuser").submit(function(){
		var inputUsername = $("#forminputusername").text();
		var inputPassword = $("#forminputpassword").text();
		var inputPasswordRepeat = $("#forminputpasswordrepeat").text();
		
		setgetUserPassword(inputUsername, inputPassword, inputPasswordRepeat, function(){
			if (statusSetUsername[0] == -1)
			{
				DisplayAlertInformation("danger", 
					"<strong>Schwerer Fehler:</strong> Benutzerverwaltung File !!"); 
			}
			else
			{
				if (statusSetUsername[1] == -1)
				{
					DisplayAlertInformation("warning",
					"<strong>Warnung:</strong> Der von Ihnen eingegebene Benutzername existiert bereits.");
				}
				else
				{
					if (statusSetUsername[2] == -1)
					{
						DisplayAlertInformation("danger",
						"<strong>Fehler:</strong> Ihre eingegebenen Passwörter stimmen nicht überein.");
					}
					else
					{
						DisplayAlertInformation("success",
						"<strong>Erfolgreich:</strong> Benutzer wurde angelegt.");
					}
				}
			}
			
		});
		
 });
 
 //Alert information
 function DisplayAlertInformation(status, statusText){
	var statusClass;
	switch (status){
		case "success":
			statusClass = "alert alert-success";
			break;
		case "warning":
			statusClass = "alert alert-warning";
			break;
		case "danger":
			statusClass = "alert alert-danger";
			break;
	}
	
	$("#alertusername").addClass(statusClass, function() {
		$(this).text(statusText);
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
		$("#navbarSet").addClass("active");
		$("#navbarItemUser").addClass("active");
	  });
	});
}