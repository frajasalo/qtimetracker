#include <QInputDialog>
#include <QDateTime>
#include <QFile>
#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "taskdialog.h"

/*
  A task is marked as running using column 3. Column 3 holds the time when the task was started if it is running.
  Column 4 holds the time of the task when it was started.
  */

// watches (c) 2000 by blacky, see http://websvn.kde.org/trunk/KDE/kdepim/ktimetracker/pics/watch-0.xpm?view=log
static char * watch_0_xpm[] = {
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
static char * watch_1_xpm[] = {
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
static char * watch_2_xpm[] = {
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
static char * watch_3_xpm[] = {
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
static char * watch_4_xpm[] = {
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
static char * watch_5_xpm[] = {
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
static char * watch_6_xpm[] = {
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
static char * watch_7_xpm[] = {
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
    running_task_item(NULL),
    base_dir(NULL)
{
    ui->setupUi(this);
    getOptions();
    load();
    prepareicons();
    timer=new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(slottimer()));
    ui->treeWidget->resizeColumnToContents(0);
    ui->treeWidget->header()->resizeSection(1,20);
    ui->treeWidget->header()->resizeSection(2,50);
    ui->treeWidget->setColumnCount(5);
    ui->treeWidget->setColumnHidden(3,true);
    ui->treeWidget->setColumnHidden(4,true);
    QTreeWidgetItem *item1 = ui->treeWidget->headerItem();
    item1->setText(1, tr(""));
    item1->setText(2, tr("time (hh:mm:ss)"));
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

/** \brief Get the base directory for working with
 *
 * This functions fills the member base_dir with the directory we will use.
 * Typically this will be the directory '.qtt' in the home directory.
 * If we can't detect the home directory or won't be able to create '.qtt'
 * we use the current directory.
 */
void MainWindow::getBaseDir(void) {

    /* determine the users home dir; the path should be larger then 4 characters (C:\ under win) */
    if (3 >= QDir::homePath().length()) {
        base_dir = new QDir(QDir().current());
        return;
    }

#ifdef  Q_OS_WIN
    QString app_dir("Qtt");
#else
    QString app_dir(".qtt");
#endif
    base_dir = new QDir(QDir().home());
    if (!base_dir->cd(app_dir)) {
        /* does not exist, create one */
        if (!base_dir->mkdir(app_dir)) {
            ui->statusBar->showMessage(QString(tr("WRN: unable to make dir: ")).append(base_dir->absolutePath()).append(QString("/")).append(app_dir), 20000);
            /* fall back to current dir */
            base_dir = new QDir(QDir().current());
            return;
        }

        if (!base_dir->cd(app_dir)) {
            /* something went strange: we created the dir but can not change into it */
            ui->statusBar->showMessage(QString(tr("can not change into dir: ")).append(base_dir->absolutePath()).append(QString("/")).append(app_dir), 20000);
            /* fall back to current dir */
            base_dir = new QDir(QDir().current());
            return;
        }

        ui->statusBar->showMessage(QString(tr("created new dir: ")).append(base_dir->absolutePath()), 10000);
    }

    /* test if the selected dir is not writable for us */
    QFileInfo wrtest(base_dir->absolutePath());
    if (!wrtest.isWritable())
        base_dir = new QDir(QDir().current());
}

/** \brief Extract the options for runtime
 *
 * For the moment parse the command line arguments of the programm for the
 * known options:
 * -p - use the current dir as "project" dir and load and save the "times"-file
 *      from it.
 */
void MainWindow::getOptions(void) {

    QStringList cmd_line_args = QCoreApplication::arguments();
    for (int i = 0; i < cmd_line_args.length(); ++i) {
        /* -p - project dir option */
        if ("-p" == cmd_line_args.at(i)) {
            /* use the current dir as "project" directory */
            base_dir = new QDir(QDir().current());
        }
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
        if (!ui->treeWidget->topLevelItem(i)->text(3).isEmpty()) result=i;
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
    if (taskdialog->hasaccepted()) {
        QTreeWidgetItem *tree_task = new QTreeWidgetItem(QStringList(taskdialog->text()));
        tree_task->setText(2, "00:00:00");
        tree_task->setText(3, QDateTime::currentDateTime().toString());
        tree_task->setText(4, "00:00:00");
        ui->treeWidget->addTopLevelItem(tree_task);
    }
    save();
    ui->treeWidget->resizeColumnToContents(0);
}

void MainWindow::slotstarttiming()
{
    if (ui->treeWidget->currentItem())
    {
        if (!running_task_item) {
            running_task_item = ui->treeWidget->currentItem();
            running_task_item->setIcon(1, qi_watch[0]);
            running_task_item->setText(3, QDateTime::currentDateTime().toString());
            running_task_item->setText(4, running_task_item->text(2));
            timer->start(1000);
        }
        /* silently ignore action if a task already running */
    }
    else QMessageBox::information(0,"Info","First select a task that you want to start timing for.");
}

int timestringtoseconds(QString timestring)
{
    QTime qtime1=QTime::fromString(timestring);
    return qtime1.hour()*3600+qtime1.minute()*60+qtime1.second();
}

QString timestring(int seconds)
{
    return QTime((int)(seconds/3600),(int)(seconds/60),seconds%60).toString();
}

void MainWindow::slotstoptiming()
{
    if (running_task_item)
    {
        if (!running_task_item->text(3).isEmpty())
        { // task is really running
            timer->stop();
            running_task_item->setIcon(1,QIcon());
            running_task_item->setText(3,QString()); // mark task as not running
        }
        save();
        running_task_item = NULL;
    }
}

void MainWindow::slotdeletetask()
{
    slotstoptiming();
    delete(ui->treeWidget->currentItem());
    save();
}

void MainWindow::slottimer()
{
    if (running_task_item) {
        static int turn=0;
        if (++turn>=8) turn-=8;
        running_task_item->setIcon(1,qi_watch[turn]);
        QString last_time_sum = running_task_item->text(4);
        QString start_time_str = running_task_item->text(3);
        running_task_item->setText(2,timestring(timestringtoseconds(last_time_sum) + QDateTime::fromString(start_time_str).secsTo(QDateTime::currentDateTime())));
    }
}

QString MainWindow::save()
{
    QString err;
    int i;
    if (!base_dir)  getBaseDir();
    QFile file1(base_dir->filePath("qtimetracker.txt"));
    if (!file1.open(QIODevice::Truncate | QIODevice::WriteOnly | QIODevice::Text)) err=QString("Could not open file");
    else
    {
        for (i=0; i<ui->treeWidget->topLevelItemCount(); i=i+1)
        {
            file1.write(ui->treeWidget->topLevelItem(i)->text(0).append("\n").toUtf8());
            file1.write(ui->treeWidget->topLevelItem(i)->text(2).append("\n").toUtf8());
        }
        file1.close();
        ui->statusBar->showMessage(QString("saved tasks:").append(QString::number((double)i)));
    }
    return err;
}

QString MainWindow::load()
{
    QString err;

    if (!base_dir)  getBaseDir();
    QFile file1(base_dir->filePath("qtimetracker.txt"));
    if (!file1.open(QIODevice::ReadOnly | QIODevice::Text)) err=QString("Could not open file");
    else
    {
        QByteArray line;
        int i=0;
        while (!file1.atEnd())
        {
            line=file1.readLine();
            line.replace("\n","");
            ui->treeWidget->addTopLevelItem(new QTreeWidgetItem(QStringList(QString(line))));
            line=file1.readLine();
            line.replace("\n","");
            ui->treeWidget->topLevelItem(ui->treeWidget->topLevelItemCount()-1)->setText(2,line);
            i++;
        }
        file1.close();
    }
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
