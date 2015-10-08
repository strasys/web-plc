<?php
/*
	class GPIO
	
	Johannes Strasser
	07.10.2015
	www.strasys.at
*/
class GPIO
{
	private $OUT1;
	private $OUT2;
	private $OUT3;
	private $OUT4;
	private $OUT5;
	private $OUT6;
	private $OUT7;
	private $OUT8;
	
	/*Generate innitial Digital Output Settings.*/
/*	function __construct($out)
	{
		$this->$OUT1 = $out[0];
		$this->$OUT2 = $out[1];
		$this->$OUT3 = $out[2];
		$this->$OUT4 = $out[3];
		$this->$OUT5 = $out[4];
		$this->$OUT6 = $out[5];
		$this->$OUT7 = $out[6];
		$this->$OUT8 = $out[7];
	}
*/

	/*set the digital output (0 = off, 1 = on)  */
	function setOut($out)
	{
		for ($i = 0; $i<8; $i++)
		{
			exec(" /usr/lib/cgi-bin/GPIOhandler s $i $out[$i]");
		}
	}
	
	function getOut()
	{
	
	}
	
	function getIn()
	{
	
	}
}
?>
