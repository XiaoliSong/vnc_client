#pragma once

#include "head.h"
#include "grabber.h"
#include "encoder.h"
#include "timer.h"
#include <QUrl>

#include <QDesktopServices>
QT_BEGIN_NAMESPACE

#define APP_FRAME_BUFFER_SIZE (1024*1024)

class Vnc_app : public QObject
{
	Q_OBJECT
public:
	explicit Vnc_app(QWidget *parent = 0);
	void connect_login(QString id,QString pw, QString vnc_ws_url);
	QString id;
	QString pw;
	QWebSocket vnc_webSocket;
	bool is_run = false;
	encoder_t *encoder;
	grabber_t *grabber;
	int target_fps;
	int bit_rate=0;
	int out_width;
	int out_height;
	HWND window= GetDesktopWindow();
	grabber_crop_area_t crop;
	float mouse_speed;
signals:
	void to_app(QString msg);
public slots:
	void onRunStop(bool is_run);
private slots:
	void onClosed();
	void onConnected();
	void onTextMessageReceived(QString message);
	void onBinaryMessageReceived(QByteArray message);
};