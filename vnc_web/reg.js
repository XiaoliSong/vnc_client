

function reg(){
	var id=document.getElementById("id").value;
	var pw=document.getElementById("pw").value;
	
	if(id==""){
		var obj=document.getElementById("notification");
		obj.innerHTML="密码不能为空！";
		return;
	}
	
	if(pw=""){
		var obj=document.getElementById("notification");
		obj.innerHTML="密码不能为空！";
		return;
	}
	var reg_pw=document.getElementById("reg_pw").value;
	pw=hex_sha1(pw);
	
	var req_url="./reg.php?id="+id+"&pw="+pw+"&reg_pw="+reg_pw;
	var xmlhttp;
	if (window.XMLHttpRequest){// code for IE7+, Firefox, Chrome, Opera, Safari
		xmlhttp=new XMLHttpRequest();
	}
	
	else{// code for IE6, IE5
		xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
	}	

	xmlhttp.onreadystatechange=function() {
		if (xmlhttp.readyState==4 && xmlhttp.status==200){
			var obj=document.getElementById("notification");
			if(xmlhttp.responseText==1){
				obj.innerHTML="注册成功，1 S 后跳转到文件管理！";
				setTimeout(function(){
					location.href="./file_manager/file_public.html?id="+id+"&pw="+pw;
				},1000);
			}
			else{
				if(xmlhttp.responseText==2){
					obj.innerHTML="注册失败！注册码不对！";
				}
				else{
					if(xmlhttp.responseText==0){
						obj.innerHTML="注册失败！已经存在该用户名！";
					}
					else{
						obj.innerHTML="注册失败！错误码："+xmlhttp.responseText;
					}
				}
			}
		}
	};
	xmlhttp.open("POST",req_url,true);
	xmlhttp.send();
}

function clearNotification(){
	document.getElementById("notification").innerHTML="";
}

