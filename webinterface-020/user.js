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

//view set up at load
function viewatLoad(callback){
	 $("#alert_user").hide();
	 $("#adduser").hide();
	 $("#userlist").hide();
	 $("#changeuserlist").hide();
	 $("#changepassword_help").hide();
	 $("#changeuser_help").hide();
	 $("#ButtonChangeSelectedUser").prop('disabled', true);
	 $("#changepassword1_input").val("");

	 if (callback){
	 	callback();
	}
 }

//load functions at webpage opening
 function startatLoad(){
	 loadNavbar(function(){
		viewatLoad(function(){
			writeuserList();
		});
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

//user-Name: show helper
$("#inputchangeuser").focusin(function(){
	$("#changeuser_help").show();
});

//user: change text of helper while typing
$("#inputchangeuser").keyup(function(){
	var username = document.getElementById("inputchangeuser");
	var username_length = username.value.length;
	//Keine umlaute und keine Leerzeichen
	var username_umlaut = new RegExp(/(?=.+[\Ä\ä\Ü\ü\Ö\ö\ß\s])/);
	var username_str_umlaut = username_umlaut.test(username.value);

	if ((username_length > 2) && (username_length < 11)){
		$("#changeuser_help p:nth-child(3)").removeClass();
		$("#changeuser_help p:nth-child(3)").addClass("text-success");
		$("#changeuser_help p:nth-child(3) span").removeClass();
		$("#changeuser_help p:nth-child(3) span").addClass("glyphicon glyphicon-ok");	
	} else {
		$("#changeuser_help p:nth-child(3)").removeClass();
		$("#changeuser_help p:nth-child(3)").addClass("text-danger");
		$("#changeuser_help p:nth-child(3) span").removeClass();
		$("#changeuser_help p:nth-child(3) span").addClass("glyphicon glyphicon-remove");		
	}

	if (username_str_umlaut){
		$("#changeuser_help p:nth-child(2)").removeClass();
		$("#changeuser_help p:nth-child(2)").addClass("text-danger");
		$("#changeuser_help p:nth-child(2) span").removeClass();
		$("#changeuser_help p:nth-child(2) span").addClass("glyphicon glyphicon-remove");	
	} else {
		$("#changeuser_help p:nth-child(2)").removeClass();
		$("#changeuser_help p:nth-child(2)").addClass("text-success");
		$("#changeuser_help p:nth-child(2) span").removeClass();
		$("#changeuser_help p:nth-child(2) span").addClass("glyphicon glyphicon-ok");
	}	
});

//Password: show helper
$("#changepassword1 input").focusin(function(){
	$("#changepassword_help").show();
});

//Password: change text of helper while typing
$("#changepassword1_input").keyup(function(){
	var password = document.getElementById("changepassword1_input");
	var password_patt_Letter = new RegExp(/(?=.*[A-Z])(?=.{1,}[a-z])/);
	var password_patt_special = new RegExp(/(?=.{1,}[\_\?\!\#])/);
	var password_length = password.value.length;
	var password_patt = new RegExp(/^(?=.*[a-z])(?=.*[\_\?\!\#])(?=.*[A-Z]).{6,15}$/);
	var password_str_res_Letter = password_patt_Letter.test(password.value);
	var password_str_res_special = password_patt_special.test(password.value);
	var password_str_res = password_patt.test(password.value);


	if (password_str_res_Letter){
		$("#changepassword_help p:nth-child(2)").removeClass();
		$("#changepassword_help p:nth-child(2)").addClass("text-success");
		$("#changepassword_help p:nth-child(2) span").removeClass();
		$("#changepassword_help p:nth-child(2) span").addClass("glyphicon glyphicon-ok");	
	} else {
		$("#changepassword_help p:nth-child(2)").removeClass();
		$("#changepassword_help p:nth-child(2)").addClass("text-danger");
		$("#changepassword_help p:nth-child(2) span").removeClass();
		$("#changepassword_help p:nth-child(2) span").addClass("glyphicon glyphicon-remove");		
	}

	if (password_str_res_special){
		$("#changepassword_help p:nth-child(3)").removeClass();
		$("#changepassword_help p:nth-child(3)").addClass("text-success");
		$("#changepassword_help p:nth-child(3) span").removeClass();
		$("#changepassword_help p:nth-child(3) span").addClass("glyphicon glyphicon-ok");	
	} else {
		$("#changepassword_help p:nth-child(3)").removeClass();
		$("#changepassword_help p:nth-child(3)").addClass("text-danger");
		$("#changepassword_help p:nth-child(3) span").removeClass();
		$("#changepassword_help p:nth-child(3) span").addClass("glyphicon glyphicon-remove");		
	}
	
	if ((password_length > 5) && (password_length < 16)){
		$("#changepassword_help p:nth-child(4)").removeClass();
		$("#changepassword_help p:nth-child(4)").addClass("text-success");
		$("#changepassword_help p:nth-child(4) span").removeClass();
		$("#changepassword_help p:nth-child(4) span").addClass("glyphicon glyphicon-ok");	
	} else {
		$("#changepassword_help p:nth-child(4)").removeClass();
		$("#changepassword_help p:nth-child(4)").addClass("text-danger");
		$("#changepassword_help p:nth-child(4) span").removeClass();
		$("#changepassword_help p:nth-child(4) span").addClass("glyphicon glyphicon-remove");		
	}
	
	// show if entire password is true
	if (password_str_res){
		$("#changepassword1").removeClass();
		$("#changepassword1").addClass("input-group has-feedback has-success");
		$("#changepassword1 span").removeClass();
		$("#changepassword1 span").addClass("glyphicon glyphicon-ok form-control-feedback");
	}
});

//Password: Check password repeat
$("#changepassword2").focusout(function(){
	var password1 = document.getElementById("changepassword1_input").value;
	var password2 = document.getElementById("changepassword2_input").value;
	
	if ((password1 == password2) && (password2.length > 5)){
		$("#changepassword2").removeClass();
		$("#changepassword2").addClass("form-group has-feedback has-success");
		$("#changepassword2 span").removeClass();
		$("#changepassword2 span").addClass("glyphicon glyphicon-ok form-control-feedback");

	} else if ((password1 != password2) && (password2.length < 5)){
		$("#changepassword2").removeClass();
		$("#changepassword2").addClass("form-group has-feedback has-error");
		$("#changepassword2 span").removeClass();
		$("#changepassword2 span").addClass("glyphicon glyphicon-remove form-control-feedback");
	}
});

//Password: show password Text
$("#changepassword1 button").click(function(){
	var className = $("i").attr('class');
	if (className == 'glyphicon glyphicon-eye-open'){
		$("i").removeClass();
		$("i").addClass("glyphicon glyphicon-eye-close");
		document.getElementById("changepassword1_input").type = "password";
	}
	else if (className == 'glyphicon glyphicon-eye-close'){
		$("i").removeClass();
		$("i").addClass("glyphicon glyphicon-eye-open");
		document.getElementById("changepassword1_input").type = "text";
	}
});

//Save changed user data and check entry
$("#ButtonChangeUserList").on('click', function(){
	
});





