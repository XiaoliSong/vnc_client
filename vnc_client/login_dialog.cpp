#include"login_dialog.h"

Login_dialog::Login_dialog(QWidget *parent) :QDialog(parent)
{
	id_edit = new QLineEdit(this);
	id_edit->setPlaceholderText(QString("账号"));
	id_edit->setStyleSheet("max-width:200px;height:30px;");

	pw_edit = new QLineEdit(this);
	pw_edit->setEchoMode(QLineEdit::Password);
	pw_edit->setPlaceholderText(QString("密码"));
	pw_edit->setStyleSheet("max-width:200px;height:30px;");

	login_btn = new QPushButton(this);
	login_btn->setObjectName(QStringLiteral("login_btn"));
	login_btn->setText(QString("登录"));
	login_btn->setStyleSheet("max-width:100px;height:30px;");
	login_btn->setDisabled(true);

	remmber_btn = new QRadioButton(this);
	remmber_btn->setText(QString("记住密码"));

	noti_label = new QLabel(this);
	noti_label->setText(QString("未连接服务器"));
	noti_label->setStyleSheet("color:red;");

	QGridLayout *layout = new QGridLayout(this);
	layout->setSpacing(30);
	layout->setAlignment(Qt::AlignCenter);
	layout->addWidget(id_edit, 0, 0, 1, 4);
	layout->addWidget(pw_edit, 1, 0, 1, 4);
	layout->addWidget(login_btn, 3, 1, 1, 2);
	layout->addWidget(remmber_btn, 4, 1, 1, 2);
	layout->addWidget(noti_label, 5, 1, 1, 2);

	this->setLayout(layout);
	this->setMinimumSize(400, 280);
	this->setWindowTitle(QString("登录"));
	this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint);

	connect(login_btn, &QPushButton::clicked, this, &Login_dialog::login);
}

bool is_ip_address(QString ip)
{
	QRegExp rx2("(//d+)(//.)(//d+)(//.)(//d+)(//.)(//d +)");

	int pos = rx2.indexIn(ip);

	if (pos>-1)
	{
		for (int i = 0; i<4; i++)
		{
			if (rx2.cap(i * 2 + 1).toInt() >= 255)
			{
				return false;
			}
		}

		if (rx2.cap(7).toInt() == 0)
		{
			return false;
		}

		if (rx2.cap(7).toInt() == 0)
		{

			return false;
		}
	}
	else{
		return false;
	}

	return true;
}

void Login_dialog::init()
{
	ifstream file;
	file.open("config.ini", ios::in);

	if (!file.is_open()) {
		QMessageBox box(QMessageBox::Warning, "失败", "读取配置文件失败！");
		box.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
		box.setButtonText(QMessageBox::Ok, QString("确 定"));
		box.setButtonText(QMessageBox::Cancel, QString("取 消"));
		box.exec();
		return;
	}
	int count = 0;
	std::string strLine;
	while (getline(file, strLine))
	{
		
		if (!strLine.empty()) {
			if (count == 0) {
				url = QString(strLine.data());
				url = url.remove("url=");
			}
			if (count == 1) {
				msg_url = QString(strLine.data());
				msg_url = msg_url.remove("msg_port=");
				msg_port = msg_url;
				msg_url = msg_url.prepend(":");
				msg_url = msg_url.prepend(url);
				msg_url = msg_url.prepend("ws://");
			}
			if (count == 2) {
				vnc_url = QString(strLine.data());
				vnc_url = vnc_url.remove("vnc_port=");
				vnc_port = vnc_url;
				vnc_url = vnc_url.prepend(":");
				vnc_url = vnc_url.prepend(url);
				vnc_url = vnc_url.prepend("ws://");
			}
			if (count == 3) {
				id = QString(strLine.data());
				id = id.remove("id=");
				id_edit->setText(id);
			}
			if (count == 4) {
				pw = QString(strLine.data());
				pw = pw.remove("pw=");
				pw_edit->setText(pw);
				if (pw == "") {
					remmber_btn->setChecked(false);
				}
				else {
					remmber_btn->setChecked(true);
				}
			}
		}
		count++;
	}
	file.close();
}

void Login_dialog::write_config()
{
	ofstream file;
	file.open("config.ini", ios::out);
	if (!file.is_open()) {
		QMessageBox box(QMessageBox::Warning, "失败", "保存配置文件失败！");
		box.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
		box.setButtonText(QMessageBox::Ok, QString("确 定"));
		box.setButtonText(QMessageBox::Cancel, QString("取 消"));
		box.exec();

		exit(0);
	}
	file << "url=" << url.toStdString().c_str() << endl;
	file << "msg_port=" << msg_port.toStdString().c_str() << endl;
	file << "vnc_port=" << vnc_port.toStdString().c_str() << endl;
	file << "id=" << id_edit->text().toStdString().c_str() << endl;
	if (remmber_btn->isChecked()) {
		file << "pw=" << pw.toStdString().c_str() << endl;
	}
	else {
		file << "pw=" << endl;
	}
	file.close();
}

void Login_dialog::login()
{
	if (pw != pw_edit->text()) {
		QByteArray hash = QCryptographicHash::hash(pw_edit->text().toLatin1(),QCryptographicHash::Sha1);
		pw = hash.toHex();
	}

	if (id != id_edit->text()) {
		id = id_edit->text();
	}

	if (id.isEmpty() || pw.isEmpty()) {
		QMessageBox::information(this, QString("输入错误"), QString("账号和密码不能为空！"), QMessageBox::NoButton);
	}

	write_config();
	emit(to_login(id, pw));
}


void Login_dialog::on_msg_client(QString msg)
{
	if (get_fun(msg) == "connect") {
		if (get_content(msg) == "pass") {
			login_btn->setEnabled(true);
			noti_label->setText("已连接上服务器");
		}
		else {
			noti_label->setText("连接服务器失败");
		}
		return;
	}

	if (get_fun(msg) == "login") {
		if (get_content(msg) == "pass") {
			noti_label->setText("登录成功");
			accept();
			App app(0);
			app.set_info(id, pw, vnc_url);

			Vnc_app vnc_app(0);
			vnc_app.connect_login(id, pw, vnc_url);

			QObject::connect(&app, &App::run_stop, &vnc_app, &Vnc_app::onRunStop);
			QObject::connect(&vnc_app, &Vnc_app::to_app, &app, &App::on_vnc_app);
			QObject::connect(p_msg_client, &Msg_client::to_app, &app, &App::on_msg_client);
			QObject::connect(&app, &App::to_msg_client, p_msg_client, &Msg_client::send_msg);
			
			app.timer->start(500);
			app.exec();
		}
		if (get_content(msg) == "error") {
			noti_label->setText("登录失败，请检查帐号密码");
			
			QMessageBox box(QMessageBox::Warning, "失败", "登录失败，请检查帐号密码！");
			box.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
			box.setButtonText(QMessageBox::Ok, QString("确 定"));
			box.setButtonText(QMessageBox::Cancel, QString("取 消"));
			box.exec();
			
		}

		if (get_content(msg) == "again") {
			noti_label->setText("登录失败，已经在其他地方登录");
			QMessageBox box(QMessageBox::Warning, "失败", "登录失败，已经在其他地方登录！");
			box.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
			box.setButtonText(QMessageBox::Ok, QString("确 定"));
			box.setButtonText(QMessageBox::Cancel, QString("取 消"));
			box.exec();

		}
		return;
	}
}
