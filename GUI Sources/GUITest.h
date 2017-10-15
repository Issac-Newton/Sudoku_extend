#pragma once

#include <QtWidgets/QMainWindow>
#include <QDateTime>
#include <QTimer>
#include <QTime>
#include <QPixmap>
#include <QIcon>
#include "ui_GUITest.h"
#include "Core.h"

class GUITest : public QMainWindow
{
	Q_OBJECT

public:
	GUITest(QWidget *parent = Q_NULLPTR);
	void showNumber();
	bool CheckAns();
	void SetResult(int number[CELL]);
	void SetFill(int number[CELL]);
	int GetMode();

	int GetEasy();
	int GetNormal();
	int GetHard();

private slots:
	void updateTime();
	void on_Start_clicked();
	void on_Stop_clicked();

	void on_CheckAns();
	void on_Clue();
	void give_pointer();

	void Restart();

	void SetModeEasy();
	void SetModeNormal();
	void SetModeHard();

	void BestRecordEasy();
	void BestRecordNormal();
	void BestRecordHard();
	void HELP();

private:
	int m_mode;
	int m_backup[CELL];
	int m_result[CELL];
	int m_fill[CELL];
	int m_fillBlack[CELL];
	bool m_hasStarted;
	FILE* m_record;

	int m_easyBest;
	int m_normalBest;
	int m_hardBest;
	int m_bestTime[3];

	Ui::GUITestClass ui;
	QTimer* timer;
	QTime * TimeRecord;
	bool isStart;
	QIcon * startIcon;
	QIcon * pauseIcon;
	QIcon * stopIcon;
	void SetMode();
	string sec2str(int sec);
	void RestartShow();
};
	