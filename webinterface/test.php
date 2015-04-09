<?php 
echo "Test!!";
chdir('/usr/lib/cgi-bin');
exec("./GPIOhandler g O", $ausgabe);
//$ausgabe[0] = 190;
echo $ausgabe[0];


?>