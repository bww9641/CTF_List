<?php
error_reporting(0);

function sanitize($str) {
	$retval = preg_replace("/'|\"|\\\\|\s|<|>/", "", $str);
	return $retval;
}
function redirect($url, $msg="") {
	die("<script>if('$msg'!=''){alert('$msg');}location.href='$url';</script>");
}

$flag = '[censored]';
$db = new mysqli("localhost", "[censored]", "[censored]", "ezbug");
$db or die('connection failed');