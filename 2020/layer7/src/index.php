<?php
error_reporting(0);
session_start();
require_once 'config.php';

if (isset($_SESSION['user'])) {
	$userinfo = preg_split('/\R/', $_SESSION['user']);
	$userid = $userinfo[0];
	$userlv = $userinfo[2];
	$msg = "hello, $userid (lv.$userlv)";
} else {
	$msg = "welcome, please login first";
}
?>
<!DOCTYPE html>
<html>
<head>
	<meta charset="utf-8">
	<title>ezbug</title>
</head>
<body>
	<h1>ezbug</h1>
	<p><?php echo $msg ?></p>
<?php
if (isset($_SESSION['user'])) {
?>	
	<a href="logout.php">logout</a>
	<a href="admin.php">admin</a>
<?php
} else {
?>
	<a href="login.php">login</a> 
	<a href="register.php">register</a> 
	<a href="admin.php">admin</a>
<?php
}
?>
</body>
</html>