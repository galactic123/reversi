#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QRect rec;
    rec.setTopLeft(QPoint(0,0));
    rec.setBottomRight(QPoint(this->width(),this->height()));
    QPixmap pixmap;
    pixmap.load(bg_name);
    painter.drawPixmap(rec,pixmap);
    QPen pen1;
    pen1.setColor(Qt::red);
    pen1.setStyle(Qt::SolidLine);
    pen1.setWidth(3);
    painter.setPen(pen1);
    for(int i=0;i<9;i++)
    {
        painter.drawLine(startX,startY+i*gridhight,9*gridwith,startY+i*gridhight);
        painter.drawLine(startX+i*gridwith,startY,startX+i*gridwith,9*gridhight);
    }
    QString blackgrid = "../mychess/img/black.png";
    QString whilegrid = "../mychess/img/white.png";
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            if(chessmap[i][j]==1)//白棋
            {
                painter.drawPixmap(startX+i*gridwith,startY+j*gridhight,gridwith,gridhight,QPixmap(whilegrid));
            }
            else if(chessmap[i][j]==-1)//黑棋
            {
                painter.drawPixmap(startX+i*gridwith,startY+j*gridhight,gridwith,gridhight,QPixmap(blackgrid));
            }
            else
            {
                continue;
            }
        }
    }
//    painter.drawPixmap(startX,startY,gridwith,gridhight,QPixmap("../mychess/img/black.png"));
}
void MainWindow::resizeEvent(QResizeEvent *event)
{
    gridwith = event->size().width()/10;
    gridhight = event->size().height()/10;
    startX = gridwith;
    startY = gridhight;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    int x = event->x();
    int y = event->y();
//    int color = 1;
    if(x>=startX&&x<=startX+8*gridwith&&y>=startY&&y<=startY+8*gridhight)
    {
        int nowx = (x-startX)/gridwith;
        int nowy = (y-startY)/gridhight;
//        qDebug()<<nowx<<nowy;
//        chessmap[nowx][nowy] = 1;
        if(chessmap[nowx][nowy]!=0)return;
        int result = num_judge(nowx,nowy,gridcolor);
        emit sendresultdata(result);
        if(result!=0)
        {
            num_judge(nowx,nowy,gridcolor,1);
            chessmap[nowx][nowy] = gridcolor;
            gridcolor*=-1;


        }
        int blacknum = 0,whitenum = 0;
        for(int i=0;i<8;i++)
        {
            for(int j=0;j<8;j++)
            {
                if(chessmap[i][j]==1)
                {
                    whitenum++;
                }
                if(chessmap[i][j]==-1)
                {
                    blacknum++;
                }
            }
        }
        emit sendstasticdata(blacknum,whitenum);
        memset(change,0,sizeof(int)*8);
        update();
    }
}
void MainWindow::init()
{
    bg_name.clear();
    bg_name = "../mychess/img/bg.jpg";
    memset(chessmap,0,sizeof(int)*64);
    chessmap[4][4] = chessmap[3][3] = 1;
    chessmap[4][3] = chessmap[3][4] = -1;
    memset(change,0,sizeof(int)*8);
    gridcolor = -1;
}
int MainWindow::num_judge(int x,int y,int color,bool ischange)
{
    int ans = 0;
//    qDebug()<<"2e";
    int px = x,py = y;
    int cnt = 0;
    int tmpmap[8][8];
    memset(tmpmap,0,sizeof (tmpmap));
    while(px>=0&&px<8&&py>=0&&py<8)
    {
        px++;
        if(!(px>=0&&px<8&&py>=0&&py<8))break;
//        qDebug()<<chessmap[px][py];
        if(chessmap[px][py]==color*(-1))
        {
            cnt++;
            if(change[0]&&ischange)tmpmap[px][py] = color;
        }
        else if(chessmap[px][py]==color){
            if(cnt)change[0] = 1;
//            qDebug()<<cnt;
            break;

        }
        else{
            cnt = 0;
            break;
        }
    }

    ans+=cnt;
    px = x,py = y;
    cnt = 0;
    while(px>=0&&px<8&&py>=0&&py<8)
    {
        px--;
        if(!(px>=0&&px<8&&py>=0&&py<8))break;
//        qDebug()<<chessmap[px][py];
        if(chessmap[px][py]==color*(-1))
        {
            cnt++;if(change[1]&&ischange)tmpmap[px][py] = color;
        }
        else if(chessmap[px][py]==color){
//            qDebug()<<cnt;
            break;

        }
        else{
            cnt = 0;
            break;
        }
    }
    if(cnt)change[1] = 1;
    ans+=cnt;
    px = x,py = y;
    cnt = 0;
    while(px>=0&&px<8&&py>=0&&py<8)
    {
        py--;
        if(!(px>=0&&px<8&&py>=0&&py<8))break;
//        qDebug()<<chessmap[px][py];
        if(chessmap[px][py]==color*(-1))
        {
            cnt++;if(change[2]&&ischange)tmpmap[px][py] = color;
        }
        else if(chessmap[px][py]==color){
//            qDebug()<<cnt;
            break;

        }
        else{
            cnt = 0;
            break;
        }
    }
     if(cnt)change[2] = 1;
    ans+=cnt;
    px = x,py = y;
    cnt = 0;
    while(px>=0&&px<8&&py>=0&&py<8)
    {
        py++;
        if(!(px>=0&&px<8&&py>=0&&py<8))break;
//        qDebug()<<chessmap[px][py];
        if(chessmap[px][py]==color*(-1))
        {
            cnt++;if(change[3]&&ischange)tmpmap[px][py] = color;
        }
        else if(chessmap[px][py]==color){
//            qDebug()<<cnt;
            if(cnt)change[3] = 1;
            break;

        }
        else{
            cnt = 0;
            break;
        }
    }

    ans+=cnt;
    px = x,py = y;
    cnt = 0;
    while(px>=0&&px<8&&py>=0&&py<8)
    {
        py++,px++;
        if(!(px>=0&&px<8&&py>=0&&py<8))break;

        if(chessmap[px][py]==color*(-1))
        {
            cnt++;if(change[4]&&ischange)tmpmap[px][py] = color;
        }
        else if(chessmap[px][py]==color){
//            qDebug()<<cnt;
            if(cnt)change[4] = 1;
            break;

        }
        else{
            cnt = 0;
            break;
        }
    }

    ans+=cnt;
    px = x,py = y;
    cnt = 0;
    while(px>=0&&px<8&&py>=0&&py<8)
    {
        py--,px--;
        if(!(px>=0&&px<8&&py>=0&&py<8))break;
//        qDebug()<<chessmap[px][py];
        if(chessmap[px][py]==color*(-1))
        {
            cnt++;if(change[5]&&ischange)tmpmap[px][py] = color;
        }
        else if(chessmap[px][py]==color){
//            qDebug()<<cnt;
            if(cnt)change[5] = 1;
            break;

        }
        else{
            cnt = 0;
            break;
        }
    }

    ans+=cnt;
    px = x,py = y;
    cnt = 0;
    while(px>=0&&px<8&&py>=0&&py<8)
    {
        py++,px--;
        if(!(px>=0&&px<8&&py>=0&&py<8))break;
//        qDebug()<<chessmap[px][py];
        if(chessmap[px][py]==color*(-1))
        {
            cnt++;if(change[6]&&ischange)tmpmap[px][py] = color;
        }
        else if(chessmap[px][py]==color){
//            qDebug()<<cnt;
            if(cnt)change[6] = 1;
            break;

        }
        else{
            cnt = 0;
            break;
        }
    }

    ans+=cnt;
    px = x,py = y;
    cnt = 0;
    while(px>=0&&px<8&&py>=0&&py<8)
    {
        py--,px++;
        if(!(px>=0&&px<8&&py>=0&&py<8))break;
//        qDebug()<<chessmap[px][py];
        if(chessmap[px][py]==color*(-1))
        {
            cnt++;if(change[7]&&ischange)tmpmap[px][py] = color;
        }
        else if(chessmap[px][py]==color){
//            qDebug()<<cnt;
            if(cnt)change[7] = 1;
            break;

        }
        else{
            cnt = 0;
            break;
        }
    }

    ans+=cnt;
    if(ischange)
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            if(tmpmap[i][j]!=0)
            {
                chessmap[i][j] = tmpmap[i][j];
            }
        }
    }
    return ans;
}
