/**
 * login handling client
 * Johannes Strasser
 * www.strasys.at
 * 08.06.2015
 * 
 */


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
