#pragma once

#include "head.h"
#include "app.h"
#include "vnc_app.h"
#include "parse.h"
#include "msg_client.h"

class Login_dialog :public QDialog
{
	Q_OBJECT
private:
	QLineEdit *id_edit;
	QLineEdit *pw_edit;
	QPushButton *login_btn;
	QRadioButton *remmber_btn;
	QLabel *noti_label;
	QString id;
	QString pw;
	QString url;
	QString msg_port;
	QString msg_url;
	QString vnc_port;
	QString vnc_url;
	Msg_client* p_msg_client;

public:
	explicit Login_dialog(QWidget *parent = 0);
	void set_msg_client(Msg_client *msg_client) {
		this->p_msg_client = msg_client;
	}
	void init();
	void write_config();
	void login();
	void connect_to_server() {
		emit(to_connect(msg_url));
		noti_label->setText("连接服务器中....");
	};
	~Login_dialog() {};
signals:
	void to_login(QString id, QString pw);
	void to_connect(QString msg_url);
public slots:
	void on_msg_client(QString msg);
};
