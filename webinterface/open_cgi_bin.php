<html>
<body>
<?php

echo "exec ab hier <br>";
$ausgabe;
unset($ausgabe);
exec("./cgi-bin/RTChandler s d 3 12 11 14", &$ausgabe);
echo "Date (dow hh:mm:ss) : " . $ausgabe[0] . " " . $ausgabe[1];
echo ":" . $ausgabe[2] . ":" . $ausgabe[3] . "<br>"; 
echo "Time: " . $ausgabe[4] . ":" . $ausgabe[5] . ":" . $ausgabe[6] . "<br>";
?>
</body>
</html>
