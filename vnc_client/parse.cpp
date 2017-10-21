#include "parse.h"

QString get_fun(QString msg)
{
	QString fun("");
	int index = msg.indexOf(';');
	fun = msg.left(index);
	return fun;
}

QString get_content(QString msg)
{
	QString content("");
	int index = msg.indexOf(';');
	content = msg.right(msg.length() - index - 1);
	return content;
}

QString get_color_string(QString str, QString color)
{
	return QString("<font color = " + color + ">" + str + "</font>");
}