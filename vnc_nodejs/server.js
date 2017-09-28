var mysql = require('mysql');
var sql_connection = mysql.createConnection({
  host:'localhost',
  user:'root',
  password:'88068806a',
  database:'vnc'
});

sql_connection.connect(function(err) {
  if (err) {
    console.error('mysql error connecting: ' + err.stack);
    return;
  }

  console.log('mysql connected as id ' + sql_connection.threadId);
});


function get_fun(msg){//解析命令
	var index=msg.indexOf(";");
	return msg.substring(0,index);
}

function get_content(msg){//获得内容
	var index=msg.indexOf(";");
	return msg.substring(index+1);
}


const WebSocket= require('ws');

msg_server = new WebSocket.Server({port:5800}); 

var server_map=new Map();

function is_exist_id_pw(id,pw)
{
	var result=server_map.get(id);
	if(result!=undefined&&result.pw==pw){
		return result;
	}
	return null;
}


function is_exist_id(id)
{
	var result=server_map.get(id);
	if(result==undefined){
		result=null;
	}
	return result;
}


function get_list()
{
	var list="list;"
	var temp_map=server_map;
	try{
		temp_map.forEach(function (value) {
			try{
				list=list+value.id+";";
			}
			catch(err){
			}
		});
	}
	catch(err){
		return list;	
	}
	return list;
}



function ad_newer(ws_id){
	var temp_map=server_map;

	temp_map.forEach(function (value) {
		try{
			value.send("newer;"+ws_id);
		}
		catch(err){
		}
	});
}


function ad_outer(ws_id){
	var temp_map=server_map;
	temp_map.forEach(function (value) {
		try{
			value.send("outer;"+ws_id)
		}
		catch(err){
		}
	});
}


function delete_view_client(ws,ws_id)
{	
	ws.view_clients_id.delete(ws_id);
	if(ws==null) return;
	try{
		for(var i=0;i<ws.view_clients.length;i++)
		{
			if(ws.view_clients[i].id==ws_id){
				ws.view_clients[i].close();
				ws.view_clients.splice(i,1);
				break;
			}
		}
	}
	catch(err){
	}
}


function delete_control_client(ws,ws_id)
{
	ws.control_clients_id.delete(ws_id);
	if(ws==null) return;
	try{
		for(var i=0;i<ws.control_clients.length;i++)
		{
			if(ws.control_clients[i].id==ws_id){
				ws.control_clients[i].close();
				ws.control_clients.splice(i,1);
				break;
			}
		}
	}
	catch(err){
	}
}

msg_server.on('connection',function(ws) {
	console.log('连接设备');
	ws.id="";
	ws.pw="";
	ws.on('message',function(msg){
		console.log(msg);
		var fun=get_fun(msg);
		var content=get_content(msg);
		switch(fun)
		{
			case "signal":{
				var temp_id=get_fun(content);
				var signal_content=get_content(content);
				var temp_ws=is_exist_id(temp_id);
				if(temp_ws!=null){
					try{
						temp_ws.send("signal;"+ws.id+";"+signal_content);
					}
					catch(err){
					}
				}
				else{
					ad_outer(temp_id);
					return;
				}
				if(signal_content=="pass_view"||signal_content=="push_view"){
					ws.vnc_ws.view_clients_id.add(temp_id);
					return;
				}
				if(signal_content=="close_view"){
					delete_view_client(ws.vnc_ws,temp_id);
					return;
				}
				if(signal_content=="pass_control"||signal_content=="push_control"){
					ws.vnc_ws.view_clients_id.add(temp_id);
					ws.vnc_ws.control_clients_id.add(temp_id);
					return;
				}
				if(signal_content=="close_control"){
					delete_control_client(ws.vnc_ws,temp_id);
					return;
				}
				return;
			}
			case "getlist":{
				var temp_list=get_list();
				console.log(temp_list);
				try{
					ws.send(temp_list);
				}
				catch(err){
				}
				break;
			}
			case "login":{//登录验证
				var index=content.indexOf(";");
				ws.id=content.substring(0,index);
				ws.pw=content.substring(index+1);
				if(is_exist_id(ws.id)!=null){
					ws.send("login;again");
					return;
				}
				var sql_params=[ws.id,ws.pw];
				var sql = 'SELECT id FROM members WHERE id=? AND pw=?';
				sql_connection.query(sql,sql_params, function (error, result, fields) {
					if(error){
						console.log('[SELECT ERROR] - ',error.message);
						return;
					}
					else{
						if(result.length==1){//密码验证通过
							console.log('密码验证通过');
							ws.send("login;pass");
							ad_newer(ws.id);
							server_map.set(ws.id,ws);
							ws.on('close',function(){
								console.log("msg服务端 "+ws.id+" 关闭连接");
								server_map.delete(ws.id);
								ad_outer(ws.id);
							});
						}
						else{//密码验证失败
							console.log('密码验证失败');
							console.log(ws.id);
							console.log(ws.pw);
							ws.send("login;error");
						}
					}
				});
				break;
			}
			
			default:{
				break;
			}
		}
	});
	
	
});

msg_server.on('close',function() {
	console.log("\n\n\n\n msg服务器关闭!\n\n\n\n");
});



vnc_server = new WebSocket.Server({port:5801}); 

vnc_server.on('connection', function(ws) {
	ws.id="";
	ws.pw="";
	ws.count=0;
	ws.view_clients=[];
	ws.view_clients_id=new Set();
	ws.control_clients=[];
	ws.control_clients_id=new Set();
	ws.on('message',function(msg){
		if(ws.count==2){
			
			for(var i=0;i<ws.control_clients.length;i++)
			{
				try{
					ws.control_clients[i].send(msg);
				}
				catch(err){
				}
				//console.log("发送数据");
			}
			
			for(var i=0;i<ws.view_clients.length;i++)
			{
				try{
					ws.view_clients[i].send(msg);
				}
				catch(err){
				}
				//console.log("发送数据");
			}
			return;
		}
		if(ws.count==0){
			ws.headerMsg=msg;
			ws.count++;
		}
		else{
			var index=msg.indexOf(";");
			ws.id=msg.substring(0,index);
			ws.pw=msg.substring(index+1);
			ws.msg_ws=is_exist_id_pw(ws.id,ws.pw);
			if(ws.msg_ws!=null){
				ws.msg_ws.vnc_ws=ws;
				ws.send("pass");
				ws.count++;
				console.log("vnc服务端"+ws.id+"连接成功");
			}
			else{
				ws.send("error");
				ws.close();
				console.log("vnc服务端"+ws.id+"连接失败");
			}
		}
	});
});


vnc_server.on('close', function(ws) { 
	console.log("\n\n\n\n vnc服务器关闭!\n\n\n\n");
});



client_listener = new WebSocket.Server({port:5802}); 
var clients=[] ;
client_listener.on('connection', function(ws) {
	ws.count=0;
	ws.wss=null;
	ws.id="";
	ws.pw="";
	ws.on('message',function(msg){
		console.log(msg);
		if(ws.count==1){
			if(ws.way=="control"){//控制模式
				try{
					ws.wss.send(msg);
				}
				catch(err){
				}
			}
			return;
		}
		if(ws.count==0){
			var index=msg.indexOf(";");
			ws.id=msg.substring(0,index);
			
			msg=msg.substring(index+1);
			index=msg.indexOf(";");
			ws.pw=msg.substring(0,index);
			
			if(is_exist_id_pw(ws.id,ws.pw)==null){//密码验证失败
				ws.send("error_login");
				return;
			}
	
			msg=msg.substring(index+1);
			index=msg.indexOf(";");
			ws.to_see_id=msg.substring(0,index);
			ws.wss=is_exist_id(ws.to_see_id);
			if(ws.wss==null){//不存在vnc服务
				console
				ws.send("error_access");
				return;
			}
			ws.wss=ws.wss.vnc_ws;
			if(ws.wss==null){//不存在vnc服务
				ws.send("error_access");
				return;
			}
			
			ws.way=msg.substring(index+1);
			
			if(ws.way=="view"){
				if(ws.wss.view_clients_id.has(ws.id)){
					console.log(ws.id+" 查看 "+ws.wss.id);
					ws.send("view");
					ws.send(ws.wss.headerMsg);
					ws.wss.view_clients.push(ws);
					ws.on('close',function(){
						for(var i=0;i<ws.wss.view_clients.length;i++)
						{
							if(ws.wss.view_clients[i]==ws){
								ws.wss.view_clients.splice(i,1);
								break;
							}
						}
					});
				}
				else{
					ws.send("error_access");
				}
			}
			
			if(ws.way=="control"){
				if(ws.wss.control_clients_id.has(ws.id)){
					console.log(ws.id+" 控制 "+ws.wss.id);
					ws.send("control");
					ws.send(ws.wss.headerMsg);
					ws.wss.control_clients.push(ws);
					ws.on('close',function(){
						for(var i=0;i<ws.wss.control_clients.length;i++)
						{
							if(ws.wss.control_clients[i]==ws){
								ws.wss.control_clients.splice(i,1);
								break;
							}
						}
					});
				}
				else{
					ws.send("error_access");
				}
			}
			
			ws.count++;
		}
	});
	console.log("客户端连接设备");
});

client_listener.on('close', function(ws) {  	
	console.log("\n\n\n\n client服务器关闭!\n\n\n\n");
});

console.log("服务程序启动");