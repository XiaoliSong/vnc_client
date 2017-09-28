#include "msg_client.h"


void Msg_client::on_to_connect(QString url)
{
	connect(&msg_webSocket, &QWebSocket::connected, this, &Msg_client::onConnected);
	connect(&msg_webSocket, &QWebSocket::disconnected, this, &Msg_client::onClosed);
	connect(&msg_webSocket, &QWebSocket::abort, this, &Msg_client::onClosed);
	msg_webSocket.ignoreSslErrors();
	connect(&msg_webSocket, &QWebSocket::textMessageReceived, this, &Msg_client::onTextMessageReceived);
	msg_webSocket.open(QUrl(url));

}

void Msg_client::on_to_login(QString id, QString pw)
{
	if (is_connected == true) {
		msg_webSocket.sendTextMessage(QString("login;").append(id).append(";").append(pw));
		msg_webSocket.flush();
	}
}


void Msg_client::onClosed()
{
	emit(to_login_dialog("connect;close"));
	emit(to_app("connect;close"));
}

void Msg_client::onConnected()
{
	this->is_connected = true;
	emit(to_login_dialog("connect;pass"));
}


void Msg_client::onTextMessageReceived(QString message)
{
	emit(to_app(message));
	if (get_fun(message) == "login") {
		emit(to_login_dialog(message));
	}
}

void Msg_client::send_msg(QString message)
{
	if (this->is_connected) {
		msg_webSocket.sendTextMessage(message);
		msg_webSocket.flush();
	}		
}