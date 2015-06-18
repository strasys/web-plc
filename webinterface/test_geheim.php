<?php
session_start();
 if(!isset($_SESSION['username'])) 
    { 
    echo "Bitte erst <a href=\"login.html\">einloggen</a>";
    exit; 
    } 
?>