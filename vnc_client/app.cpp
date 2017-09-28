#include<app.h>

App::App(QWidget *parent) :QDialog(parent)
{
	timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, &App::handleTimeout);

	to_public_file_btn = new QPushButton;
	to_public_file_btn->setText(QString("公共文件"));
	to_public_file_btn->setStyleSheet("height:30px;width:50px");

	to_person_file_btn = new QPushButton;
	to_person_file_btn->setText(QString("个人文件"));
	to_person_file_btn->setStyleSheet("height:30px;width:50px");

	to_change_info_btn = new QPushButton;
	to_change_info_btn->setText(QString("修改信息"));
	to_change_info_btn->setStyleSheet("height:30px;width:50px");

	to_run_stop_btn = new QPushButton;
	to_run_stop_btn->setText(QString("开始共享屏幕"));
	to_run_stop_btn->setStyleSheet("height:30px;width:100px");
	to_run_stop_btn->setDisabled(true);

	online_table = new QTableWidget(0,1);
	online_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	online_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
	online_table->setSelectionBehavior(QAbstractItemView::SelectItems);
	online_table->horizontalHeader()->setVisible(false);

	allow_any_btn =new QRadioButton(this);
	allow_any_btn->setText(QString("允许任何人查看"));
	allow_any_btn->setChecked(false);

	QStringList header;
	header << "帐号" << "操作";
	online_table->setHorizontalHeaderLabels(header);

	noti_text = new QTextEdit(this);
	noti_text->setStyleSheet("color:red;");
	noti_text->setAlignment(Qt::AlignLeft);
	noti_text->setDisabled(true);
	noti_text->setFixedHeight(100);
	QGridLayout *layout = new QGridLayout(this);

	layout->addWidget(to_public_file_btn, 0, 2, 1, 2);
	layout->addWidget(to_person_file_btn, 0, 5, 1, 2);
	layout->addWidget(to_change_info_btn, 0, 8, 1, 2);//8+2+2
	layout->addWidget(online_table,1,1,10,10);
	layout->addWidget(to_run_stop_btn, 12, 5, 1, 2);
	layout->addWidget(noti_text, 13, 1, 1, 10);
	layout->addWidget(allow_any_btn, 14, 5, 1, 2);

	//layout->setColumnStretch(0, 1);
//	layout->setColumnStretch(12, 1);
	// 设置水平间距
	layout->setHorizontalSpacing(10);
	// 设置垂直间距
	layout->setVerticalSpacing(10);
	// 设置外间距
	layout->setContentsMargins(10, 10, 10, 10);

	this->setLayout(layout);
	this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint);
	this->setMinimumWidth(500);
	this->setMinimumHeight(600);

	connect(to_public_file_btn, &QPushButton::clicked, this, &App::to_public_file);
	connect(to_person_file_btn, &QPushButton::clicked, this, &App::to_person_file);
	connect(to_change_info_btn, &QPushButton::clicked, this, &App::to_change_info);
	connect(to_run_stop_btn, &QPushButton::clicked, this, &App::to_run_stop);
}


void App::set_info(QString id, QString pw, QString vnc_url)
{
	this->id = id;
	QString url("");
	url = vnc_url.remove("ws://");
	url = url.left(url.indexOf(":"));
	url.prepend("http://");

	this->to_change_info_url= QString("/file_manager/changepw.html?id=").append(id).append("&pw=").append(pw);
	this->to_person_fie_url= QString("/file_manager/file_person.html?id=").append(id).append("&pw=").append(pw).append("&to_see_id=").append(id);
	this->to_public_file_url = QString("/file_manager/file_public.html?id=").append(id).append("&pw=").append(pw);
	this->vnc_url= QString("/viewer/view.html?id=").append(id).append("&pw=").append(pw);

	this->to_change_info_url.prepend(url);
	this->to_person_fie_url.prepend(url);
	this->to_public_file_url.prepend(url);
	this->vnc_url.prepend(url);

	this->setWindowTitle(id + " 的桌面");
}


void App::to_public_file()
{
	QDesktopServices::openUrl(to_public_file_url);

}


void App::to_person_file()
{
	QDesktopServices::openUrl(to_person_fie_url);
}


void App::to_change_info()
{
	QDesktopServices::openUrl(to_change_info_url);
}


void App::to_run_stop()
{
	if (this->is_run == true){
		this->is_run = false;
		this->to_run_stop_btn->setText("开始共享屏幕");
		noti_text->append("已经停止共享屏幕");
	}
	else {
		this->is_run = true;
		this->to_run_stop_btn->setText("停止共享屏幕");
		noti_text->append("已经开始共享屏幕");
	}
	emit(run_stop(this->is_run));
	
}


void App::on_vnc_app(QString msg)
{
	if (get_fun(msg) == "connect") {
		if (get_content(msg) == "pass") {
			noti_text->append("已连接上服务器");
		}
		else {
			noti_text->append("连接服务器失败");
			to_run_stop_btn->setDisabled(true);
		}
		return;
	}

	if (get_fun(msg) == "login") {
		if (get_content(msg) == "pass") {
			to_run_stop_btn->setEnabled(true);
			noti_text->append("登录成功");
		}
		else {
			noti_text->setText("登录失败，请检查帐号密码");
		}
		return;
	}
}



void App::add_member(QString id)
{
	online_table->setRowCount(online_table->rowCount() + 1);
	online_table->setCellWidget(online_table->rowCount() - 1, 0, new Member(id,vnc_url, 0));
	online_table->setRowHeight(online_table->rowCount() - 1, 50);
	QObject::connect((Member *)online_table->cellWidget(online_table->rowCount() - 1, 0), &Member::send_msg, this, &App::on_member);
	noti_text->append(id+(" 已上线"));
}

void App::delete_member(QString id, int i)
{
	online_table->removeRow(i);
	noti_text->append(id+(" 已下线"));
}


void  App::on_msg_client(QString msg)
{
	if (get_fun(msg) == "signal") {
		msg = get_content(msg);
		QString temp_id = get_fun(msg);
		int index = online_list.indexOf(temp_id);
		if (index != -1) {
			Member *menber = (Member *)online_table->cellWidget(index, 0);
			QString content= get_content(msg);

			if (content == "ask_view") {
				noti_text->append(temp_id+(" 请求查看你的桌面"));

				if (allow_any_btn->isChecked()) {
					emit(to_msg_client("signal;" + temp_id + ";pass_view"));
					noti_text->append(" 已自动同意 " + temp_id + " 的查看桌面请求");
					try {
						menber->is_push_view = true;
						menber->push_view_btn->setText(QString("关闭查看"));
					}
					catch (exception& e) {

					}
				}
				else {
					QMessageBox box(QMessageBox::Question, "请求查看", temp_id + (" 请求查看你的桌面"));
					box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
					box.setButtonText(QMessageBox::Yes, QString("确 定"));
					box.setButtonText(QMessageBox::No, QString("取 消"));
					int nRet = box.exec();
					if (QMessageBox::Yes == nRet) {
						emit(to_msg_client("signal;" + temp_id + ";pass_view"));
						noti_text->append(" 已同意 " + temp_id + " 的查看桌面请求");
						try {
							menber->is_push_view = true;
							menber->push_view_btn->setText(QString("关闭查看"));
						}
						catch (exception& e) {

						}
					}

					if (QMessageBox::No == nRet) {
						emit(to_msg_client("signal;" + temp_id + ";deny_view"));
						noti_text->append(" 已拒绝 " + temp_id + " 的查看桌面请求");
					}
				}
				return;
			}

			if (content == "ask_control") {
				noti_text->append(temp_id+(" 请求控制你的桌面"));

				QMessageBox box(QMessageBox::Question, "请求控制", temp_id+(" 请求控制你的桌面"));
				box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
				box.setButtonText(QMessageBox::Yes, QString("确 定"));
				box.setButtonText(QMessageBox::No, QString("取 消"));
				int nRet = box.exec();
				if (QMessageBox::Yes == nRet) {
					emit(to_msg_client("signal;" + temp_id + ";pass_control"));
					noti_text->append(" 已同意 " + temp_id + " 的控制桌面请求");
					try {
						menber->is_push_view = true;
						menber->push_view_btn->setText(QString("关闭查看"));
						menber->is_push_control = true;
						menber->push_control_btn->setText(QString("关闭控制"));
					}
					catch (exception& e) {

					}
				}

				if (QMessageBox::No == nRet) {
					emit(to_msg_client("signal;" + temp_id + ";deny_control"));
					noti_text->append(" 已拒绝 " + temp_id + " 的控制桌面请求");
				}
				return;
			}

			if (content == "push_view") {
				try {
					menber->recv_msg(content);
				}
				catch(exception& e){

				}
				noti_text->append(temp_id+(" 已向你推送桌面查看"));

				QMessageBox box(QMessageBox::Information, "推送桌面查看", temp_id+(" 已向你推送桌面查看，打开对方桌面?"));
				box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
				box.setButtonText(QMessageBox::Yes, QString("确 定"));
				box.setButtonText(QMessageBox::No, QString("取 消"));
				int nRet = box.exec();
				if (QMessageBox::Yes == nRet) {
					QDesktopServices::openUrl(vnc_url + "&to_see_id=" + temp_id + "&way=view");
				}
				return;
			}

			if (content == "push_control") {
				try {
					menber->recv_msg(content);
				}
				catch (exception& e) {

				}
				noti_text->append(temp_id+(" 已向你推送桌面控制"));

				QMessageBox box(QMessageBox::Information, "推送桌面控制", temp_id+(" 已向你推送桌面控制，控制对方桌面?"));
				box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
				box.setButtonText(QMessageBox::Yes, QString("确 定"));
				box.setButtonText(QMessageBox::No, QString("取 消"));
				int nRet = box.exec();
				if (QMessageBox::Yes == nRet) {
					QDesktopServices::openUrl(vnc_url + "&to_see_id=" + temp_id + "&way=control");
				}
				return;
			}

			if (content == "pass_view") {
				try {
					menber->recv_msg(content);
				}
				catch (exception& e) {

				}
				noti_text->append(temp_id+(" 已同意你的查看桌面请求"));

				QMessageBox box(QMessageBox::Information, "同意查看", temp_id+(" 已同意你的查看桌面请求，打开对方桌面?"));
				box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
				box.setButtonText(QMessageBox::Yes, QString("确 定"));
				box.setButtonText(QMessageBox::No, QString("取 消"));
				int nRet = box.exec();
				if (QMessageBox::Yes == nRet) {
					QDesktopServices::openUrl(vnc_url + "&to_see_id=" + temp_id + "&way=view");
				}
				return;
			}

			if (content == "pass_control") {
				try {
					menber->recv_msg(content);
				}
				catch (exception& e) {

				}
				noti_text->append(temp_id+(" 已同意你的控制桌面请求"));

				QMessageBox box(QMessageBox::Information, "同意控制", temp_id+(" 已同意你的推送桌面控制，控制对方桌面?"));
				box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
				box.setButtonText(QMessageBox::Yes, QString("确 定"));
				box.setButtonText(QMessageBox::No, QString("取 消"));
				int nRet = box.exec();
				if (QMessageBox::Yes == nRet) {
					QDesktopServices::openUrl(vnc_url + "&to_see_id=" + temp_id + "&way=control");
				}
				return;
			}

			if (content == "deny_view") {
				noti_text->append(temp_id+(" 已拒绝你的查看桌面请求"));

				QMessageBox box(QMessageBox::Information, "拒绝查看", temp_id+(" 已拒绝你的查看桌面请求，重新发送请求?"));
				box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
				box.setButtonText(QMessageBox::Yes, QString("确 定"));
				box.setButtonText(QMessageBox::No, QString("取 消"));
				int nRet = box.exec();
				if (QMessageBox::Yes == nRet) {
					emit(to_msg_client("signal;" + temp_id + ";ask_view"));
					noti_text->append(" 重新向 " + temp_id + " 发送查看桌面请求");
				}
			}

			if (content == "deny_control") {
				noti_text->append(temp_id+(" 已拒绝你的控制桌面请求"));

				QMessageBox box(QMessageBox::Information, "拒绝控制", temp_id+(" 已拒绝你的推送桌面控制，重新发送请求?"));
				box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
				box.setButtonText(QMessageBox::Yes, QString("确 定"));
				box.setButtonText(QMessageBox::No, QString("取 消"));
				int nRet = box.exec();
				if (QMessageBox::Yes == nRet) {
					emit(to_msg_client("signal;" + temp_id + ";ask_control"));
					noti_text->append(" 重新向 " + temp_id + " 发送控制桌面请求");
				}
				return;
			}

			if (content == "close_view") {
				try {
					menber->recv_msg(content);
				}
				catch (exception& e) {

				}
				noti_text->append(temp_id+(" 已关闭你的桌面查看"));

				QMessageBox box(QMessageBox::Information, "关闭查看", temp_id+(" 已关闭你的桌面查看，重新发送请求?"));
				box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
				box.setButtonText(QMessageBox::Yes, QString("确 定"));
				box.setButtonText(QMessageBox::No, QString("取 消"));
				int nRet = box.exec();
				if (QMessageBox::Yes == nRet) {
					emit(to_msg_client("signal;" + temp_id + ";ask_view"));
				}
				return;
			}

			if (content == "close_control") {
				try {
					menber->recv_msg(content);
				}
				catch (exception& e) {

				}
				noti_text->append(temp_id+(" 已关闭你的桌面控制"));

				QMessageBox box(QMessageBox::Information, "关闭控制", temp_id+(" 已关闭你的桌面控制，重新发送请求?"));
				box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
				box.setButtonText(QMessageBox::Yes, QString("确 定"));
				box.setButtonText(QMessageBox::No, QString("取 消"));
				int nRet = box.exec();
				if (QMessageBox::Yes == nRet) {
					emit(to_msg_client("signal;" + temp_id + ";ask_control"));
				}
				return;
			}

		}
		return;
	}

	if (get_fun(msg) == "newer") {
		QString temp_id = get_content(msg);
		if (online_list.indexOf(temp_id) == -1 && temp_id != id) {
			online_list.append(temp_id);
			add_member(temp_id);
		}
		return;
	}

	if (get_fun(msg) == "outer") {
		QString temp_id = get_content(msg);
		int index = online_list.indexOf(temp_id);
		if (index >=0 && temp_id != id) {
			delete_member(temp_id, index);
			online_list.remove(index);
		}
		return;
	}

	if (get_fun(msg) == "list") {
		QString content = get_content(msg);
		//去除不在线的
		for (int i = 0; i < online_list.length(); i++)
		{
			if (content.indexOf(online_list[i]) == -1) {
				delete_member(online_list[i], i);
				online_list.remove(i);
			}
		}

		//添加新在线的
		int index;
		QString temp_id;
		while (!content.isEmpty())
		{
			index = content.indexOf(';');
			temp_id = content.left(index);

			if (online_list.indexOf(temp_id) == -1&& temp_id !=id){
				online_list.append(temp_id);
				add_member(temp_id);
			}
			content = content.remove(0, index + 1);
		}
		return;
	}
}

void App::on_member(QString msg)
{
	emit(to_msg_client(msg));
	if (get_fun(msg) == "signal") {
		msg = get_content(msg);
		QString temp_id = get_fun(msg);
		int index = online_list.indexOf(temp_id);
		QString content = get_content(msg);
		if (content == "ask_view") {
			noti_text->append("向 " + temp_id + " 发送查看桌面请求");
			return;
		}

		if (content == "ask_control") {
			noti_text->append("向 " + temp_id + " 发送控制桌面请求");
		}

		if (content == "push_view") {
			noti_text->append("向 " + temp_id + " 推送桌面查看");
			return;
		}

		if (content == "push_control") {
			noti_text->append("向 " + temp_id + " 推送桌面控制");
			return;
		}

		if (content == "close_view") {
			noti_text->append("关闭 " + temp_id + " 的桌面查看");
			return;
		}

		if (content == "close_control") {
			noti_text->append("关闭 " + temp_id + " 的桌面控制");
			return;
		}
	}
}


void App::handleTimeout()
{
	if (count == 0 && timer->isActive()) {
		timer->stop();
		timer->start(500);
		emit(to_msg_client("getlist;"));
		count++;
	}

	if (count == 1 && timer->isActive()) {
		timer->stop();
		timer->start(4000);
		emit(to_msg_client("getlist;"));
		count++;
	}

	if (count ==2 && timer->isActive()) {
		timer->stop();
		timer->start(5000);
		emit(to_msg_client("getlist;"));
		count++;
	}

	if (count == 3 && timer->isActive()) {
		timer->stop();
		timer->start(6000);
		emit(to_msg_client("getlist;"));
		count++;
	}

	if (count == 4 && timer->isActive()) {
		timer->stop();
		timer->start(7000);
		emit(to_msg_client("getlist;"));
		count++;
	}
}