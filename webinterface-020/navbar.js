/**
 * Navbar Functions
 * 
 * Johannes Strasser
 * 01.02.2017
 * www.strasys.at
 * 
 */


$('#navbar').on('shown.bs.collapse', function () {
       $("#navbar_collapse_button_glyphicon").removeClass("glyphicon-option-vertical").addClass("glyphicon-remove");
    });

$('#navbar').on('hidden.bs.collapse', function () {
       $("#navbar_collapse_button_glyphicon").removeClass("glyphicon-remove").addClass("glyphicon-option-vertical");
    });








