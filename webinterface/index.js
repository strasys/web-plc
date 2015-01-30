/**
 * Program for start side.
 * 
 * Johannes Strasser
 * 15.01.2015
 * www.strasys.at
 * 
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
		$("#navbarHome").addClass("active");	
	  });
	});
}
