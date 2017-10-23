#include "head.h"
#include "vnc_app.h"
#include "login_dialog.h"
#include "msg_client.h"
#include "app.h"
#include "log.h"
QString log_file_name;
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QDir dir;
	if (!dir.exists("./log")) {
		if (!dir.mkdir("./log")) {
			QMessageBox box(QMessageBox::Warning, "失败", "无法找到日志文件夹，请尝试在程序目录建个log空文件夹！");
			box.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
			box.setButtonText(QMessageBox::Ok, QString("确 定"));
			box.setButtonText(QMessageBox::Cancel, QString("取 消"));
			box.exec();
			exit(0);
		}
	}

	QFile qssFile("style.qss");//资源文件":/css.qss"
	qssFile.open(QFile::ReadOnly);
	if (qssFile.isOpen())
	{
		QString css = QLatin1String(qssFile.readAll());
		app.setStyleSheet(css);
		qssFile.close();
	}

	log_file_name = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss-ddd").append(".txt").prepend("./log/");
	
	qInstallMessageHandler(log_msg);
	
	qInfo("program start");

	Login_dialog login_dialog(0);
	login_dialog.read_config();
	Msg_client msg_client(0);
	login_dialog.set_msg_client(&msg_client);
	QObject::connect(&login_dialog, &Login_dialog::to_connect, &msg_client, &Msg_client::on_to_connect);

	QObject::connect(&login_dialog, &Login_dialog::to_login, &msg_client, &Msg_client::on_to_login);

	QObject::connect(&msg_client,&Msg_client::to_login_dialog, &login_dialog, &Login_dialog::on_msg_client);

	login_dialog.connect_to_server();
	login_dialog.show();
	QObject::connect(&login_dialog, &Login_dialog::close, &app, &QCoreApplication::quit);
	
	return app.exec();
}
