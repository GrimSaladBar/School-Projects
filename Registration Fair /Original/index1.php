

	<?php
	
		$servername = "localhost";
		$username = "root";
		$password = "";
		$dbname = "final examination";
		
		// Create connection
		$conn = mysqli_connect($servername, $username, $password, $dbname);
		
		
		$id=$_POST["id"];
		$firstname=$_POST["firstname"];
		$lastname=$_POST["lastname"];
		$telephone=$_POST["telephone"];
		$volunteerOption=$_POST["volunteerOption"];
		$confirmedField=$_POST["confirmedField"];
		
		if (!$conn)
		{
			die ('Error: '. mysqli_error($conn));
		}
		
		$sql=mysqli_query($conn, "INSERT INTO volunteers values('$id','$firstname','$lastname','$telephone','$volunteerOption', '$confirmedField')");
		
		if (!$sql)
{
die ('Error: '. mysqli_error($conn));
}
else
{
header("Location: thankyou.html");
}
mysqli_close($conn);
?>

	?>

