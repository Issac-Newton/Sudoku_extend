#include "MyTextEdit.h"
#include <QTextEdit.h>
#include "func.h"

MyTextEdit::MyTextEdit(QWidget* parent) : QTextEdit(parent)
{

}

MyTextEdit::~MyTextEdit()
{

}

void MyTextEdit::focusInEvent(QFocusEvent *e)
{
	if (!isReadOnly())
	{
		setStyleSheet(QString::fromUtf8("font: 20pt \"\351\273\221\344\275\223\";""border: 3px solid red"));
	}
	emit cursorPositionChanged();
}

void MyTextEdit::focusOutEvent(QFocusEvent *e)
{
	QString str;
	str = toPlainText();
	int position = textCursor().position();
	int length = str.count();
	if (!isReadOnly())
	{
		setStyleSheet(QString::fromUtf8("font: 21pt \"\351\273\221\344\275\223\";""border: 1px solid grey;color:blue"));
		if (!IsValidChar(str))
		{
			setPlainText("");
			setCursorWidth(0);
		}
		else
		{
			//setStyleSheet("color:blue");
			setAlignment(Qt::AlignCenter);
		}
	}

}