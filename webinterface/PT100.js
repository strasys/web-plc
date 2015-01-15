/**
 * Program to update the PT100 values and
 * to set the wire length offset.
 * 
 * 15.01.2015
 * Johannes Strasser
 * 
 * www.strasys.at
 */


// load functions ad webpage opening
function startatLoad(){
	loadNavbar();
}
window.onload=startatLoad();

//Load the top fixed navigation bar and highlight the 
//active site roots.
function loadNavbar(){
$(document).ready(function(){
	$("#mainNavbar").load("navbar.html", function(){
		$("#navbarFunction").addClass("active");
		$("#navbarItemPT100").addClass("active");
	
	  });
	});
}