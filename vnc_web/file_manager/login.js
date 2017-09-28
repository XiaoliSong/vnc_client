function login_public(){
	var id=document.getElementById("id").value;
	var pw=document.getElementById("pw").value;
	pw=hex_sha1(pw);
	location.href="./file_public.html?id="+id+"&pw="+pw+"&page=0";
}

function login_person(){
	var id=document.getElementById("id").value;
	var pw=document.getElementById("pw").value;
	pw=hex_sha1(pw);
	location.href="./file_person.html?id="+id+"&pw="+pw+"&to_see_id="+id+"&page=0";
}

function clearNotification(){
	document.getElementById("notification").innerHTML="";
}

document.onkeydown=function(event){
	var e = event || window.event || arguments.callee.caller.arguments[0];
	if(e && e.keyCode==13){ // enter ¼ü
		login_public();
	}
}; 