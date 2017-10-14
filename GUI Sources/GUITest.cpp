#include "GUITest.h"
#include <QMessageBox>
#include "QString"
#include "func.h"
#include "Core.h"
#include <assert.h>
#include <chrono>
#include <random>

bool informSuccess = false;

GUITest::GUITest(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	this->m_easyBest = -1;
	this->m_normalBest = -1;
	this->m_hardBest = -1;
	this->m_hasStarted = false;

	memset(m_fill, 0, sizeof(m_fill));
	m_record = fopen("record.txt", "r");
	//这里应该有一个断言，文件一定要存在
	if (m_record == NULL)
	{
		QMessageBox::information(this, tr("error"), tr("File is not exist"));
	}
	for (int i = 0; i < 3; i++)
	{
		if (fscanf(m_record, "%d", &m_bestTime[i]) == EOF)
		{
			m_bestTime[i] = 0;
		}
	}

	fclose(m_record);
	m_record = NULL;

	isStart = false;
	timer = new QTimer;
	TimeRecord = new QTime(0, 0, 0); //初始化时间

	ui.Timer->setDigitCount(8);
	ui.Timer->setSegmentStyle(QLCDNumber::Flat);
	ui.Timer->display(TimeRecord->toString("hh:mm:ss"));

	QPixmap pixStart("start.png");
	startIcon = new QIcon(pixStart);
	QPixmap pixPause("pause.png");
	pauseIcon = new QIcon(pixPause);
	QPixmap pixStop("stop.png");
	stopIcon = new QIcon(pixStop);

	ui.Start->setIcon(*startIcon);
	ui.Start->show();
	ui.Start->setIconSize(QSize(48, 45));
	/*ui.Stop->setIcon(*stopIcon);
	ui.Stop->show();
	ui.Stop->setIconSize(QSize(48, 45));*/

	connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));
	connect(ui.Start, SIGNAL(clicked()), this, SLOT(on_Start_clicked()));
	//connect(ui.Stop, SIGNAL(clicked()), this, SLOT(on_Stop_clicked()));
	connect(ui.pushButton_5, SIGNAL(clicked()), this, SLOT(on_CheckAns()));
	connect(ui.pushButton_3, SIGNAL(clicked()), this, SLOT(on_Clue()));
	connect(ui.pushButton_4, SIGNAL(clicked()), this, SLOT(Restart()));
	//每个小格子的槽函数
	for (int i = 0; i < GRIDSIZE; i++)
	{
		for (int j = 0; j < GRIDSIZE; j++)
		{
			connect(ui.textEdit[i][j], SIGNAL(cursorPositionChanged()), this, SLOT(give_pointer()));
		}
	}

	//菜单栏上的难度选择
	connect(ui.actionEasy, SIGNAL(triggered()), this, SLOT(SetModeEasy()));
	connect(ui.actionNormal, SIGNAL(triggered()), this, SLOT(SetModeNormal()));
	connect(ui.actionHard, SIGNAL(triggered()), this, SLOT(SetModeHard()));

	//菜单栏上的用户最佳记录
	connect(ui.actionEasy_2, SIGNAL(triggered()), this, SLOT(BestRecordEasy()));
	connect(ui.actionNormal_2, SIGNAL(triggered()), this, SLOT(BestRecordNormal()));
	connect(ui.actionHard_2, SIGNAL(triggered()), this, SLOT(BestRecordHard()));
	ui.focusIn = NULL;
}

void GUITest::updateTime()
{
	*TimeRecord = TimeRecord->addSecs(1);
	ui.Timer->display(TimeRecord->toString("hh:mm:ss"));
}

void GUITest::on_Start_clicked() 
{
	if (!m_hasStarted)
	{
		return;
	}
	if (!isStart) //尚未开始 开始计时
	{
		ui.Start->setIcon(*pauseIcon);
		ui.Start->show();
		timer->start(1000);
		showNumber();
	}
	else //已经开始，暂停
	{
		ui.Start->setIcon(*startIcon);
		ui.Start->show();
		timer->stop();

		//首先将所有的数字都拷贝下来
		memset(m_fill, 0, sizeof(m_fill));
		for (int i = 0; i < GRIDSIZE; i++)
		{
			for (int j = 0; j < GRIDSIZE; j++)
			{
				QString str = ui.textEdit[i][j]->toPlainText();
				
				if (IsValidChar(str))
				{
					int num = str.toInt();
					m_fill[i * GRIDSIZE + j] = num;
					if (ui.textEdit[i][j]->isReadOnly())
					{
						m_fillBlack[i * GRIDSIZE + j] = num;
					}
					ui.textEdit[i][j]->setReadOnly(false);
					QString strIn = "";
					ui.textEdit[i][j]->setText(strIn);
				}
				ui.textEdit[i][j]->setReadOnly(true);
			}
		}

	}
	isStart = !isStart;
}

void GUITest::on_Stop_clicked()
{
	ui.Start->setIcon(*startIcon);
	ui.Start->show();
	timer->stop();    //计时器停止
	TimeRecord->setHMS(0, 0, 0); //时间设为0
	ui.Timer->display(TimeRecord->toString("hh:mm:ss")); //显示00:00:00
	//Restart();
	//RestartShow(); 
	//这里不应该只是暂停游戏，还应该把所有的格子都覆盖起来
	isStart = false;
}

void GUITest::showNumber()
{

	for (int i = 0; i < GRIDSIZE; i++)
	{
		for (int j = 0; j < GRIDSIZE; j++)
		{
			ui.textEdit[i][j]->setReadOnly(false);
			if (m_fill[i * GRIDSIZE + j] > 0)
			{
				QString str = QString::number(m_fill[i * GRIDSIZE + j], 10);
				ui.textEdit[i][j]->setText(str);
				if (m_fillBlack[i * GRIDSIZE + j] == 0)       //此时要用蓝色字体
				{
					ui.textEdit[i][j]->setStyleSheet(QString::fromUtf8("font: 21pt \"\351\273\221\344\275\223\";""border: 1px solid grey;color:blue"));
					ui.textEdit[i][j]->setAlignment(Qt::AlignCenter);
					ui.textEdit[i][j]->setReadOnly(false);
				}
				else
				{
					ui.textEdit[i][j]->setStyleSheet(QString::fromUtf8("font: 21pt \"\351\273\221\344\275\223\";"));
					ui.textEdit[i][j]->setAlignment(Qt::AlignCenter);
					ui.textEdit[i][j]->setReadOnly(true);
				}
				
			}
			else
			{
				QString str = "";
				ui.textEdit[i][j]->setText(str);
			}
		}
	}
	ui.focusIn = NULL;
}

bool GUITest::CheckAns()
{
	for (int i = 0; i < GRIDSIZE; i++)
	{
		for (int j = 0; j < GRIDSIZE; j++)
		{
			QString str = ui.textEdit[i][j]->toPlainText();
			if (IsValidChar(str))
			{
				int num = str.toInt();
				if (num != m_result[i * GRIDSIZE + j])
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
	}
	return true;
}

//检查答案
void GUITest::on_CheckAns()
{
	if (!m_hasStarted)
	{
		return;
	}
	if (CheckAns())
	{
		ui.Start->setIcon(*startIcon);
		ui.Start->show();
		timer->stop();
		isStart = false;
		string str;
		str = "Your answer is right !!";

		int time_temp = TimeRecord->hour() * 3600 + TimeRecord->minute() * 60 + TimeRecord->second();
		switch (m_mode)
		{
		case EASY:
			if (m_bestTime[EASY - 1] == 0)
			{
				m_bestTime[EASY - 1] = time_temp;
				str = str + "\n And You Get A New Record";
			}
			else if (m_bestTime[EASY - 1] > time_temp)
			{
				str = str + "\n And You Get A New Record";
				m_bestTime[EASY - 1] = time_temp;
			}
			break;

		case MIDDLE:
			if (m_bestTime[MIDDLE - 1] == 0)
			{
				m_bestTime[MIDDLE - 1] = time_temp;
				str = str + "\n And You Get A New Record";
			}
			else if (m_bestTime[MIDDLE - 1] > time_temp)
			{
				str = str + "\n And You Get A New Record";
				m_bestTime[MIDDLE - 1] = time_temp;
			}
			break;
		case HARD:
			if (m_bestTime[HARD - 1] == 0)
			{
				m_bestTime[HARD - 1] = time_temp;
				str = str + "\n And You Get A New Record";
			}
			else if (m_bestTime[HARD - 1] > time_temp)
			{
				str = str + "\n And You Get A New Record";
				m_bestTime[HARD - 1] = time_temp;
			}
			break;
		}

		m_record = fopen("record.txt", "w");
		if (m_record == NULL)
		{
			QMessageBox::information(this, tr("error"), tr("File is not exist"));
		}
		for (int i = 0; i < 3; i++)
		{
			fprintf(m_record, "%d\n", m_bestTime[i]);
		}
		fclose(m_record);

		QMessageBox::information(this, tr("Result"), tr(str.c_str()));
	}
	else
	{
		QMessageBox::information(this, tr("Result"), tr("Your answer is Wrong."));
	}
}

void GUITest::SetResult(int number[CELL])
{
	for (int i = 0; i < CELL; i++)
	{
		m_result[i] = number[i];
	}
}

void GUITest::on_Clue()
{
	if (ui.focusIn != NULL)
	{
		int col;
		int line;
		for (int i = 0; i < GRIDSIZE; i++)
		{
			for (int j = 0; j < GRIDSIZE; j++)
			{
				if (ui.focusIn == ui.textEdit[i][j])
				{
					line = i;
					col = j;
					break;
				}
			}
		}

		int num = m_result[line * GRIDSIZE + col];

		QString str = QString::number(num, 10);
		ui.textEdit[line][col]->setText(str);
		ui.textEdit[line][col]->setStyleSheet(QString::fromUtf8("font: 21pt \"\351\273\221\344\275\223\";""border: 1px solid grey"));     //这里的边框或许要设置一下
		ui.textEdit[line][col]->setAlignment(Qt::AlignCenter);
		ui.textEdit[line][col]->setReadOnly(true);
		informSuccess = true;
	}
}

void GUITest::SetFill(int number[CELL])
{
	for (int i = 0; i < CELL; i++)
	{
		m_fill[i] = number[i];
	}
}

void GUITest::give_pointer()
{
	MyTextEdit* temp = qobject_cast<MyTextEdit*>(sender());
	if (!temp->isReadOnly())
	{
		ui.focusIn = temp;
	}
}

void GUITest::SetMode()
{
	int save_sudoku[1][CELL];
	memset(save_sudoku, 0, sizeof(save_sudoku));

	bool choosen[10];
	memset(choosen,0,sizeof(choosen));

	srand(time(0));

	for (int i = 0; i < 5; i++)
	{
	int posi = rand() % 9 + 1;
	while (choosen[posi])
	{
	posi = rand() % 9 + 1;
	}
	choosen[posi] = true;
	save_sudoku[0][i] = posi;
	}

	int reduce;
	int empty;
	switch (m_mode)
	{
	case EASY:
		reduce = 40 + rand() % 8;
		break;
	case MIDDLE:
		reduce = 32 + rand() % 8;
		break;
	case HARD:
		reduce = 31;
		break;
	default:
		break;
	}
	empty = CELL - reduce;

	Core temp;
	temp.generate(1, empty, empty, true, save_sudoku);

	memset(m_fillBlack, 0, sizeof(m_fillBlack));
	memset(m_fill,0,sizeof(m_fill));

	for (int i = 0; i < CELL; i++)
	{
		m_fill[i] = save_sudoku[0][i];
		m_fillBlack[i] = save_sudoku[0][i];
		m_backup[i] = save_sudoku[0][i];
	}

	m_hasStarted = true;
	temp.solve(save_sudoku[0], m_result);
	showNumber();	
}

int GUITest::GetMode()
{
	return this->m_mode;
}

void GUITest::Restart()
{
	if (m_hasStarted)
	{
		on_Stop_clicked();
		on_Start_clicked();
		//showNumber();
		RestartShow();
		ui.focusIn = NULL;
	}
}

void GUITest::SetModeEasy()
{

	this->m_mode = EASY;
	this->setWindowTitle(QApplication::translate("GUITestClass", "Sudoku Game.    Mode:Easy", Q_NULLPTR));
	SetMode();
	on_Stop_clicked();
	on_Start_clicked();
}

void GUITest::SetModeNormal()
{
	this->m_mode = MIDDLE;
	this->setWindowTitle(QApplication::translate("GUITestClass", "Sudoku Game.    Mode:Normal", Q_NULLPTR));
	SetMode();
	on_Stop_clicked();
	on_Start_clicked();
}

void GUITest::SetModeHard()
{
	this->m_mode = HARD;
	this->setWindowTitle(QApplication::translate("GUITestClass", "Sudoku Game.    Mode:Hard", Q_NULLPTR));
	SetMode();
	on_Stop_clicked();
	on_Start_clicked();
}

//用户最优记录槽函数
void GUITest::BestRecordEasy()
{
	if (m_bestTime[EASY - 1] > 0)
	{
		string record = "The Best Record In Easy Is \n";
		record = record + sec2str(m_bestTime[EASY - 1]);
		QMessageBox::information(this, tr("Record"), tr(record.c_str()));
	}
	else
	{
		QMessageBox::information(this, tr("Record"), tr("Get to create your record !!"));
	}
}

void GUITest::BestRecordNormal()
{
	if (m_bestTime[MIDDLE - 1] > 0)
	{
		string record = "The Best Record In Normal Is \n";
		record = record + sec2str(m_bestTime[MIDDLE - 1]);
		QMessageBox::information(this, tr("Record"), tr(record.c_str()));
	}
	else
	{
		QMessageBox::information(this, tr("Record"), tr("Get to create your record !!"));
	}
}

void GUITest::BestRecordHard()
{
	if (m_bestTime[HARD - 1] > 0)
	{
		string record = "The Best Record In Hard Is \n";
		record = record + sec2str(m_bestTime[HARD - 1]);
		QMessageBox::information(this, tr("Record"), tr(record.c_str()));
	}
	else
	{
		QMessageBox::information(this, tr("Record"), tr("Get to create your record !!"));
	}
}

int GUITest::GetEasy()
{
	return m_bestTime[EASY - 1];
}

int GUITest::GetNormal()
{
	return m_bestTime[MIDDLE - 1];
}

int GUITest::GetHard()
{
	return m_bestTime[HARD - 1];
}

string GUITest::sec2str(int sec_count)
{
	string time;
	int sec = sec_count % 60;
	int min = sec_count / 60;
	int hour = min / 60;

	string hour_time = "";
	if (hour > 0)
	{
		hour_time = hour_time + to_string(hour);
		hour_time = hour_time + "h,";
		min = min % 60;
	}

	string min_time = "";
	if (min > 0)
	{
		min_time = min_time + to_string(min);
		min_time = min_time + "m,";
	}

	string sec_time = "";
	if (sec > 0)
	{
		sec_time = sec_time + to_string(sec);
		sec_time = sec_time + "s";
	}
	time = hour_time + min_time + sec_time;
	return time;
}

void GUITest::RestartShow()
{
	for (int i = 0; i < GRIDSIZE; i++)
	{
		for (int j = 0; j < GRIDSIZE; j++)
		{
			ui.textEdit[i][j]->setReadOnly(false);
			if (m_backup[i * GRIDSIZE + j] > 0)
			{
				QString str = QString::number(m_fill[i * GRIDSIZE + j], 10);
				ui.textEdit[i][j]->setText(str);
				ui.textEdit[i][j]->setStyleSheet(QString::fromUtf8("font: 21pt \"\351\273\221\344\275\223\";"));
				ui.textEdit[i][j]->setAlignment(Qt::AlignCenter);
				ui.textEdit[i][j]->setReadOnly(true);
			}

			else
			{
				QString str = "";
				ui.textEdit[i][j]->setText(str);
			}
		}
	}
}