#pragma once
#include "head.h"
#include "parse.h"

class Msg_client :public QObject {
	Q_OBJECT
public:
	Msg_client(QWidget *parent = 0) {};
	QWebSocket msg_webSocket;
	bool is_connected = false;
signals:
	void to_login_dialog(QString msg);
	void to_app(QString message);
public slots:
	void on_to_connect(QString url);
	void on_to_login(QString id, QString pw);
	void send_msg(QString message);
	void onClosed();
	void onConnected();
	void onTextMessageReceived(QString message);
};