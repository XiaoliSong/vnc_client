<?php
	include "../connect.php";
	
	function del_dir($dirName)
	{
		if ( $handle = opendir( "$dirName" ) ) {
			while ( false !== ( $item = readdir( $handle ) ) ) {
				if ( $item != "." && $item != ".." ) {
					if ( is_dir( "$dirName/$item" ) ) {
						delDirAndFile( "$dirName/$item" );
					} else {
						unlink( "$dirName/$item" );
					}
				}
			}
			closedir( $handle );
			rmdir( $dirName );
		}
	}

	
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
			if($rowcount==1){//´æÔÚÓÃ»§
				$sql="SELECT id from members WHERE id='$delete_id'";
				$result=$conn->query($sql);
				$rowcount=$result->num_rows;
				if($rowcount==0){
					echo 0;
				}
				else{
					if($os_str=="Linux"){
						if (!file_exists("../file_manager/file".$delete_id)){
							$sql="DELETE FROM members WHERE id='$delete_id'";//É¾³ý
							if($result=$conn->query($sql)){
								echo 1;
							}
							else{
								echo -4;
							}
						}
						else{
							del_dir("../file_manager/file/".$delete_id);
							$sql="DELETE FROM members WHERE id='$delete_id'";//É¾³ý
							if($result=$conn->query($sql)){
								echo 1;
							}
							else{
								echo -4;
							}
						}
					}
					else{
						if (!file_exists(iconv("UTF-8","gb2312","../file_manager/file/".$delete_id))){
							$sql="DELETE FROM members WHERE id='$delete_id'";//É¾³ý
							if($result=$conn->query($sql)){
								echo 1;
							}
							else{
								echo -4;
							}
						}
						else{
							del_dir(iconv("UTF-8","gb2312","../file_manager/file/".$delete_id));
							$sql="DELETE FROM members WHERE id='$delete_id'";//É¾³ý
							if($result=$conn->query($sql)){
								$sql="DELETE FROM file WHERE upload_id='$delete_id'";//É¾³ý
								if($result=$conn->query($sql)){
									echo 1;
								}
								else{
									echo -5;
								}
							}
							else{
								echo -4;
							}
						}
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