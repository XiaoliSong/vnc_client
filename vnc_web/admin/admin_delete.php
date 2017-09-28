<?php
	include "../connect.php";
	
	$os_name=PHP_OS;
	if(strpos($os_name,"Linux")!==false){
		$os_str="Linux";
	}else if(strpos($os_name,"WIN")!==false){
		$os_str="Windows";
	}
	
	$account=10;
	$id=$_GET["id"];
	$pw=$_GET["pw"];
	$delete_id=$_GET["delete_id"];
	
	$conn=connect();	
	if($conn!=NULL){
		$sql="SELECT id FROM admin_members WHERE id='$id' AND pw='$pw'";
		if ($result=$conn->query($sql)){
			$rowcount=$result->num_rows;
			$result->close();
			if($rowcount==1){//ดๆิฺำรปง
				$sql="SELECT id from admin_members WHERE id='$delete_id'";
				$result=$conn->query($sql);
				$rowcount=$result->num_rows;
				if($rowcount==0){
					echo 0;
				}
				else{
					$sql="DELETE FROM admin_members WHERE id='$delete_id'";//ษพณý
					if($result=$conn->query($sql)){
						echo 1;
					}
					else{
						echo -3;
					}		
				}
			}
			else{
				echo -2;
			}
		}
	}
	else{
		echo -1;
	}

?>