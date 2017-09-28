#pragma once
#include "head.h"

class Member : public QDialog
{
	Q_OBJECT
public:
	bool is_view = false;
	bool is_control = false;
	bool is_push_view = false;
	bool is_push_control = false;
	QString id;
	QString vnc_url;
	QLabel *id_label;
	QPushButton *view_btn;
	QPushButton *control_btn;
	QPushButton *push_view_btn;
	QPushButton *push_control_btn;
	Member(QString id, QString vnc_url, QWidget *parent = 0);
	~Member() {};
	void recv_msg(QString msg);
signals:
	void send_msg(QString msg);
private:
	void view();
	void control();
	void push_view();
	void push_control();
};