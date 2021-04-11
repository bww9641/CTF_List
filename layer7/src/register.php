<?php
error_reporting(0);
require_once 'config.php';

if (isset($_POST['submit'])) {
	$userid = sanitize($_POST['userid']);
	$userpw = sanitize($_POST['userpw']);
	$userlv = 1;

	$user_exists = $db->query("SELECT * FROM users WHERE userid='{$userid}'");
	if ($user_exists->fetch_array(MYSQLI_NUM)) {
		redirect("register.php", "already user exists!");
	}

	$insert_user = "INSERT INTO users VALUES ('{$userid}', '{$userpw}', {$userlv})";
	$db->query($insert_user);
	$db->close();

	redirect("login.php", "welcome!");
}
?>
<!DOCTYPE html>
<html>
<head>
	<meta charset="utf-8">
	<title>ezbug</title>
</head>
<body>
	<h1>register</h1>
	<form method="POST">
		<input type="text" name="userid" placeholder="userid" autofocus>
		<input type="password" name="userpw" placeholder="userpw"><br>
		<input type="submit" name="submit" value="register">
	</form>
</body>
</html>