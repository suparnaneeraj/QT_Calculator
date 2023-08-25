#include "mainwindow.h"
#include "ui_mainwindow.h"

double calcValue=0.0;
bool divTrigger=false;
bool mulTrigger=false;
bool addTrigger=false;
bool subTrigger=false;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Display->setText(QString::number(calcValue));
    QPushButton *numButtons[10];
    for(int i=0;i<10;i++)
    {
        QString buttonName="Button"+QString::number(i);
        numButtons[i]=MainWindow::findChild< QPushButton *>(buttonName);
        connect(numButtons[i],SIGNAL(released()),this,SLOT(NumButtonPressed()));
    }
    connect(ui->Addition,SIGNAL(released()),this,SLOT(MathButtonPressed()));
    connect(ui->Subtract,SIGNAL(released()),this,SLOT(MathButtonPressed()));
    connect(ui->Division,SIGNAL(released()),this,SLOT(MathButtonPressed()));
    connect(ui->Multiply,SIGNAL(released()),this,SLOT(MathButtonPressed()));
    connect(ui->Equals,SIGNAL(released()),this,SLOT(EqualButton()));
    connect(ui->Clear,SIGNAL(released()),this,SLOT(ClearButtonPressed()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::NumButtonPressed()
{
    QPushButton *button=(QPushButton*)sender();
    QString butVal=button->text();
    QString displayVal= ui->Display->text();
    if((displayVal.toDouble()==0)||(displayVal.toDouble()==0.0))
    {
        ui->Display->setText(butVal);
    }
    else
    {
        QString newVal=displayVal+butVal;
        double dblNewVal=newVal.toDouble();
        ui->Display->setText(QString::number(dblNewVal,'g',160));
    }
}

void MainWindow::MathButtonPressed()
{
    divTrigger=false;
    mulTrigger=false;
    addTrigger=false;
    subTrigger=false;
    QString displayValue=ui->Display->text();
    calcValue=displayValue.toDouble();
    QPushButton *buttonPressed=(QPushButton*)sender();
    QString butVal=buttonPressed->text();
    if(QString::compare(butVal,"/",Qt::CaseInsensitive)==0)
    {
        divTrigger=true;
    }
    else if(QString::compare(butVal,"*",Qt::CaseInsensitive)==0)
    {
        mulTrigger=true;
    }
    else if(QString::compare(butVal,"+",Qt::CaseInsensitive)==0)
    {
        addTrigger=true;
    }
    else if(QString::compare(butVal,"-",Qt::CaseInsensitive)==0)
    {
        subTrigger=true;
    }
    ui->Display->setText("");
}

void MainWindow::EqualButton()
{
    double solution=0.0;
    QString displayValue=ui->Display->text();
    double displayVal=displayValue.toDouble();
    if(divTrigger)
    {
        solution=calcValue/displayVal;
    }
    else if(mulTrigger)
    {
        solution=calcValue*displayVal;
    }
    else if(addTrigger)
    {
        solution=calcValue+displayVal;
    }
    else
    {
        solution=calcValue-displayVal;
    }
    ui->Display->setText(QString::number(solution));
}

void MainWindow::ClearButtonPressed()
{
    ui->Display->setText("");
}


