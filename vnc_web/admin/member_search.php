<?php
	include "../connect.php";
	$account=10;
	$id=$_GET["id"];
	$pw=$_GET["pw"];
	$search_id=$_GET["search_id"];
	
	$conn=connect();	
	if($conn!=NULL){
		$sql="SELECT id FROM admin_members WHERE id='$id' AND pw='$pw'";
		if ($result=$conn->query($sql)){
			$rowcount=$result->num_rows;
			$result->close();
			if($rowcount==1){//ดๆิฺำรปง
				$sql="SELECT id,reg_time,intro from members WHERE id='$search_id'";
				$result=$conn->query($sql);
				$rowcount=$result->num_rows;
				if($rowcount==1){
					$arr=array();
					$result=$conn->query($sql);
					while ($row = mysqli_fetch_assoc($result))
					{
						$arr[]=$row;
					}
					echo json_encode($arr);
					$result->close();
				}
				else{
					echo 0;
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