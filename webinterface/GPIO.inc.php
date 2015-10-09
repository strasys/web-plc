<?php
/*
	class GPIO
	
	Johannes Strasser
	07.10.2015
	www.strasys.at
*/
class GPIO
{

	/*set the digital output (0 = off, 1 = on)  */
	function setOut($out)
	{
		for ($i = 0; $i<8; $i++)
		{
			unset($ausgabe);
			exec(" /usr/lib/cgi-bin/GPIOhandler s $i $out[$i]", $ausgabe);
		}
	}
	
	function getOut()
	{
		unset($ausgabe);
		exec(" /usr/lib/cgi-bin/GPIOhandler g O", $ausgabeOut);
		
		return $ausgabeOut;
	}
	
	function getIn()
	{
		unset($ausgabe);
		exec(" /usr/lib/cgi-bin/GPIOhandler g I", $ausgabeIn);
		
		return $ausgabeIn;
	}
}
?>
