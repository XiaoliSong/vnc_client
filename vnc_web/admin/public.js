function get_query_string(name){
     var reg = new RegExp("(^|&)"+ name +"=([^&]*)(&|$)");
     var r = window.location.search.substr(1).match(reg);
     if(r!=null) return  unescape(r[2]); 
	 return null;
}

document.getElementById("to_member_list").href="./member_list.html?id="+get_query_string("id")+"&pw="+get_query_string("pw")+"&page=0";
document.getElementById("to_member_manager").href="./member_manager.html?id="+get_query_string("id")+"&pw="+get_query_string("pw");
document.getElementById("to_admin_list").href="./admin_list.html?id="+get_query_string("id")+"&pw="+get_query_string("pw")+"&page=0";
document.getElementById("to_admin_manager").href="./admin_manager.html?id="+get_query_string("id")+"&pw="+get_query_string("pw");