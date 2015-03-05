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
		$("#navbarItemAIO").addClass("active");
	
	  });
	});
}