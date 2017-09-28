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
	$add_id=$_GET["add_id"];
	$add_pw=$_GET["add_pw"];
	
	$conn=connect();	
	if($conn!=NULL){
		$sql="SELECT id FROM admin_members WHERE id='$id' AND pw='$pw'";
		if ($result=$conn->query($sql)){
			$rowcount=$result->num_rows;
			$result->close();
			if($rowcount==1){//存在用户
				$sql="SELECT id from admin_members WHERE id='$add_id'";
				$result=$conn->query($sql);
				$rowcount=$result->num_rows;
				if($rowcount==1){
					echo 0;
				}
				else{
					date_default_timezone_set('PRC'); 
					$time=date('Y-m-d H:i:s',time());
					$sql="INSERT INTO admin_members SET id='$add_id',pw='$add_pw',reg_time='$time' ";//插入
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