#include "member.h"

Member::Member(QString id, QString vnc_url, QWidget *parent):QDialog(parent)
{
	this->id = id;
	this->vnc_url = vnc_url;
	id_label= new QLabel(this);
	id_label->setText(id);
	id_label->setStyleSheet("color:red;");

	view_btn = new QPushButton(this);
	view_btn->setText(QString("申请查看"));
	view_btn->setStyleSheet("max-width:100px;height:30px;");

	control_btn = new QPushButton(this);
	control_btn->setText(QString("申请控制"));
	control_btn->setStyleSheet("max-width:100px;height:30px;");


	push_view_btn = new QPushButton(this);
	push_view_btn->setText(QString("推送查看"));
	push_view_btn->setStyleSheet("max-width:100px;height:30px;");

	push_control_btn = new QPushButton(this);
	push_control_btn->setText(QString("推送控制"));
	push_control_btn->setStyleSheet("max-width:100px;height:30px;");

	QGridLayout *layout = new QGridLayout(this);
	layout->addWidget(id_label, 0, 0, 1, 1);
	layout->addWidget(view_btn, 0, 1, 1, 1);
	layout->addWidget(control_btn, 0, 2, 1, 1);
	layout->addWidget(push_view_btn, 0, 3, 1, 1);
	layout->addWidget(push_control_btn, 0, 4, 1, 1);
	//水平间距
	layout->setHorizontalSpacing(10);
	this->setLayout(layout);
	
	connect(view_btn, &QPushButton::clicked, this, &Member::view);
	connect(control_btn, &QPushButton::clicked, this, &Member::control);
	connect(push_view_btn, &QPushButton::clicked, this, &Member::push_view);
	connect(push_control_btn, &QPushButton::clicked, this, &Member::push_control);
}


void Member::view()
{
	if (this->is_view == false) {
		emit(send_msg("signal;" + id + ";ask_view"));
		QMessageBox::information(this, QString("申请查看"), QString("已经发送查看请求！"), QMessageBox::NoButton);
	}
	else {
		QDesktopServices::openUrl(vnc_url+"&to_see_id="+id+"&way=view");
	}
}


void Member::control()
{
	if (this->is_control == false) {
		emit(send_msg("signal;" + id + ";ask_control"));
		QMessageBox::information(this, QString("申请控制"), QString("已经发送控制请求！"), QMessageBox::NoButton);
	}
	else {
		QDesktopServices::openUrl(vnc_url + "&to_see_id=" + id + "&way=control");
	}
}


void Member::push_view()
{
	if (this->is_push_view == true) {
		emit(send_msg("signal;" + id + ";close_view"));
		if (this->is_push_control == true) {
			this->is_push_control = false;
			emit(send_msg("signal;" + id + ";close_control"));
			push_control_btn->setText(QString("推送控制"));
		}
		push_view_btn->setText(QString("推送查看"));
	}
	else {
		emit(send_msg("signal;" + id + ";push_view"));
		push_view_btn->setText(QString("关闭查看"));
	}
	this->is_push_view = !this->is_push_view;
}


void Member::push_control()
{
	if (this->is_push_control == true) {
		emit(send_msg("signal;" + id + ";close_control"));
		push_control_btn->setText(QString("推送控制"));
	}
	else {
		emit(send_msg("signal;" + id + ";push_control"));
		push_control_btn->setText(QString("关闭控制"));
		push_view_btn->setText(QString("关闭查看"));
		this->is_push_view = true;
	}
	this->is_push_control = !this->is_push_control;
}


void Member::recv_msg(QString msg)
{
	if (msg == "pass_view"|| msg == "push_view") {
		this->is_view = true;
		view_btn->setText(QString("查看"));
		return;
	}

	if (msg == "pass_control"|| msg == "push_control") {
		this->is_control = true;
		this->is_view = true;
		view_btn->setText(QString("查看"));
		control_btn->setText(QString("控制"));
		return;
	}

	if (msg == "close_view") {
		this->is_view = false;
		view_btn->setText(QString("申请查看"));
		this->is_control = false;
		control_btn->setText(QString("申请控制"));
		return;
	}

	if (msg == "close_control") {
		this->is_control = false;
		control_btn->setText(QString("申请控制"));
		return;
	}
}