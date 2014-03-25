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

#include <QInputDialog>
#include <QDateTime>
#include <QDebug>
#include <QFile>
#include <QMessageBox>
#include <QMouseEvent>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "taskdialog.h"

/*
  A task is marked as running using column 3. Column 3 holds the time when the task was started if it is running.
  Column 4 holds the time of the task when it was started.
  */

// Gallery of unmodern art
static const char *ch_new[] = {
/* columns rows colors chars-per-pixel */
"22 22 2 1",
"+ c #009900",
"  c None",
/* pixels */
"                      ",
"                      ",
"         +++          ",
"         +++          ",
"         +++          ",
"         +++          ",
"         +++          ",
"         +++          ",
"         +++          ",
"  ++++++++++++++++++  ",
"  ++++++++++++++++++  ",
"  ++++++++++++++++++  ",
"         +++          ",
"         +++          ",
"         +++          ",
"         +++          ",
"         +++          ",
"         +++          ",
"         +++          ",
"                      ",
"                      ",
"                      ",
};
static const char *ch_start[] = {
/* columns rows colors chars-per-pixel */
"22 22 2 1",
"+ c #009900",
"  c None",
/* pixels */
"                      ",
"                      ",
"      ++              ",
"      +++             ",
"      ++++            ",
"      +++++           ",
"      ++++++          ",
"      +++++++         ",
"      ++++++++        ",
"      +++++++++       ",
"      ++++++++++      ",
"      +++++++++       ",
"      ++++++++        ",
"      +++++++         ",
"      ++++++          ",
"      +++++           ",
"      ++++            ",
"      +++             ",
"      ++              ",
"                      ",
"                      ",
"                      ",
};
static const char *ch_stop[] = {
/* columns rows colors chars-per-pixel */
"22 22 2 1",
"+ c #404040",
"  c None",
/* pixels */
"                      ",
"                      ",
"                      ",
"   ++++++++++++++++   ",
"   ++++++++++++++++   ",
"   ++++++++++++++++   ",
"   ++++++++++++++++   ",
"   ++++++++++++++++   ",
"   ++++++++++++++++   ",
"   ++++++++++++++++   ",
"   ++++++++++++++++   ",
"   ++++++++++++++++   ",
"   ++++++++++++++++   ",
"   ++++++++++++++++   ",
"   ++++++++++++++++   ",
"   ++++++++++++++++   ",
"   ++++++++++++++++   ",
"   ++++++++++++++++   ",
"   ++++++++++++++++   ",
"                      ",
"                      ",
"                      ",
};
static const char *ch_delete[] = {
/* columns rows colors chars-per-pixel */
"22 22 2 1",
"+ c #900000",
"  c None",
/* pixels */
"                      ",
"                      ",
"  +++             +++ ",
"  ++++           ++++ ",
"   ++++         ++++  ",
"    ++++       ++++   ",
"     ++++     ++++    ",
"      ++++   ++++     ",
"       ++++ ++++      ",
"        +++++++       ",
"         +++++        ",
"         +++++         ",
"         +++++        ",
"        +++++++       ",
"       ++++ ++++      ",
"      ++++   ++++     ",
"     ++++     ++++    ",
"    ++++       ++++   ",
"   ++++         ++++  ",
"  ++++           ++++ ",
"                      ",
"                      ",
};
static const char *ch_complete[] =  {
        "15 13 7 1",
        "       c None",
        ".      c #000000",
        "+      c #009000",
        "@      c #ACACAC",
        "#      c #E9E9E9",
        "$      c #989898",
        "%      c #FFFFFF",
        "               ",
        "              +",
        "             ++",
        "           +++ ",
        "          +++  ",
        "         +++   ",
        "        +++    ",
        "       +++     ",
        "+     +++      ",
        " ++  +++       ",
        "  +++++        ",
        "   +++         ",
        "    +          "};

// watches (c) 2000 by blacky, see http://websvn.kde.org/trunk/KDE/kdepim/ktimetracker/pics/watch-0.xpm?view=log
static const char * watch_0_xpm[] = {
"15 13 7 1",
"       c None",
".      c #000000",
"+      c #4A4A4A",
"@      c #ACACAC",
"#      c #E9E9E9",
"$      c #989898",
"%      c #FFFFFF",
"    +@#.#@+    ",
"   $%%%.%%%$   ",
"  $%%%%.%%%%$  ",
" +%%%%%.%%%%%+ ",
" @%%%%%.%%%%%@ ",
" #%%%%%.%%%%%# ",
".%%%%%%.%%%%%%.",
" #%%%%%%%%%%%# ",
" @%%%%%%%%%%%@ ",
" +%%%%%%%%%%%+ ",
"  $%%%%%%%%%$  ",
"   $%%%%%%%$   ",
"    +@#%#@+    "};
/* XPM */
static const char * watch_1_xpm[] = {
"15 13 7 1",
" 	c None",
".	c #000000",
"+	c #4A4A4A",
"@	c #ACACAC",
"#	c #E9E9E9",
"$	c #FFFFFF",
"%	c #989898",
"    +@#$#@+    ",
"   %$$$$$$$%   ",
"  %$$$$$$$$.%  ",
" +$$$$$$$$.$$+ ",
" @$$$$$$$.$$$@ ",
" #$$$$$$.$$$$# ",
".$$$$$$.$$$$$$.",
" #$$$$$$$$$$$# ",
" @$$$$$$$$$$$@ ",
" +$$$$$$$$$$$+ ",
"  %$$$$$$$$$%  ",
"   %$$$$$$$%   ",
"    +@#$#@+    "};
static const char * watch_2_xpm[] = {
"15 13 7 1",
" 	c None",
".	c #000000",
"+	c #4A4A4A",
"@	c #ACACAC",
"#	c #E9E9E9",
"$	c #FFFFFF",
"%	c #989898",
"    +@#$#@+    ",
"   %$$$$$$$%   ",
"  %$$$$$$$$$%  ",
" +$$$$$$$$$$$+ ",
" @$$$$$$$$$$$@ ",
" #$$$$$$$$$$$# ",
".$$$$$$........",
" #$$$$$$$$$$$# ",
" @$$$$$$$$$$$@ ",
" +$$$$$$$$$$$+ ",
"  %$$$$$$$$$%  ",
"   %$$$$$$$%   ",
"    +@#$#@+    "};
static const char * watch_3_xpm[] = {
"15 13 7 1",
"       c None",
".      c #000000",
"+      c #4A4A4A",
"@      c #ACACAC",
"#      c #E9E9E9",
"$      c #FFFFFF",
"%      c #989898",
"    +@#$#@+    ",
"   %$$$$$$$%   ",
"  %$$$$$$$$$%  ",
" +$$$$$$$$$$$+ ",
" @$$$$$$$$$$$@ ",
" #$$$$$$$$$$$# ",
".$$$$$$.$$$$$$.",
" #$$$$$$.$$$$# ",
" @$$$$$$$.$$$@ ",
" +$$$$$$$$.$$+ ",
"  %$$$$$$$$.%  ",
"   %$$$$$$$%   ",
"    +@#$#@+    "};
static const char * watch_4_xpm[] = {
"15 13 7 1",
"       c None",
".      c #000000",
"+      c #4A4A4A",
"@      c #ACACAC",
"#      c #E9E9E9",
"$      c #FFFFFF",
"%      c #989898",
"    +@#$#@+    ",
"   %$$$$$$$%   ",
"  %$$$$$$$$$%  ",
" +$$$$$$$$$$$+ ",
" @$$$$$$$$$$$@ ",
" #$$$$$$$$$$$# ",
".$$$$$$.$$$$$$.",
" #$$$$$.$$$$$# ",
" @$$$$$.$$$$$@ ",
" +$$$$$.$$$$$+ ",
"  %$$$$.$$$$%  ",
"   %$$$.$$$%   ",
"    +@#.#@+    "};
static const char * watch_5_xpm[] = {
"15 13 7 1",
"       c None",
".      c #000000",
"+      c #4A4A4A",
"@      c #ACACAC",
"#      c #E9E9E9",
"$      c #FFFFFF",
"%      c #989898",
"    +@#$#@+    ",
"   %$$$$$$$%   ",
"  %$$$$$$$$$%  ",
" +$$$$$$$$$$$+ ",
" @$$$$$$$$$$$@ ",
" #$$$$$$$$$$$# ",
".$$$$$$.$$$$$$.",
" #$$$$.$$$$$$# ",
" @$$$.$$$$$$$@ ",
" +$$.$$$$$$$$+ ",
"  %.$$$$$$$$%  ",
"   %$$$$$$$%   ",
"    +@#$#@+    "};
static const char * watch_6_xpm[] = {
"15 13 7 1",
"       c None",
".      c #000000",
"+      c #4A4A4A",
"@      c #ACACAC",
"#      c #E9E9E9",
"$      c #FFFFFF",
"%      c #989898",
"    +@#$#@+    ",
"   %$$$$$$$%   ",
"  %$$$$$$$$$%  ",
" +$$$$$$$$$$$+ ",
" @$$$$$$$$$$$@ ",
" #$$$$$$$$$$$# ",
"........$$$$$$.",
" #$$$$$$$$$$$# ",
" @$$$$$$$$$$$@ ",
" +$$$$$$$$$$$+ ",
"  %$$$$$$$$$%  ",
"   %$$$$$$$%   ",
"    +@#$#@+    "};
static const char * watch_7_xpm[] = {
"15 13 7 1",
"       c None",
".      c #000000",
"+      c #4A4A4A",
"@      c #ACACAC",
"#      c #E9E9E9",
"$      c #FFFFFF",
"%      c #989898",
"    +@#$#@+    ",
"   %$$$$$$$%   ",
"  %.$$$$$$$$%  ",
" +$$.$$$$$$$$+ ",
" @$$$.$$$$$$$@ ",
" #$$$$.$$$$$$# ",
".$$$$$$.$$$$$$.",
" #$$$$$$$$$$$# ",
" @$$$$$$$$$$$@ ",
" +$$$$$$$$$$$+ ",
"  %$$$$$$$$$%  ",
"   %$$$$$$$%   ",
"    +@#$#@+    "};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    oldtimeinseconds(-1),
    store(new StorageSimpleText)
{
    ui->setupUi(this);
    connect(ui->treeWidget, SIGNAL(mousedoubleclicked(QMouseEvent*)),this,SLOT(on_mousedoubleclick(QMouseEvent*)));
    prepareicons();
    load();
    timer=new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(slottimer()));
    const QPixmap pm_watch_0(watch_0_xpm);
    QIcon qi_watch_0(pm_watch_0);
    const QPixmap pm_new(ch_new);
    QIcon qi_new(pm_new);
    ui->btn_addtask->setIcon(qi_new);
    const QPixmap pm_start(ch_start);
    QIcon qi_start(pm_start);
    ui->btn_starttimer->setIcon(qi_start);
    const QPixmap pm_stop(ch_stop);
    QIcon qi_stop(pm_stop);
    ui->btn_stoptimer->setIcon(qi_stop);
    const QPixmap pm_delete(ch_delete);
    QIcon qi_delete(pm_delete);
    ui->btn_deletetask->setIcon(qi_delete);
    ui->treeWidget->resizeColumnToContents(coltaskname);
    ui->treeWidget->header()->resizeSection(coltimericon,20);
    ui->treeWidget->header()->resizeSection(coltime,120);
    ui->treeWidget->header()->resizeSection(colcomplete,20);
    ui->treeWidget->setRootIsDecorated(false);
    ui->treeWidget->setColumnCount(7);
    ui->treeWidget->setColumnHidden(collaststart,true);
    ui->treeWidget->setColumnHidden(collasttime,true);
    ui->treeWidget->setColumnHidden(coltaskid,true);
    QTreeWidgetItem *item1 = ui->treeWidget->headerItem();
/* For Qt5, QApplication::UnicodeUTF8 is obsolate and QTreeWidgetItem::setText() has only 2 parameters. */
#if (QT_VERSION >= 0x050000)
    // col 1: task name
    item1->setText(coltimericon, QApplication::translate("MainWindow", "", 0)); // col 2: timer icon
    item1->setText(coltime, QApplication::translate("MainWindow", "time (hh:mm:ss)", 0)); // col 3: time col
    // col 4: last start time of task, e.g. Sunday 11:45 (hidden)
    // col 5: last content of col 2 before start, e.g. 00:00:19 (hidden)
    item1->setText(colcomplete, QApplication::translate("MainWindow", "", 0)); // col 0: completed
#else
    // col 1: task name
    item1->setText(coltimericon, QApplication::translate("MainWindow", "", 0, QApplication::UnicodeUTF8)); // col 2: timer icon
    item1->setText(coltime, QApplication::translate("MainWindow", "time (hh:mm:ss)", 0, QApplication::UnicodeUTF8)); // col 3: time col
    // col 4: last start time of task, e.g. Sunday 11:45 (hidden)
    // col 5: last content of col 2 before start, e.g. 00:00:19 (hidden)
    item1->setText(colcomplete, QApplication::translate("MainWindow", "", 0, QApplication::UnicodeUTF8)); // col 0: completed
#endif
}

MainWindow::~MainWindow()
{
    slotstoptiming();
    delete ui;
}

void MainWindow::prepareicons()
{
    const QPixmap pm_watch_0(watch_0_xpm);
    qi_watch[0]=QIcon(pm_watch_0);
    QPixmap pm_watch(watch_1_xpm);
    qi_watch[1]=QIcon(pm_watch);
    pm_watch=QPixmap(watch_2_xpm);
    qi_watch[2]=QIcon(pm_watch);
    pm_watch=QPixmap(watch_3_xpm);
    qi_watch[3]=QIcon(pm_watch);
    pm_watch=QPixmap(watch_4_xpm);
    qi_watch[4]=QIcon(pm_watch);
    pm_watch=QPixmap(watch_5_xpm);
    qi_watch[5]=QIcon(pm_watch);
    pm_watch=QPixmap(watch_6_xpm);
    qi_watch[6]=QIcon(pm_watch);
    pm_watch=QPixmap(watch_7_xpm);
    qi_watch[7]=QIcon(pm_watch);
    QPixmap pm_complete=QPixmap(ch_complete);
    qi_complete=QIcon(pm_complete);
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type())
    {
        case QEvent::LanguageChange:
            ui->retranslateUi(this);
            break;
        default:
            break;
    }
}

void MainWindow::on_actionQuit_triggered()
{
    close();
}

int MainWindow::runningtaskindex()
{
    int result=-1;
    for (int i=0; i<taskcount(); i=i+1)
    {
        if (!ui->treeWidget->topLevelItem(i)->text(collaststart).isEmpty()) result=i;
    }
    return result;
}

int MainWindow::taskcount()
{
    return ui->treeWidget->topLevelItemCount();
}

void MainWindow::slotaddtask()
{
    taskDialog* taskdialog=new taskDialog();
    taskdialog->exec();
    if (taskdialog->hasaccepted())
    {
        uint32_t new_task_id = store->AddTask(taskdialog->text().toStdString());
        ui->treeWidget->addTopLevelItem(new QTreeWidgetItem(QStringList(QString())));
        ui->treeWidget->topLevelItem(ui->treeWidget->topLevelItemCount()-1)->setText(coltaskname, store->GetTaskName(new_task_id).c_str());
        ui->treeWidget->topLevelItem(ui->treeWidget->topLevelItemCount()-1)->setText(coltaskid, QString::number(new_task_id));
        ui->treeWidget->topLevelItem(ui->treeWidget->topLevelItemCount()-1)->setFlags(ui->treeWidget->topLevelItem((ui->treeWidget->topLevelItemCount()-1))->flags() | Qt::ItemIsEditable);
        /* HINT: When compiling for Qt5 this is necesarry or nothing is shown in the time column. */
        ui->treeWidget->topLevelItem(ui->treeWidget->topLevelItemCount()-1)->setText(this->coltime, "00:00:00");
        save();
        ui->treeWidget->resizeColumnToContents(coltaskname);
    }
}

/** \brief Convert a time string to a value of seconds
 *  \param timestring the time string to convert
 *  \return value of seconds converted from time string
 *
 * The expected time string should be
 *   HH:MM:SS
 * where HH stands for the hour, MM for the minute and SS for
 * the seconds.
 */
int timestringtoseconds(QString timestring)
{
    QStringList time_elements = timestring.split(':');
    if (3 != time_elements.length())
        return 0;
    /* calculate the soconds from the single values */
    int seconds = time_elements[0].toInt() * 60 * 60;
    seconds += time_elements[1].toInt() * 60;
    seconds += time_elements[2].toInt();
    return seconds;
}

/** \brief Convert a value of seconds to a readable time string
 *  \param seconds the value of seconds to convert
 *  \return time string in the form HH:MM:SS
 */
QString timestring(int seconds)
{
    int days = seconds / (24 * 60 * 60);
    seconds -= days * (24 * 60 * 60);
    QTime time = QTime((int)(seconds / 3600), (int)(seconds / 60) % 60, seconds % 60);
    QString answer;
    return answer.sprintf("%02d:%02d:%02d", days * 24 + time.hour(), time.minute(), time.second());
}

void MainWindow::slotstarttiming()
{
    stopalltimers();
    if (ui->treeWidget->currentItem())
    {
        ui->treeWidget->currentItem()->setIcon(coltimericon, qi_watch[0]);
        ui->treeWidget->currentItem()->setText(collaststart, QString::number(QDateTime::currentDateTime().toTime_t()));
        ui->treeWidget->currentItem()->setText(collasttime, ui->treeWidget->currentItem()->text(coltime));
        oldtimeinseconds=-1; // dear slottimer, please note the current time column
        timer->start(1000);
    }
    else QMessageBox::information(0,"Info","First select a task that you want to start timing for.");
}

void MainWindow::slotstoptiming()
{
    if (ui->treeWidget->currentItem())
    {
        if (!ui->treeWidget->currentItem()->text(collaststart).isEmpty())
        { // task is really running
            timer->stop();
            ui->treeWidget->currentItem()->setIcon(coltimericon,QIcon());
            /* update the store to give a chance to save period */
            uint32_t task_id = ui->treeWidget->currentItem()->text(coltaskid).toUInt();
            uint task_start = ui->treeWidget->currentItem()->text(collaststart).toUInt();
            uint task_end = QDateTime::currentDateTime().toTime_t();
            store->AddTaskPeriod(task_id, task_start, task_end);
            /* mark task as not running */
            ui->treeWidget->currentItem()->setText(collaststart,QString());
        }
        save();
    }
}

void MainWindow::stopalltimers()
{
    timer->stop();
    for (int i = 0; i < taskcount(); ++i)
    {
        if (!ui->treeWidget->topLevelItem(i)->text(collaststart).isEmpty())
        { // task is really running
            ui->treeWidget->topLevelItem(i)->setIcon(coltimericon,QIcon());
            /* update the store to give a chance to save period */
            uint32_t task_id = ui->treeWidget->topLevelItem(i)->text(coltaskid).toUInt();
            uint task_start = ui->treeWidget->topLevelItem(i)->text(collaststart).toUInt();
            uint task_end = QDateTime::currentDateTime().toTime_t();
            store->AddTaskPeriod(task_id, task_start, task_end);
            /* mark task as not running */
            ui->treeWidget->topLevelItem(i)->setText(collaststart,QString());
        }
    }
    save();
}

void MainWindow::slotdeletetask()
{
    slotstoptiming();
    uint32_t del_task_id = ui->treeWidget->currentItem()->text(coltaskid).toUInt();
    store->DelTask(del_task_id);
    delete(ui->treeWidget->currentItem());
    save();
}

void MainWindow::slottimer()
{
    static int turn=0;
    if (++turn>=8) turn-=8;
    ui->treeWidget->topLevelItem(runningtaskindex())->setIcon(coltimericon,qi_watch[turn]);

    // time calculation
    if (oldtimeinseconds==-1)
    {
        oldtimeinseconds = timestringtoseconds(ui->treeWidget->topLevelItem(runningtaskindex())->text(coltime));
    }
    uint laststart = ui->treeWidget->topLevelItem(runningtaskindex())->text(collaststart).toUInt();
    uint curr_time = oldtimeinseconds + QDateTime::currentDateTime().toTime_t() - laststart;
    ui->treeWidget->topLevelItem(runningtaskindex())->setText(coltime, timestring(curr_time));
}

/** @brief Save all tasks to the store
 *  @return Empty string for success or an error message.
 *
 * The function iterates over the tree widgets content and collects the
 * infomations of the tasks into a std::vector.
 * This vector is the argument for the Save() function of the store.
 */
QString MainWindow::save() {

    std::vector<task_t> v;
    for (int i = 0; i < ui->treeWidget->topLevelItemCount(); ++i) {
        task_t t;
        t.id = ui->treeWidget->topLevelItem(i)->text(coltaskid).toUInt();
        t.parent = 0;
        t.time = ui->treeWidget->topLevelItem(i)->text(coltime).toStdString();
        if (ui->treeWidget->topLevelItem(i)->icon(colcomplete).isNull())
            t.complete = false;
        else
            t.complete = true;
        v.push_back(t);
    }
    return QString(store->Save(v).c_str());
}

/** @brief Load the tasks from the store into the tree widget
 *  @return Empty string for success or an error message
 *
 * The store provides a std::vector of all tasks.
 * From the content of this vector the functions fills the tree widget
 */
QString MainWindow::load() {

    std::vector<task_t> tasks;
    QString err = QString(store->Load(tasks).c_str());
    if ("" != err)  return err;

    /* Lambda function for adding a task to the tree widget */
    auto add_task_func = [&] (task_t t) -> void {
        /* for each task add a new item to the tree widget */
        ui->treeWidget->addTopLevelItem(new QTreeWidgetItem(QStringList(QString())));
        /* fill the new item with task's id, name, time and "complete" */
        ui->treeWidget->topLevelItem(ui->treeWidget->topLevelItemCount()-1)->setText(coltaskid, QString::number(t.id));
        ui->treeWidget->topLevelItem(ui->treeWidget->topLevelItemCount()-1)->setText(coltaskname, store->GetTaskName(t.id).c_str());
        ui->treeWidget->topLevelItem(ui->treeWidget->topLevelItemCount()-1)->setText(coltime, QString(t.time.c_str()));
        if (t.complete)
            ui->treeWidget->topLevelItem(ui->treeWidget->topLevelItemCount()-1)->setIcon(colcomplete, qi_complete);
        else
            ui->treeWidget->topLevelItem(ui->treeWidget->topLevelItemCount()-1)->setData(colcomplete, Qt::DisplayRole,QVariant(" "));
        /** @todo (Frank Bergmann, 25.3.2014) Make the item editable ? */
        ui->treeWidget->topLevelItem(ui->treeWidget->topLevelItemCount()-1)->setFlags(ui->treeWidget->topLevelItem(ui->treeWidget->topLevelItemCount()-1)->flags()|Qt::ItemIsEditable);

    };
    for_each(tasks.begin(), tasks.end(), add_task_func);
    /* err should be an empty string */
    return err;
}

void MainWindow::on_btn_addtask_clicked()
{
    slotaddtask();
}

void MainWindow::on_btn_starttimer_clicked()
{
    slotstarttiming();
}

void MainWindow::on_btn_stoptimer_clicked()
{
    slotstoptiming();
}

void MainWindow::on_btn_deletetask_clicked()
{
    slotdeletetask();
}

void MainWindow::on_mousedoubleclick(QMouseEvent *e)
{
    if (ui->treeWidget->itemAt(e->x(),e->y())==0)
    {
        slotaddtask();
    }
}

void MainWindow::on_treeWidget_clicked(const QModelIndex &index)
{
    if (index.column()==colcomplete)
    {
        if (ui->treeWidget->currentItem()->icon(colcomplete).isNull())
        {
            ui->treeWidget->currentItem()->setIcon(colcomplete,qi_complete);
            ui->treeWidget->currentItem()->setData(colcomplete,Qt::DisplayRole,QVariant(" "));
        }
        else
        {
            ui->treeWidget->currentItem()->setIcon(colcomplete,QIcon());
            ui->treeWidget->currentItem()->setData(colcomplete,Qt::DisplayRole,QVariant());
        }
        save();
    }
}
