/**
 * user and user rights management
 * 
 * 10.06.2015
 * Johannes Strasser
 * 
 * www.strasys.at
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
		$("#navbarSet").addClass("active");
		$("#navbarItemUser").addClass("active");
	  });
	});
}