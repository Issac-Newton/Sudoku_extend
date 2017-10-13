#pragma once
#include <QTextEdit>

class MyTextEdit :public QTextEdit
{
	Q_OBJECT
	
public:
	MyTextEdit(QWidget* parent = 0);
	~MyTextEdit();

protected:
	virtual void focusInEvent(QFocusEvent *e);
	virtual void focusOutEvent(QFocusEvent *e);
	
};