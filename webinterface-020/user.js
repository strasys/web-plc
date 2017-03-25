/**
 * user and user rights management
 * 
 * 23.03.2017
 * Johannes Strasser
 * 
 * www.strasys.at
 */

var selecteduser;

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
									(statusUsernamePassword.username),
									(statusUsernamePassword.loginstatus),
									(statusUsernamePassword.adminstatus)
									];
					if (callback1){
						callback1();
					}
				}
			},"username="+Username+"&password="+Password+"&passwordRepeat="+
			PasswordRepeat+"&adminright="+Adminright);		
}

function getloginstatus(callback1){
	setgetuser("post","user.php",function()
			{
				if (xhttp.readyState==4 && xhttp.status==200)
					{
						var statusLogIn = JSON.parse(xhttp.responseText);
						
						LogInStatusCheck = [(statusLogIn.loginstatus),
						                    (statusLogIn.adminstatus)
						                    ];
						if (callback1){
							callback1();
						}
					}
			},"loginstatus=get");
}

function submitUserData(){

}


 
 //Alert information
function DisplayAlertInformation(status, statusText){

}

function getuserList(callback1){
	setgetuser("post","user.php",function()
		{
		if (xhttp.readyState==4 && xhttp.status==200)
			{
			userList = JSON.parse(xhttp.responseText);
				
				if (callback1){
					callback1();
				}
			}
	},"setget=get");
}

//Alert information
function DisplayAlertInformation(msg, status, callback3){
	switch (status){
		case 0:
			$("#alert_icon").removeClass();
			$("#alert_icon").addClass("login-icon glyphicon glyphicon-chevron-right");
			$("#alert_text-msg").html(msg);
			$("#alert_msg").removeClass();
			$("#alert_msg").addClass("login-msg");
			break
		case -1:
			$("#alert_icon").removeClass();
			$("#alert_icon").addClass("login-icon glyphicon glyphicon-remove error");
			$("#alert_text-msg").html(msg);
			$("#alert_msg").removeClass();
			$("#alert_msg").addClass("login-msg error");
			break;
		case 1:
			$("#alert_icon").removeClass();
			$("#alert_icon").addClass("login-icon glyphicon glyphicon-ok success");
			$("#alert_text-msg").html(msg);
			$("#alert_msg").removeClass();
			$("#alert_msg").addClass("login-msg success");
			break;
	}

	if (callback3){
		callback3();
	}
	
}


//display user list
 function writeuserList(){
	 getuserList(function(){
		 var test = userList[0];
	//	$("#userlist_head").focus();
		$("<th>Auswahl</th><th>Bentutzer Name</th><th>Rechte</th>").appendTo("#userlist_head");
		var n=0;
		for (i=1;i<((userList[0])-1);i=i+2){
			n++
			$("<tr><td><label><input type=\"radio\" name=\"user\" value=\""+n+"\"></label></td><td>"+userList[i]+"</td><td>"+userList[i+1]+"</td></tr>").appendTo("#userlist_body");
			}	
	});
 }

//load functions at webpage opening
 function startatLoad(){
	 $("#alert_user").hide();
	 $("#adduser").hide();
	 $("#userlist").hide();
	 $("#changeuserlist").hide();
	 $("#inputchangeuser_help").hide();
	 $("#ButtonChangeSelectedUser").prop('disabled', true);
	loadNavbar(function(){
		writeuserList();
	});
}
window.onload=startatLoad();

//Load the top fixed navigation bar and highlight the 
//active site roots.
function loadNavbar(callback){
	getloginstatus(function(){
		if (LogInStatusCheck[0])
		{
			$(document).ready(function(){
				$("#mainNavbar").load("navbar.html", function(){
					$("#navbarSet").addClass("active");
					$("#navbarItemUser").addClass("active");
					$("#navbarlogin").hide();
					$("#navbarSet").hide();
					
					if (LogInStatusCheck[1])
					{
						$("#navbarSet").show();
						$("#userlist").show();
					}
				});
			});

			if (callback) {
				callback();
			}
		}
		else
		{
			window.location.replace("login.html");
		}
	});
}

// select user line
$("#userlist_body").on('change', function(){
	selecteduser = $('input[name=user]:checked', '#userlist_body').val();
	$("#ButtonChangeSelectedUser").prop('disabled', false);
});

// change selected user line
$("#ButtonChangeSelectedUser").on('click', function(){
	$("#userlist").hide();
	var selector = 2 * selecteduser -1;
	$("#inputchangeuser").val(userList[selector]);
	
	if(userList[selector + 1] == 'admin'){
		$("#radiochange_admin").prop('checked', true);
	} else {
		$("#radiochange_user").prop('checked', true);	
	}
	$("#changeuserlist").show();
	DisplayAlertInformation("\"user\" Daten anpassen", 0, function(){
		$("#alert_user").show();	
	});
});

//Save changed user data and check entry
$("#ButtonChangeUserList").on('click', function(){
	
});





