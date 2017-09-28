var page=get_query_string("page");
if(page==null||page<0){
	page=0;
}

function member_list(responseText){
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
				obj.innerHTML="当前没有用户！";
				return;
			}
		}
	}
	
	var member=JSON.parse(responseText);

	var parent_obj=document.getElementById("list");
	for(var i=0;i<member.length;i++)
	{
		var d = new Date(member[i]['reg_time']);
		var date=d.getFullYear()+"-"+(d.getMonth()+1)+"-"+d.getDate();
		var tr_ele=document.createElement("tr");//js新建元素
		tr_ele.innerHTML="<td>"+member[i]['id']+"</td>";
		tr_ele.innerHTML+="<td>"+date+"</td>";
		tr_ele.innerHTML+="<td>"+member[i]['intro']+"</td>";
		parent_obj.appendChild(tr_ele);
	}

	if(member.length==0){
		var obj=document.getElementById("noti");
		obj.innerHTML="当前没有用户！";
	}
	if(member.length>=10){
		document.getElementById("next-page").style.visibility="visible";
	}
}

function get_member(){
	var req_url="./member_get.php?id="+get_query_string("id")+"&pw="+get_query_string("pw")+"&page="+page;
	var xmlhttp;
	if (window.XMLHttpRequest){// code for IE7+, Firefox, Chrome, Opera, Safari
		xmlhttp=new XMLHttpRequest();
	}
	
	else{// code for IE6, IE5
		xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
	}	

	xmlhttp.onreadystatechange=function() {
		if (xmlhttp.readyState==4 && xmlhttp.status==200){
			member_list(xmlhttp.responseText)
		}
	};
	xmlhttp.open("POST",req_url,true);
	xmlhttp.send();
}

get_member();

if(page==0){
	document.getElementById("former-page").style.visibility="hidden";
	document.getElementById("former-page").href="./member_list.html?id="+get_query_string("id")+"&pw="+get_query_string("pw")+"&page="+page;
}
else{
	document.getElementById("former-page").style.visibility="visible";
	var temp_page=page-1;
	document.getElementById("former-page").href="./member_list.html?id="+get_query_string("id")+"&pw="+get_query_string("pw")+"&page="+temp_page;
}

var temp_page=parseInt(page)+1;
document.getElementById("next-page").href="./member_list.html?id="+get_query_string("id")+"&pw="+get_query_string("pw")+"&page="+temp_page;
document.getElementById("page_noti").innerHTML=page;