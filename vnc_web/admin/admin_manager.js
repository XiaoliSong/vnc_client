function add(){
	var add_id=document.getElementById("add_id").value;
	var add_pw=document.getElementById("add_pw").value;
	add_pw=hex_sha1(add_pw);
	var req_url="./admin_add.php?id="+get_query_string("id")+"&pw="+get_query_string("pw")+"&add_id="+add_id+"&add_pw="+add_pw;
	var xmlhttp;
	if (window.XMLHttpRequest){// code for IE7+, Firefox, Chrome, Opera, Safari
		xmlhttp=new XMLHttpRequest();
	}
	
	else{// code for IE6, IE5
		xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
	}	

	xmlhttp.onreadystatechange=function() {
		if (xmlhttp.readyState==4 && xmlhttp.status==200){
			var obj=document.getElementById("noti");
			if(xmlhttp.responseText==1){
				obj.innerHTML="添加成功!";
			}
			else{
				if(xmlhttp.responseText==0){
					obj.innerHTML="添加失败!已存在该账号！";
				}
				else{
					obj.innerHTML="错误："+xmlhttp.responseText;
				}
			}
		}
	};
	xmlhttp.open("POST",req_url,true);
	xmlhttp.send();
}

function delete_admin(){
	var delete_id=document.getElementById("delete_id").value;
	var req_url="./admin_delete.php?id="+get_query_string("id")+"&pw="+get_query_string("pw")+"&delete_id="+delete_id;
	var xmlhttp;
	if (window.XMLHttpRequest){// code for IE7+, Firefox, Chrome, Opera, Safari
		xmlhttp=new XMLHttpRequest();
	}
	
	else{// code for IE6, IE5
		xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
	}	

	xmlhttp.onreadystatechange=function() {
		if (xmlhttp.readyState==4 && xmlhttp.status==200){
			var obj=document.getElementById("noti");
			if(xmlhttp.responseText==1){
				obj.innerHTML="删除成功!";
			}
			else{
				if(xmlhttp.responseText==0){
					obj.innerHTML="删除失败!不存在该账号！";
				}
				else{
					obj.innerHTML="错误："+xmlhttp.responseText;
				}
			}
		}
	};
	xmlhttp.open("POST",req_url,true);
	xmlhttp.send();
}

function search(){
	var search_id=document.getElementById("search_id").value;
	var req_url="./admin_search.php?id="+get_query_string("id")+"&pw="+get_query_string("pw")+"&search_id="+search_id;
	var xmlhttp;
	if (window.XMLHttpRequest){// code for IE7+, Firefox, Chrome, Opera, Safari
		xmlhttp=new XMLHttpRequest();
	}
	
	else{// code for IE6, IE5
		xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
	}	

	xmlhttp.onreadystatechange=function() {
		if (xmlhttp.readyState==4 && xmlhttp.status==200){
			var obj=document.getElementById("noti");
			if(xmlhttp.responseText.length>2){
				var mem=JSON.parse(xmlhttp.responseText);
				obj.innerHTML="存在该管理员!<br />";
				obj.innerHTML+="管理员名："+mem[0]["id"]+"<br />";
				obj.innerHTML+="注册时间："+mem[0]["reg_time"]+"<br />";
				obj.innerHTML+="简介："+mem[0]["intro"]+"<br />";
			}
			else{
				if(xmlhttp.responseText==0){
					obj.innerHTML="不存在管理员!";
				}
				else{
					obj.innerHTML="错误："+xmlhttp.responseText;
				}
			}
		}
	};
	xmlhttp.open("POST",req_url,true);
	xmlhttp.send();
}

