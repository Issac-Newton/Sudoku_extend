/********************************************************************************
** Form generated from reading UI file 'GUITest.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUITEST_H
#define UI_GUITEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QPixmap>
#include <QLabel>
#include "MyTextEdit.h"
#include "stdafx.h"

QT_BEGIN_NAMESPACE

class Ui_GUITestClass
{
public:
	MyTextEdit* focusIn;
	QAction *actionEasy;
	QAction *actionNormal;
	QAction *actionHard;
	QAction *actionEasy_2;
	QAction *actionNormal_2;
	QAction *actionHard_2;
	//QAction *actionHelp;

	QLabel *label;
	QWidget *centralWidget;
	QWidget *gridLayoutWidget;
	QGridLayout *gridLayout;
	QWidget *verticalLayoutWidget;
	QVBoxLayout *verticalLayout;
	QLCDNumber *Timer;
	QHBoxLayout *horizontalLayout;
	QSpacerItem *horizontalSpacer;
	QPushButton *Start;
	QSpacerItem *horizontalSpacer_3;
	QSpacerItem *horizontalSpacer_2;
	QPushButton *pushButton_3;
	QPushButton *pushButton_4;
	QPushButton *pushButton_5;
	QPushButton *pushButton_help;

	QMenu *menu;
	QMenu *menu_2;
	//QMenu *menu_help;
	QFrame *gridFrame;

	MyTextEdit* textEdit[9][9];
	QFrame* line[40];

	QMenuBar *menuBar;
	QToolBar *mainToolBar;
	QStatusBar *statusBar;

	void setupUi(QMainWindow *GUITestClass)
	{
		if (GUITestClass->objectName().isEmpty())
		{
			GUITestClass->setObjectName(QStringLiteral("Sudoku Game"));
		}
		//这里有一个大小（整个窗口）
		//GUITestClass->resize(667, 624);
		GUITestClass->resize(750, 710);
		GUITestClass->setMaximumSize(QSize(750, 710));
		GUITestClass->setAnimated(false);

		actionEasy = new QAction(GUITestClass);
		actionEasy->setObjectName(QStringLiteral("actionEasy"));
		actionNormal = new QAction(GUITestClass);
		actionNormal->setObjectName(QStringLiteral("actionNormal"));
		actionHard = new QAction(GUITestClass);
		actionHard->setObjectName(QStringLiteral("actionHard"));
		actionEasy_2 = new QAction(GUITestClass);
		actionEasy_2->setObjectName(QStringLiteral("actionEasy_2"));
		actionNormal_2 = new QAction(GUITestClass);
		actionNormal_2->setObjectName(QStringLiteral("actionNormal_2"));
		actionHard_2 = new QAction(GUITestClass);
		actionHard_2->setObjectName(QStringLiteral("actionHard_2"));

		centralWidget = new QWidget(GUITestClass);

		centralWidget->setObjectName(QStringLiteral("centralWidget"));
		gridFrame = new QFrame(centralWidget);
		gridFrame->setObjectName(QStringLiteral("gridFrame"));

		//这个是数独盘
		//gridFrame->setGeometry(QRect(9, 9, 445, 440));
		gridFrame->setGeometry(QRect(9, 9, 500, 500));
		gridFrame->setFrameShape(QFrame::Box);
		gridLayout = new QGridLayout(gridFrame);
		gridLayout->setSpacing(0);
		gridLayout->setContentsMargins(11, 11, 11, 11);
		gridLayout->setObjectName(QStringLiteral("gridLayout"));
		gridLayout->setSizeConstraint(QLayout::SetNoConstraint);

		int Line = 0;
		int line_pointer = 0;

		QPalette p = QPalette();
		p.setColor(QPalette::Base, Qt::white);

		for (int i = 0; i < 11; i++)
		{
			int line_temp;
			int col_temp;

			int Col = 0;

			if (i < 3)
			{
				line_temp = i;
			}
			else if (i == 3)
			{
				for (int k = 0; k < 11; k++)
				{
					line[line_pointer] = new QFrame(gridFrame);
					line[line_pointer]->setFrameShadow(QFrame::Plain);
					line[line_pointer]->setLineWidth(5);
					line[line_pointer]->setFrameShape(QFrame::HLine);
					gridLayout->addWidget(line[line_pointer], Line, Col, 1, 1);
					Col++;
					line_pointer++;
				}
				Line++;
				continue;
			}
			else if (i > 3 && i < 7)
			{
				line_temp = i - 1;
			}
			else if (i == 7)
			{
				for (int k = 0; k < 11; k++)
				{
					line[line_pointer] = new QFrame(gridFrame);
					line[line_pointer]->setFrameShadow(QFrame::Plain);
					line[line_pointer]->setLineWidth(5);
					line[line_pointer]->setFrameShape(QFrame::HLine);
					gridLayout->addWidget(line[line_pointer], Line, Col, 1, 1);
					Col++;
					line_pointer++;
				}
				Line++;
				continue;
			}
			else if (i > 7)
			{
				line_temp = i - 2;
			}

			for (int j = 0; j < 11; j++)
			{
				if (j == 3 || j == 7)
				{
					line[line_pointer] = new QFrame(gridFrame);
					line[line_pointer]->setFrameShadow(QFrame::Plain);
					line[line_pointer]->setLineWidth(5);
					line[line_pointer]->setFrameShape(QFrame::VLine);
					gridLayout->addWidget(line[line_pointer], Line, Col, 1, 1);
					Col++;
					line_pointer++;
					continue;
				}

				col_temp = col_translate(j);

				textEdit[line_temp][col_temp] = new MyTextEdit(gridFrame);   //调用构造函数
				textEdit[line_temp][col_temp]->setReadOnly(true);
				textEdit[line_temp][col_temp]->setAcceptRichText(false);
				textEdit[line_temp][col_temp]->setCursorWidth(1);
				textEdit[line_temp][col_temp]->setPalette(p);
				textEdit[line_temp][col_temp]->setStyleSheet(QString::fromUtf8("font: 21pt \"\351\273\221\344\275\223\";"));
				gridLayout->addWidget(textEdit[line_temp][col_temp], Line, Col, 1, 1);
				Col++;
			}
			Line++;
		}


		//layout
		verticalLayoutWidget = new QWidget(centralWidget);
		verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));

		//时钟的大小
		//verticalLayoutWidget->setGeometry(QRect(475, 50, 150, 120));      //这里修改的是时钟的位置
		verticalLayoutWidget->setGeometry(QRect(530, 50, 150, 120));      //这里修改的是时钟的位置
		verticalLayout = new QVBoxLayout(verticalLayoutWidget);
		verticalLayout->setSpacing(6);
		verticalLayout->setContentsMargins(11, 11, 11, 11);
		verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
		verticalLayout->setContentsMargins(0, 0, 0, 0);
		Timer = new QLCDNumber(verticalLayoutWidget);
		Timer->setObjectName(QStringLiteral("lcdNumber"));

		verticalLayout->addWidget(Timer);

		horizontalLayout = new QHBoxLayout();
		horizontalLayout->setSpacing(6);
		horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));

		//这里也有一个弹簧
		horizontalSpacer = new QSpacerItem(60, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

		horizontalLayout->addItem(horizontalSpacer);

		//按钮(位置可能受影响)
		Start = new QPushButton(verticalLayoutWidget);
		Start->setObjectName(QStringLiteral("pushButton"));
		//按钮的大小
		Start->setMinimumSize(QSize(60, 50));

		horizontalLayout->addWidget(Start);

		//这里下面是两个弹簧
		horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

		horizontalLayout->addItem(horizontalSpacer_3);

		horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

		horizontalLayout->addItem(horizontalSpacer_2);

		verticalLayout->addLayout(horizontalLayout);

		label = new QLabel(centralWidget);
		label->setObjectName(QStringLiteral("label"));
		//label->setGeometry(QRect(470, 210, 180, 300));
		label->setGeometry(QRect(525, 210, 200, 300));
		label->setStyleSheet(QLatin1String("font: 14pt \"Adobe Devanagari\";\n"
			"border-image:url(bw.png);"
			"font: 12pt \"Comic Sans MS\";\n"
			"color:rgb(0, 0, 0);"));
		//"color:rgb(24, 16, 255);"));

		//最下面的三个按钮
		pushButton_3 = new QPushButton(centralWidget);
		pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
		pushButton_3->setGeometry(QRect(370, 540, 120, 80));
		pushButton_4 = new QPushButton(centralWidget);
		pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
		pushButton_4->setGeometry(QRect(60, 540, 120, 80));
		pushButton_5 = new QPushButton(centralWidget);
		pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
		pushButton_5->setGeometry(QRect(215, 540, 120, 80));
		pushButton_help = new QPushButton(centralWidget);
		pushButton_help->setObjectName(QStringLiteral("pushButton_help"));
		pushButton_help->setGeometry(QRect(525, 540, 120, 80));

		GUITestClass->setCentralWidget(centralWidget);
		menuBar = new QMenuBar(GUITestClass);
		menuBar->setObjectName(QStringLiteral("menuBar"));
		menuBar->setGeometry(QRect(0, 0, 605, 23));
		menu = new QMenu(menuBar);
		menu->setObjectName(QStringLiteral("menu"));
		menu_2 = new QMenu(menuBar);
		menu_2->setObjectName(QStringLiteral("menu_2"));
		/*menu_help = new QMenu(menuBar);
		menu_help->setObjectName(QStringLiteral("menu_help"));*/
		GUITestClass->setMenuBar(menuBar);

		//GUITestClass->setMenuBar(menuBar);

		mainToolBar = new QToolBar(GUITestClass);
		mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
		GUITestClass->addToolBar(Qt::TopToolBarArea, mainToolBar);

		statusBar = new QStatusBar(GUITestClass);
		statusBar->setObjectName(QStringLiteral("statusBar"));
		GUITestClass->setStatusBar(statusBar);


		//这个是菜单栏
		menuBar->addAction(menu->menuAction());
		menuBar->addAction(menu_2->menuAction());
		//menuBar->addAction(menu_help->menuAction());
		menu->addAction(actionEasy);
		menu->addAction(actionNormal);
		menu->addAction(actionHard);
		menu_2->addAction(actionEasy_2);
		menu_2->addAction(actionNormal_2);
		menu_2->addAction(actionHard_2);
		//menu_help->addAction(actionHelp);
		retranslateUi(GUITestClass);

		QMetaObject::connectSlotsByName(GUITestClass);
	} // setupUi

	void retranslateUi(QMainWindow *GUITestClass)
	{
		GUITestClass->setWindowTitle(QApplication::translate("GUITestClass", "Sudoku Game", Q_NULLPTR));
		QPixmap pixmap = QPixmap("background.jpg").scaled(GUITestClass->size());
		QPalette palette(GUITestClass->palette());
		palette.setBrush(QPalette::Background, QBrush(pixmap));
		GUITestClass->setPalette(palette);


		QString button_style = "QPushButton{font-family:Comic Sans MS;font-size:16pt;background-image:url(button1.jpg); color:white; border-radius:10px;border-style: outset;}"
			"QPushButton:pressed{background-image:url(pressed1.jpg);border-style:inset;}";
		pushButton_3->setStyleSheet(button_style);
		pushButton_4->setStyleSheet(button_style);
		pushButton_5->setStyleSheet(button_style);
		pushButton_help->setStyleSheet(button_style);
		/*pushButton_3->setStyleSheet("QPushButton{background-image:url(button1.jpg); color:white; border-radius:10px;border-style: outset;}"
		"QPushButton:pressed{background-image:url(pressed1.jpg);border-style:inset;}");*/

		//添加label的字体
		label->setText(QApplication::translate("GUITestClass", "            Notice\n"
			"     Step 1.\n"
			"      Choose Mode\n"
			"     Step 2.\n"
			"      Finish Puzzle\n"
			"     Step 3.\n"
			"      Check", Q_NULLPTR));

		//添加子菜单
		actionEasy->setText(QApplication::translate("GUITestClass", "Easy", Q_NULLPTR));
		actionNormal->setText(QApplication::translate("GUITestClass", "Normal", Q_NULLPTR));
		actionHard->setText(QApplication::translate("GUITestClass", "Hard", Q_NULLPTR));
		actionEasy_2->setText(QApplication::translate("GUITestClass", "Easy", Q_NULLPTR));
		actionNormal_2->setText(QApplication::translate("GUITestClass", "Normal", Q_NULLPTR));
		actionHard_2->setText(QApplication::translate("GUITestClass", "Hard", Q_NULLPTR));
		//actionHelp->setText(QApplication::translate("GUITestClass", "Rules", Q_NULLPTR));
		Start->setText(QString());
		pushButton_3->setText(QApplication::translate("GUITestClass", "Hint", Q_NULLPTR));
		//		pushButton_3->setStyleSheet("QPushButton{font-family:Gabriola;font-size:36pt}");
		pushButton_4->setText(QApplication::translate("GUITestClass", "Restart", Q_NULLPTR));
		pushButton_5->setText(QApplication::translate("GUITestClass", "Check", Q_NULLPTR));
		pushButton_help->setText(QApplication::translate("GUITestClass", "Help", Q_NULLPTR));
		menu->setTitle(QApplication::translate("GUITestClass", "Mode", Q_NULLPTR));
		menu_2->setTitle(QApplication::translate("GUITestClass", "Personal Best", Q_NULLPTR));
		//menu_help->setTitle(QApplication::translate("GUITestClass", "Help", Q_NULLPTR));
	} // retranslateUi

private:
	int col_translate(int j)
	{
		if (j < 3)
		{
			return j;
		}
		else if (j > 3 && j < 7)
		{
			return (j - 1);
		}
		else if (j > 7)
		{
			return (j - 2);
		}
		return j;
	}

};

namespace Ui {
	class GUITestClass : public Ui_GUITestClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUITEST_H

