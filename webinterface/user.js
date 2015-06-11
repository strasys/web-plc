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

 function setgetUserPassword(callback1){
		setgetuser("post","user.php",function()
			{
				if (xhttp.readyState==4 && xhttp.status==200)
				{
				var getUserInfo = JSON.parse(xhttp.responseText); 
				
				userInfo = [(getAIn.INvalue1),
				            (getAIn.INvalue2)
				               ];
					if (callback1){
						callback1();
					}
				}
			},"setgetAnalog=g&InOut=I");		
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