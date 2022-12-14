#include "rootdialog.h"
#include "ui_rootdialog.h"
#include "unistd.h"

//界面1：RootDialog::	主菜单，关机(pushButton_blur)
//界面2：MainWindow::	主界面
//界面3：Newconfiginfo::	工艺(stackedWidget_2::4)，历史(stackedWidget_2::3)，
//		系统设置(stackedWidget_2::2)，作业指导(stackedWidget_2::5)，关于(stackedWidget_2::8)，用户(stackedWidget_2::9)
//界面4：StepEdit::	步骤编辑
//界面5：CodeEdit::	编码设置

RootDialog::RootDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RootDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
    this->setGeometry(QRect(0, 0, 1366, 768));

    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpdate()));
    timer->start(1000);

    ui->label_wifi->hide();
    ui->label_black->hide();

    ui->label_4->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->label_5->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->label_7->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->label_9->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->label_10->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->label_11->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->label_14->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->label_15->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->label_16->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->label_17->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->label_18->setAttribute(Qt::WA_TransparentForMouseEvents);

    isLogin = false;
    isSystem = false;
    isProgram = false;
    isPdm = false;
    isHistory = false;
    isUser= false;
    vari1_r = "";
    connect(&timer_showdown,SIGNAL(timeout()),this,SLOT(battery15()));

//    tmpKey = blackKey;
    tmpKey = noKey;

    codeEdit = new CodeEdit;
//    QTimer::singleShot(0,codeEdit,SLOT(init()));
    connect(codeEdit,SIGNAL(sendKey(int)),this,SLOT(receiveKey(int)));
//    KeyRead *keyread = new KeyRead;
//    QTimer::singleShot(0,keyread,SLOT(init()));
//    connect(keyread,SIGNAL(sendKey(int)),this,SLOT(receiveKey(int)));

    stepEdit = new StepEdit;
    //stepeditbev = new stepeditbev;
    stepEditBev = new stepeditbev;
}

RootDialog::~RootDialog()
{
    delete ui;
}


//进主界面
void RootDialog::on_pushButton_clicked()
{
    if(isLogin || tmpKey != noKey || 1)
    {
        isLogin = false;
//        ui->label_user->setText("");
//        ui->pushButton_6->setStyleSheet("border-image: url(:/LCD_CS351/LCD_CS351/logo/Head.png);");
//        w->show();

        EnterWhich = "HOME";
        winManage();
    }
    else
    {
        if(!isPopups){
            e3 = new QGraphicsOpacityEffect(this);
            e3->setOpacity(0.5);
            ui->label_black->setGraphicsEffect(e3);
            ui->label_black->show();
            ui->label_black->setGeometry(0,0,1366,768);
            EnterWhich = "HOME";
            passwordPanel = new PasswordPanel(this);
            connect(passwordPanel,SIGNAL(sendResult(bool)),this,SLOT(receiveResult(bool)));
            isPopups = true;
            passwordPanel->show();
        }
    }

}

//系统设置
void RootDialog::on_pushButton_4_clicked()
{
    if(isLogin || tmpKey == redKey)
    {
//        c->systemConfigure();
//        c->show();
        EnterWhich = "System";
        winManage();
    }
    else
    {
        if(!isPopups){
            e3 = new QGraphicsOpacityEffect(this);
            e3->setOpacity(0.5);
            ui->label_black->setGraphicsEffect(e3);
            ui->label_black->show();
            ui->label_black->setGeometry(0,0,1366,768);
            EnterWhich = "System";
            passwordPanel = new PasswordPanel(this);
            connect(passwordPanel,SIGNAL(sendResult(bool)),this,SLOT(receiveResult(bool)));
            isPopups = true;
            passwordPanel->show();
        }
    }
}

//历史
void RootDialog::on_pushButton_13_clicked()
{
    if(isLogin || tmpKey != noKey || 1)
    {
//        c->history();
//        c->show();
        EnterWhich = "History";
        winManage();
    }
    else
    {
        if(!isPopups){
            e3 = new QGraphicsOpacityEffect(this);
            e3->setOpacity(0.5);
            ui->label_black->setGraphicsEffect(e3);
            ui->label_black->show();
            ui->label_black->setGeometry(0,0,1366,768);
            EnterWhich = "History";
            passwordPanel = new PasswordPanel(this);
            connect(passwordPanel,SIGNAL(sendResult(bool)),this,SLOT(receiveResult(bool)));
            isPopups = true;
            passwordPanel->show();
        }
    }
}


//关于
void RootDialog::on_pushButton_8_clicked()
{
    if(isLogin || tmpKey!= noKey || 1)
    {
//        c->on_pushButton_13_clicked();
//        c->show();
        EnterWhich = "About";
        winManage();
    }
    else
    {
        if(!isPopups){
            e3 = new QGraphicsOpacityEffect(this);
            e3->setOpacity(0.5);
            ui->label_black->setGraphicsEffect(e3);
            ui->label_black->show();
            ui->label_black->setGeometry(0,0,1366,768);
            EnterWhich = "About";
            passwordPanel = new PasswordPanel(this);
            connect(passwordPanel,SIGNAL(sendResult(bool)),this,SLOT(receiveResult(bool)));
            isPopups = true;
            passwordPanel->show();
        }
    }
}

//工艺
void RootDialog::on_pushButton_2_clicked()
{
    SaveWhat = "";

    if(isLogin || tmpKey ==greenKey || tmpKey == redKey)
    {
//        c->configList();
//        c->show();
        EnterWhich = "ConfigList";
        winManage();
    }
    else
    {
        if(!isPopups){
            e3 = new QGraphicsOpacityEffect(this);
            e3->setOpacity(0.5);
            ui->label_black->setGraphicsEffect(e3);
            ui->label_black->show();
            ui->label_black->setGeometry(0,0,1366,768);
            EnterWhich = "ConfigList";
            passwordPanel = new PasswordPanel(this);
            connect(passwordPanel,SIGNAL(sendResult(bool)),this,SLOT(receiveResult(bool)));
            isPopups = true;
            passwordPanel->show();
        }
    }
}

//作业指导
void RootDialog::on_pushButton_3_clicked()
{
    if(isLogin || tmpKey == greenKey || tmpKey == redKey)
    {
//        c->PDMEdit();
//        c->show();
        EnterWhich = "PDM";
        winManage();
    }
    else
    {
        if(!isPopups){
            e3 = new QGraphicsOpacityEffect(this);
            e3->setOpacity(0.5);
            ui->label_black->setGraphicsEffect(e3);
            ui->label_black->show();
            ui->label_black->setGeometry(0,0,1366,768);
            EnterWhich = "PDM";
            passwordPanel = new PasswordPanel(this);
            connect(passwordPanel,SIGNAL(sendResult(bool)),this,SLOT(receiveResult(bool)));
            isPopups = true;
            passwordPanel->show();
        }
    }

}
void RootDialog::timerUpdate()
{
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy-MM-dd hh:mm:ss");
    ui->label_date->setText(str);
//    qDebug()<<"*&*&*&*&*&*&*&**&*&*&*&*&*&*"<<vari1_r;
    if(vari1_r.mid(0,1) != "M")
    {
        codeEdit->readTimer.stop();
    }
}

void RootDialog::wifishow(bool wificonnect)
{
    if(wificonnect)
        ui->label_wifi->show();
    else
        ui->label_wifi->hide();
}

void RootDialog::batteryshow1(QString power)
{
    if(power == "17")
    {
        if(timer_showdown.isActive())
        {
            qDebug()<<"timer_showdown stop";
            timer_showdown.stop();
        }
        ui->label_battery->setStyleSheet("border-image: url(:/LCD_CS351/LCD_CS351/logo/battery2.png);background:transparent;");
    }
    else if(power == "16")
    {
        if(timer_showdown.isActive())
        {
            qDebug()<<"timer_showdown stop";
            timer_showdown.stop();
        }
        ui->label_battery->setStyleSheet("border-image: url(:/LCD_CS351/LCD_CS351/logo/battery1.png);background:transparent;");
    }
    else if(power == "05")
        ui->label_battery->setStyleSheet("border-image: url(:/LCD_CS351/LCD_CS351/logo/battery.png);background:transparent;");
    else if(power == "04")
        ui->label_battery->setStyleSheet("border-image: url(:/LCD_CS351/LCD_CS351/logo/battery_2.png);background:transparent;");
    else if(power == "03")
        ui->label_battery->setStyleSheet("border-image: url(:/LCD_CS351/LCD_CS351/logo/battery_red.png);background:transparent;");
    else if(power == "02"||power == "01")
    {
        //15 分钟后关机
        ui->label_battery->setStyleSheet("border-image: url(:/LCD_CS351/LCD_CS351/logo/battery_red.png);background:transparent;");
        timer_showdown.start(900000);
    }
}

void RootDialog::init(MainWindow *window, Newconfiginfo *newconfiginfo)
{
    w = window;
    c = newconfiginfo;
//    w->show();
}


//退出按键
void RootDialog::on_pushButton_11_clicked()
{
    //    if(isLogin)
    //    {

    //        e3 = new QGraphicsOpacityEffect(this);
    //        e3->setOpacity(0.5);
    //        ui->label_black->setGraphicsEffect(e3);
    //        fullScreenPixmap = QPixmap::grabWindow(QApplication::desktop()->winId());
    //        fullScreenPixmap.save("fullScreen.jpg","JPG");

    ////    或
    ////    fullScreenPixmap->save("Screenshot.png","png");
    pushButton_blur = new QPushButton(this);
    pushButton_blur->setFocusPolicy(Qt::NoFocus);
    //        pushButton_blur->setStyleSheet("background-image: url(fullScreen.jpg);");
    pushButton_blur->setStyleSheet("border-image: url(:/LCD_CS351/LCD_CS351/35_all/background.png);");

    //        e0 = new QGraphicsBlurEffect(this);
    //        e0->setBlurRadius(0.8);
    //        pushButton_blur->setGraphicsEffect(e0);
    pushButton_blur->show();
    pushButton_blur->setGeometry(0,0,1366,768);
    pushButton_reboot= new QPushButton(this);
    pushButton_reboot->setFocusPolicy(Qt::NoFocus);
    pushButton_reboot->setGeometry(844,284,200,200);
    pushButton_reboot->setText(tr("重新启动"));
    pushButton_reboot->setStyleSheet("border-style: solid;border-radius:20px;background-color: rgb(241, 156, 31); font: 20pt \"黑体\";color: rgb(248, 248, 255);");
    connect(pushButton_reboot,SIGNAL(clicked()),this,SLOT(reboot()));
    pushButton_poweroff= new QPushButton(this);
    pushButton_poweroff->setFocusPolicy(Qt::NoFocus);

    pushButton_poweroff->setGeometry(583,284,200,200);
    pushButton_poweroff->setText(tr("关闭电源"));
    pushButton_poweroff->setStyleSheet("border-style: solid;border-radius:20px;background-color: rgb(255, 102, 102); font: 20pt \"黑体\";color: rgb(248, 248, 255);");
    pushButton_poweroff->show();
    connect(pushButton_poweroff,SIGNAL(clicked()),this,SLOT(poweroff()));
    connect(pushButton_blur,SIGNAL(clicked()),this,SLOT(closeDialog()));
}

void RootDialog::reboot()
{
    qDebug() << "reboot here";
    system("reboot");
}

void RootDialog::poweroff()
{
    qDebug() << "poweroff here";
    system("echo 0 > /sys/class/leds/control_lvds/brightness");
    system("poweroff");
}

void RootDialog::closeDialog()
{
    pushButton_blur->hide();
    pushButton_reboot->hide();
    pushButton_poweroff->hide();
}

void RootDialog::winManage()
{
    isLogin = true;
    ui->pushButton_6->setStyleSheet("border-image: url(:/re/Administrator.png);");
    ui->label_user->setText("Admin");

//    qDebug()<<"winHiddenStatus:"<<c->isHidden()<<w->isHidden()<<codeEdit->isHidden()<<stepEdit->isHidden();
//    qDebug()<<"winVisibleStatus:"<<c->isVisible()<<w->isVisible()<<codeEdit->isVisible()<<stepEdit->isVisible();

    if(c->isVisible()){
//        c->hide();
        c->setWindowFlags(Qt::WindowStaysOnTopHint);
    }
    if(w->isVisible()){
//        w->hide();
        w->setWindowFlags(Qt::WindowStaysOnTopHint);
    }
    if(codeEdit->isVisible()){
        codeEdit->setWindowFlags(Qt::WindowStaysOnTopHint);
    }
    if(stepEdit->isVisible()){
        stepEdit->setWindowFlags(Qt::WindowStaysOnTopHint);
    }
    if(EnterWhich == "System")//系统设置
    {
        c->systemConfigure();
        c->show();
    }
    else if(EnterWhich == "History")//历史
    {
        c->history();
        c->show();
    }
    else if(EnterWhich == "ConfigList")//工艺
    {
        c->configList();
        c->show();
    }
    else if(EnterWhich == "PDM")//作业指导
    {
        c->PDMEdit();
        c->show();
    }
    else if(EnterWhich == "User")//用户
    {
        c->on_pushButton_100_clicked();
        c->show();
    }
    else if(EnterWhich == "HOME")//主菜单
    {
        isLogin = false;
        ui->label_user->setText("");
        ui->pushButton_6->setStyleSheet("border-image: url(:/LCD_CS351/LCD_CS351/logo/Head.png);");
        w->show();
    }
    else if(EnterWhich == "About")//关于
    {
        c->on_pushButton_13_clicked();
        c->show();
    }
    else if(EnterWhich == "Code")//编码设置
    {
        codeEdit->readTimer.stop();
        codeEdit->clearUi();
        codeEdit->show();
    }
    else if(EnterWhich == "Step")//步骤
    {
        stepEdit->show();
    }
    else if(EnterWhich == "StepBev")//步骤
    {
        stepEditBev->show();
    }

    EnterWhich = "";
}

void RootDialog::receiveResult(bool pass)
{
//    qDebug()<<"QApplication::activeWindow():"<<QApplication::activeWindow();
    ui->label_black->hide();
    delete e3;
    delete passwordPanel;
    isPopups = false;
    if(pass)
    {
        winManage();
    }
    EnterWhich = "";
}

void RootDialog::on_pushButton_6_clicked()
{

    if(!isLogin)
    {
        if(!isPopups){
            e3 = new QGraphicsOpacityEffect(this);
            e3->setOpacity(0.5);
            ui->label_black->setGraphicsEffect(e3);
            ui->label_black->show();
            ui->label_black->setGeometry(0,0,1366,768);
            EnterWhich = "";
            passwordPanel = new PasswordPanel(this);
            connect(passwordPanel,SIGNAL(sendResult(bool)),this,SLOT(receiveResult(bool)));
            isPopups = true;
            passwordPanel->show();
        }
    }
}


//注销
void RootDialog::on_pushButton_5_clicked()
{
    if(isLogin)
    {
        if(!isPopups){
            e3 = new QGraphicsOpacityEffect(this);
            e3->setOpacity(0.5);
            ui->label_black->setGraphicsEffect(e3);
            ui->label_black->show();
            ui->label_black->setGeometry(0,0,1366,768);
            SaveWhat = "Logout";
            save = new Save(this);
            connect(save,SIGNAL(sendLogout(bool)),this,SLOT(logout(bool)));
            isPopups = true;
            save->show();
        }
    }
    else
    {
        if(!isPopups){
            e3 = new QGraphicsOpacityEffect(this);
            e3->setOpacity(0.5);
            ui->label_black->setGraphicsEffect(e3);
            ui->label_black->show();
            ui->label_black->setGeometry(0,0,1366,768);
            SaveWhat = "noLogin";
            save = new Save(this);
            connect(save,SIGNAL(sendClose()),this,SLOT(closeSave()));
            isPopups = true;
            save->show();
        }
    }
}
void RootDialog::closeSave()
{
    ui->label_black->hide();
    delete e3;
    delete save;
    isPopups = false;
    SaveWhat = "";
    //    ISmaintenance = false;
    //    workmode = false;
}

void RootDialog::logout(bool isLogout)
{
    ui->label_black->hide();
    delete e3;
    delete save;
    isPopups = false;
    if(isLogout)
    {

        isLogin = false;
        ui->label_user->setText("");
        ui->pushButton_6->setStyleSheet("border-image: url(:/LCD_CS351/LCD_CS351/logo/Head.png);");
    }
    SaveWhat = "";
}

//用户
void RootDialog::on_pushButton_9_clicked()
{
    if(isLogin || tmpKey == redKey)
    {
//        c->on_pushButton_100_clicked();
//        c->show();
        EnterWhich = "User";
        winManage();
    }
    else
    {
        if(!isPopups){
            e3 = new QGraphicsOpacityEffect(this);
            e3->setOpacity(0.5);
            ui->label_black->setGraphicsEffect(e3);
            ui->label_black->show();
            ui->label_black->setGeometry(0,0,1366,768);
            EnterWhich = "User";
            passwordPanel = new PasswordPanel(this);
            connect(passwordPanel,SIGNAL(sendResult(bool)),this,SLOT(receiveResult(bool)));
            isPopups = true;
            passwordPanel->show();
        }
    }
}

void RootDialog::battery15()
{
    system("echo 0 > /sys/class/leds/control_lvds/brightness");  //关背光
    qDebug("power down 1");
    system("poweroff");
}


void RootDialog::receiveKey(int key)
{
    if(tmpKey != noKey)
    {
        if(c->isVisible())
            c->close();
        if(w->isVisible())
            w->close();
        emit sendKeyToStep(true);
    }
    else
    {
        emit sendKeyToStep(false);
    }
    tmpKey = key;
}

//编码设置
void RootDialog::on_pushButton_code_clicked()
{
    if(isLogin || tmpKey == redKey)
    {
//        codeEdit->readTimer.stop();
//        codeEdit->clearUi();
//        codeEdit->show();
        EnterWhich = "Code";
        winManage();
    }
    else
    {
        if(!isPopups){
            e3 = new QGraphicsOpacityEffect(this);
            e3->setOpacity(0.5);
            ui->label_black->setGraphicsEffect(e3);
            ui->label_black->show();
            ui->label_black->setGeometry(0,0,1366,768);
            EnterWhich = "Code";
            passwordPanel = new PasswordPanel(this);
            connect(passwordPanel,SIGNAL(sendResult(bool)),this,SLOT(receiveResult(bool)));
            isPopups = true;
            passwordPanel->show();
        }
    }
}

//步骤
void RootDialog::on_pushButton_step_clicked()
{
    if(isLogin || tmpKey ==greenKey || tmpKey == redKey)
    {
//        stepEdit->show();
        EnterWhich = "Step";
        winManage();
    }
    else
    {
        if(!isPopups){
            e3 = new QGraphicsOpacityEffect(this);
            e3->setOpacity(0.5);
            ui->label_black->setGraphicsEffect(e3);
            ui->label_black->show();
            ui->label_black->setGeometry(0,0,1366,768);
            EnterWhich = "Step";
            passwordPanel = new PasswordPanel(this);
            connect(passwordPanel,SIGNAL(sendResult(bool)),this,SLOT(receiveResult(bool)));
            isPopups = true;
            passwordPanel->show();
        }
    }
}

