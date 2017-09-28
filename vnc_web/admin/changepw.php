<?php
	include "../connect.php";

	$id=$_GET["id"];
	$pw=$_GET["pw"];
	$new_pw=$_GET["new_pw"];

	$conn=connect();	
	if($conn!=NULL){
		$sql="SELECT id FROM admin_members WHERE id='$id' AND pw='$pw'";
		if ($result=$conn->query($sql)){
			$rowcount=$result->num_rows;
			$result->close();
			if($rowcount==1){//ดๆิฺำรปง
				$sql="UPDATE admin_members SET pw='$new_pw' WHERE id='$id'";
				if ($result=$conn->query($sql)){
					echo 1;
				}
				else{
					echo "-3"; 
				}
			}
			else{
				echo 0;
			}
		}
	}
	else{
		echo "-1";
	}
?>