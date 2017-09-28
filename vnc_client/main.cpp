#include "vnc_app.h"
#include "login_dialog.h"
#include "msg_client.h"
#include "app.h"
#include <QApplication>
#include "head.h"
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	Login_dialog login_dialog(0);
	login_dialog.init();
	Msg_client msg_client(0);
	login_dialog.set_msg_client(&msg_client);
	QObject::connect(&login_dialog, &Login_dialog::to_connect, &msg_client, &Msg_client::on_to_connect);

	QObject::connect(&login_dialog, &Login_dialog::to_login, &msg_client, &Msg_client::on_to_login);

	QObject::connect(&msg_client,&Msg_client::to_login_dialog, &login_dialog, &Login_dialog::on_msg_client);

	login_dialog.connect_to_server();
	login_dialog.show();
	QObject::connect(&login_dialog, &Login_dialog::close, &app, &QCoreApplication::quit);
	
	return app.exec();
	
	//QDesktopServices::openUrl(QString(QStringLiteral("http://10.8.187.174/file_login.html")));
}
