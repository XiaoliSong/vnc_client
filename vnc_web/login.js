function login_file(){
	var id=document.getElementById("id").value;
	var pw=document.getElementById("pw").value;
	pw=hex_sha1(pw);
	location.href="./file_manager/file_public.html?id="+id+"&pw="+pw;
}

function clearNotification(){
	document.getElementById("notification").innerHTML="";
}

document.onkeydown=function(event){
	var e = event || window.event || arguments.callee.caller.arguments[0];
	if(e && e.keyCode==13){ // enter ¼ü
		login();
	}
}; 