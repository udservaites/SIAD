<?php
	echo "Index page\n";

	//lets store a login session in $_SESSION[""]
	
	if(isset($_SESSION["logged"])) {
		echo "You have been here before! Welcome back!!";

	}else {

		echo "You have not logged in before!";
	}




?>
