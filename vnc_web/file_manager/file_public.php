<?php
	include "../connect.php";
	$account=10;
	$id=$_GET["id"];
	$pw=$_GET["pw"];
	$page=$_GET["page"];
	$left=$account*$page;
	
	$conn=connect();	
	if($conn!=NULL){
		$sql="SELECT id FROM members WHERE id='$id' AND pw='$pw'";
		if ($result=$conn->query($sql)){
			$rowcount=$result->num_rows;
			$result->close();
			if($rowcount==1){//存在用户
				$sql="SELECT * from file ORDER BY time desc limit $left,$account";
				$result=$conn->query($sql);
				$rowcount=$result->num_rows;
				
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
				echo -2;
			}
		}
	}
	else{
		echo -1;
	}

?>