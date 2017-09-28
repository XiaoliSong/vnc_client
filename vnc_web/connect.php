<?php 
	header("Content-type: text/html; charset=utf-8"); 
	function connect(){//连接数据库
		$host='localhost';				//数据库主机名
		$user='root';			//数据库连接用户名
		$pass='88068806a';				//对应的密码
		$db='vnc';						//数据库名
		$conn=new mysqli($host,$user,$pass,$db);
		if($conn->connect_errno){
			echo "连接数据库失败！<br />";
			return NULL;
		}
		else{
			return $conn;
		}
	}
?>