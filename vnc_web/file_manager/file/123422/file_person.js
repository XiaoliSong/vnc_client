function get_query_string(name){
     var reg = new RegExp("(^|&)"+ name +"=([^&]*)(&|$)");
     var r = window.location.search.substr(1).match(reg);
     if(r!=null) return  unescape(r[2]); 
	 return null;
}

document.getElementById("back_to_all").href="./file_public.html?id="+get_query_string("id")+"&pw="+get_query_string("pw")+"&page=0";
document.getElementById("back_to_self").href="./file_person.html?id="+get_query_string("id")+"&pw="+get_query_string("pw")+"&to_see_id="+get_query_string("id")+"&page=0";
document.title=get_query_string("to_see_id")+"的文件";

if(get_query_string("id")==get_query_string("to_see_id")){
	document.getElementById("upload_iframe").src="./file_upload.html?id="+get_query_string("id")+"&pw="+get_query_string("pw");
}
else{
	document.getElementById("upload_iframe").style.display="none";
}
var page=get_query_string("page");

//删除文件
function delete_file(name){
	var req_url="./file_delete.php?id="+get_query_string("id")+"&pw="+get_query_string("pw")+"&name="+name;
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
				obj.innerHTML="删除成功！";
				setTimeout("alert('删除成功！');window.location.reload()",300);
			}
			else{
				obj.innerHTML="删除失败！错误码："+xmlhttp.responseText;
			}
		}
	};
	xmlhttp.open("POST",req_url,true);
	xmlhttp.send();
}

//显示文件
function file_display(responseText){
	if(responseText==-1){
		var obj=document.getElementById("noti");
		obj.innerHTML="连数据库失败！"
		return;
	}
	else{
		if(responseText==-2) {
			var obj=document.getElementById("noti");
			obj.innerHTML="账号密码不匹配！"
			return;
		}
		else{
			if(responseText==""){
				var obj=document.getElementById("noti");
				obj.innerHTML="当前没有文件！";
				return;
			}
		}
	}
	
	var file=JSON.parse(responseText);
	
	var parent_obj=document.getElementById("file_table");
	if(get_query_string("id")==get_query_string("to_see_id")){
		document.getElementById("file_th").innerHTML+="<th>操作</th>"
	}
	for(var i=0;i<file.length;i++)
	{
		var d = new Date(file[i]['time']);
		var date=d.getFullYear()+"-"+(d.getMonth()+1)+"-"+d.getDate();
		var tr_ele=document.createElement("tr");//js新建元素
		tr_ele.innerHTML="<td>"+date+"</td>";
		var upload_id_info="<td><a href='file_person.html?id="+get_query_string("id")+"&pw="+get_query_string("pw")+"&to_see_id="+file[i]['upload_id']+"&page=0'>"+file[i]['upload_id']+"</a></td>";
		tr_ele.innerHTML+=upload_id_info;
		tr_ele.innerHTML+="<td><a href='./file/"+file[i]['upload_id']+"/"+file[i]['name']+"'>"+file[i]['name']+"</a></td>";
		if(get_query_string("id")==get_query_string("to_see_id")){
			tr_ele.innerHTML+="<td><button onclick=\" delete_file(\'"+file[i]['name']+"\')\">删除</button>"
		}
		parent_obj.appendChild(tr_ele);
	}
	
	if(file.length==0){
		var obj=document.getElementById("noti");
		obj.innerHTML="当前没有文件！";
	}
	if(file.length>=10){
		document.getElementById("next-page").style.visibility="visible";
	}
}


//ajax获取文件
function getFile(){
	var req_url="./file_person.php?id="+get_query_string("id")+"&pw="+get_query_string("pw")+"&to_see_id="+get_query_string("to_see_id")+"&page="+page;
	var xmlhttp;
	if (window.XMLHttpRequest){// code for IE7+, Firefox, Chrome, Opera, Safari
		xmlhttp=new XMLHttpRequest();
	}
	
	else{// code for IE6, IE5
		xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
	}	

	xmlhttp.onreadystatechange=function() {
		if (xmlhttp.readyState==4 && xmlhttp.status==200){
			file_display(xmlhttp.responseText);
		}
	};
	xmlhttp.open("POST",req_url,true);
	xmlhttp.send();
}
getFile();

if(page==0){
	document.getElementById("former-page").style.visibility="hidden";
	document.getElementById("former-page").href="./file_person.html?id="+get_query_string("id")+"&pw="+get_query_string("pw")+"&to_see_id="+get_query_string("to_see_id")+"&page="+page;
}
else{
	document.getElementById("former-page").style.visibility="visible";
	var temp_page=page-1;
	document.getElementById("former-page").href="./file_person.html?id="+get_query_string("id")+"&pw="+get_query_string("pw")+"&to_see_id="+get_query_string("to_see_id")+"&page="+temp_page;
}

var temp_page=parseInt(page)+1;
document.getElementById("next-page").href="./file_person.html?id="+get_query_string("id")+"&pw="+get_query_string("pw")+"&to_see_id="+get_query_string("to_see_id")+"&page="+temp_page;
document.getElementById("page_noti").innerHTML=page;


