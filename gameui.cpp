#include "gameui.h"
#include "ui_gameui.h"

gameUI::gameUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gameUI)
{
    ui->setupUi(this);
    init();
}

gameUI::~gameUI()
{
    delete ui;
}

void gameUI::init()
{
   chess = new MainWindow();
//   chess->chessmap[0][0] = 1;
   QPushButton* restart = ui->restart;
   connect(restart,SIGNAL(clicked()),this,SLOT(restart_click()));

   ui->gridLayout->addWidget(chess);

   connect(chess,SIGNAL(sendresultdata(int)),this,SLOT(reciveresultdata(int)));
   connect(chess,SIGNAL(sendstasticdata(int,int)),this,SLOT(recivestasticdata(int,int)));
}
void gameUI::restart_click()
{
    chess->init();
    chess->update();
}
void gameUI::reciveresultdata(int res)
{
    if(!res)
    {
        ui->textEdit_3->setText(QString("非法放置"));
    }
    else{
        ui->textEdit_3->setText(QString("已经放置"));
    }
}
void gameUI::recivestasticdata(int black,int white)
{
    ui->textEdit->setText(QString::number(black));
    ui->textEdit_2->setText(QString::number(white));

    if(black+white==64)
    {
        if(black>white)
        {
            ui->textEdit_3->setText(QString("黑胜"));
        }
        else if(white>black)
        {
            ui->textEdit_3->setText("白胜");
        }
        else{
            ui->textEdit_3->setText("平局");
        }
    }
}
