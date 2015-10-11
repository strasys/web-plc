<?php
/*
	class GPIO
	
	Johannes Strasser
	07.10.2015
	www.strasys.at
*/
class GPIO
{

	/*
	 * set the digital output 
	 *$out[$i] is an array  => (0 = off, 1 = on)
	 *$i is the (=number of digital output) 0 to 7 => OUT1 ... OUT8
	 */
	function setOut($out)
	{
		for ($i = 0; $i<8; $i++)
		{
			
			exec("flock /tmp/GPIOlock /usr/lib/cgi-bin/GPIOhandler s $i $out[$i]");
		}
	}
	/*
	 *For fast switching operations (flash light, etc.) it is recommended to use
	 *the setOutsingle function instead of the setOut function.
	 *$i (0 to 7) is the number of the digital output.
	 *$outs is 0 or 1 (0 = off, 1 = on) is the to be set value of the Output.
	 */
	function setOutsingle($outs, $i)
	{
		
		exec("flock /tmp/GPIOslock /usr/lib/cgi-bin/GPIOhandler s $i $outs");
	}
	/*
	 * The function getOut returns an array numbered 0..7 (=OUT 1 to OUT 8)
	 */
	function getOut()
	{
		unset($ausgabeOut);
		exec(" /usr/lib/cgi-bin/GPIOhandler g O", $ausgabeOut);
		
		return $ausgabeOut;
	}
	/*
	 * The function getIn returns an array numbered 0..3 (=IN 1 to 4)
	 */
	function getIn()
	{
		unset($ausgabeIn);
		exec(" /usr/lib/cgi-bin/GPIOhandler g I", $ausgabeIn);
		
		return $ausgabeIn;
	}
}
?>
