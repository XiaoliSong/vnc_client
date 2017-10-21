#pragma once

#include"head.h"


extern QString log_file_name;
void log_msg(QtMsgType type, const QMessageLogContext &context, const QString &msg);
