/*
 * Copyright 2010-2013 by Thorsten Staerk
 * http://www.staerk.de/thorsten
 *
 * This file is part of qtimetracker.
 *
 * qtimetracker is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * qtimetracker is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with qtimetracker.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModelIndex>
#include <QTimer>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QIcon qi_watch[8];
    QIcon qi_complete;
    int oldtimeinseconds; // remember "time" column when task was started
    /** \brief column number for the task name */
    static const int coltaskname = 1;
    /** \brief column number for the timer icon */
    static const int coltimericon = 2;
    /** \brief column number for displaying the time */
    static const int coltime = 3;
    /** \brief column number for remembering the last start time when a task is running */
    static const int collaststart = 4;
    /** \brief column number for storing the display time (coltime) of the last start */
    static const int collasttime = 5;
    /** \brief column number for marking a task as completed (icon) */
    static const int colcomplete = 0;

private slots:
    QString save();
    QString load();
    /** Deliver the index of the task that is running.
       Only one timer can run at the moment.
       A task is marked as running if there is a date in column 3.
       Example: result=2 means the timer has been started for the third task. */
    int runningtaskindex();
    /** Deliver how many tasks exist.
      As long as there are no subtasks, this is trivial, but this will
      change as soon as we have subtasks. */
    int taskcount();
    void prepareicons();
    void on_actionQuit_triggered();
    void slottimer();
    void slotstarttiming();
    void slotstoptiming();
    void stopalltimers();
    void slotaddtask();
    void slotdeletetask();
    void on_btn_addtask_clicked();
    void on_btn_starttimer_clicked();
    void on_btn_stoptimer_clicked();
    void on_btn_deletetask_clicked();
    void on_treeWidget_clicked(const QModelIndex &index);
    void on_mousedoubleclick(QMouseEvent* e);
};

#endif // MAINWINDOW_H
