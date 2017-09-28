<?php
	include "../connect.php";
	$os_name=PHP_OS;
	if(strpos($os_name,"Linux")!==false){
		$os_str="Linux";
	}else if(strpos($os_name,"WIN")!==false){
		$os_str="Windows";
	}
	
	$id=$_GET["id"];
	$pw=$_GET["pw"];
	$name=$_GET["name"];
	$path="./file/".$id;
	
	
	$conn=connect();	
	if($conn!=NULL){
		$sql="SELECT id FROM members WHERE id='$id' AND pw='$pw'";
		if ($result=$conn->query($sql)){
			$rowcount=$result->num_rows;
			$result->close();
			if($rowcount==1){//存在用户
				$sql="SELECT upload_id FROM file WHERE upload_id='$id' AND name='$name'";
				if ($result=$conn->query($sql)){
					$rowcount=$result->num_rows;
					$result->close();
					if($rowcount==1){//存在文件
						$sql="DELETE FROM file WHERE upload_id='$id' AND name='$name'";
						if ($result=$conn->query($sql)){
							$result=false;
							if($os_str=="Linux"){
								$result = @unlink ($path."/".$name); 
							}
							else{
								$result = @unlink (iconv("UTF-8","gb2312", $path."/".$name)); 
							}
							if ($result == true) { 
								echo '1'; 
							} 
							else { 
								echo "-4"; 
							} 
						}
					}
					else{
						echo "-3"; 
					}
				}
			}
			else{
				echo "-2";
			}
		}
	}
	else{
		echo "-1";
	}
?>