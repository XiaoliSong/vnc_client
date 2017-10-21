#pragma once
#include "head.h"

class Member : public QDialog
{
	Q_OBJECT
private:
	QString id;
	QString vnc_web_url;

	bool is_view = false;
	bool is_control = false;
	bool is_push_view = false;
	bool is_push_control = false;
	
	QLabel *id_label;
	QPushButton *view_btn;
	QPushButton *control_btn;
	QPushButton *push_view_btn;
	QPushButton *push_control_btn;
public:
	Member(QString id, QString vnc_web_url, QWidget *parent = 0);
	~Member() {};
	void set_view_enabled();
	void set_control_enabled();
	void recv_msg(QString msg);
signals:
	void send_msg(QString msg);
private:
	void view();
	void control();
	void push_view();
	void push_control();
};