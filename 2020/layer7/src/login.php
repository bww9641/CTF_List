<?php
error_reporting(0);
session_start();
require_once 'config.php';

if (isset($_POST['submit'])) {
	$userid = sanitize($_POST['userid']);
	$userpw = sanitize($_POST['userpw']);

	$result = $db->query("SELECT * FROM users WHERE userid='{$userid}' AND userpw='{$userpw}'");
	if ($user = $result->fetch_array(MYSQLI_ASSOC)) {
		$userid = $user['userid'];
		$userpw = $user['userpw'];
		$userlv = $user['userlv'];
		$_SESSION['user'] = "$userid\r\n$userpw\r\n$userlv";
		redirect("index.php", "hello, $userid");
	}
	redirect("login.php", "failed!");
}
?>
<!DOCTYPE html>
<html>
<head>
	<meta charset="utf-8">
	<title>ezbug</title>
</head>
<body>
	<h1>login</h1>
	<form method="POST">
		<input type="text" name="userid" placeholder="userid" autofocus>
		<input type="password" name="userpw" placeholder="userpw"><br>
		<input type="submit" name="submit" value="login">
	</form>
</body>
</html>