<!DOCTYPE html>
<html>

<?php
    //code here
    echo "Current time: " . date("Y-m-d h:i:sa");

?>
	<head>

		<meta charset="UTF-8">
		<title>PHP login</title>
	</head>

	<body>
		<div>
			<form name="myForm" action="index.php" onsubmit="return validateForm()" method="POST">
			<p>
				Username: <input type="text" required pattern="\w+" name="username">
			</p>
			<p>
				Password: <input type="text" required pattern="(?=.*\d)(?=.*[a-z])(?=.*[A-Z]).{6,}" name="pwd1" onchange="form.pwd2.pattern = this.value;">
			</p>
			<p>
				Confirm Password: <input title="Please enter the same password as above" type="password" required pattern="(?=.*\d)(?=.*[a-z])(?=.*[A-Z]).{6,}" name="pwd2" onchange="this.setCustomValidity(this.validity.patternMismatch ? this.title: '');">
			</p>
			<input type="submit" value= "Submit!!">
			</form>


		</div>
	</body>

</html>