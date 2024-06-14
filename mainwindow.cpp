#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    li = 1;
    ls = 12;
    band = false;
    timer = new QTimer();

    connect(timer, SIGNAL(timeout()), this, SLOT(repaint()));
    ui->statusbar->addPermanentWidget(ui->label,1);
    ui->statusbar->addPermanentWidget(ui->label_2,2);
    ui->statusbar->addPermanentWidget(ui->label_3);

}

MainWindow::~MainWindow()
{
    delete ui;


}

void MainWindow::keyPressEvent(QKeyEvent *evento)
{
    if(evento->key() == Qt::Key_I)
    {
        band = true;
        timer->start(100);
        update();
    }
    if(evento->key() == Qt::Key_D)
    {
        timer->stop();
    }
    if(evento->key() == Qt::Key_S)
        close();

}

void MainWindow::dragon(int limite, QPainter *canvas)
{
    int i;
    paso = 4096;

    signo = -1;

    EjeX[1] = canvas->window().width()/4;
    EjeX[4097] = 3 * canvas->window().width()/4;
    EjeY[1] = EjeY[4097] = 2 * canvas->window().height()/3;
    canvas->setPen(QColor(50,50,200));
    QFont fuente = canvas->font();
    fuente.setPointSize(fuente.pointSize()*2);
    canvas->setFont(QFont("RockWell",22));

    canvas->drawText(5,25,"CURVA FRACTAL DEL DRAGON");

    //investigar global
    canvas->setPen(QColor(0,QRandomGenerator::global()->bounded(100)+155,QRandomGenerator::global()->bounded(100)+155));
    canvas->drawLine(EjeX[1], EjeY[1], EjeX[4097], EjeY[4097]);

    for(i =1; i<=limite; i++)
    {
      generarDragon(canvas);
      paso /= 2;
    }

}

void MainWindow::paintEvent(QPaintEvent *e)
{
    QPainter *canvas = new QPainter(this);
    if(band)
    {
        if(li <= ls)
        {
            dragon(li,canvas);
            li++;
        }
        else

            band = false;

    }
    if(!band)
    {
        li--;
        dragon(li,canvas);
        if(li ==0)
            band = true;
    }
    canvas->end();

}

void MainWindow::generarDragon(QPainter *Canvas)
{
    int i,j,dx,dy;
    j=paso/2;
    Canvas->setPen(QColor(0,QRandomGenerator::global()->bounded(100)+155,QRandomGenerator::global()->bounded(100)+155));
    for(i=1;i<= 4096; i+=paso)
    {
        dx = EjeX[paso + i] - EjeX[i];
        dy = EjeY[paso + i] - EjeY[i];

        signo *=-1;
        //signo = 1;


        EjeX[i + j] = EjeX[i] + (dx + (dy * signo))/2;
        EjeY[i + j] = EjeY[i] + (dy - (dx * signo))/2;

        Canvas->drawLine(EjeX[i],EjeY[i], EjeX[i+j],EjeY[i+j]);
        Canvas->drawLine(EjeX[i+j],EjeY[i+j], EjeX[i+paso],EjeY[i+paso]);
    }
}

void MainWindow::linea_DDa(int x1, int y1, int x2, int y2)
{
    int dx,dy,steps,k;
    float x_inc, y_inc,x,y;
    dx = x2 - x1;
    dy = y2 - y1;

    if(abs(dx) > abs(dy))
        steps = abs(dx);
    else
        steps = abs(dy);
    x_inc = (float)dx/steps;
    y_inc = (float)dy/steps;
    x=x1;
    y=y1;
    //pulpixel(floor(x), floor(y),1);
    for(k=1; k< steps+1; k++)
    {
        x= x+x_inc;
        y= y+y_inc;
        //pulpixel(floor(x), floor(y),1)
    }
}

//utilizar la linea dda con el fractal dragon













