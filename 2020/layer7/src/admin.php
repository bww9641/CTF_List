<?php
error_reporting(0);
session_start();
require_once 'config.php';

if (!isset($_SESSION['user'])) {
	die('please login first');
}
$userinfo = preg_split('/\R/', $_SESSION['user']);
$userid = $userinfo[0];
$userlv = $userinfo[2];

if ($userlv > 9) {
	echo "hello admin, this is for you!<br>";
	echo $flag;
} else {
	echo "hi $userid, but you are not admin.";
}