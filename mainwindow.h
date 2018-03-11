#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRegExp>
#include <QRegExpValidator>
#include <QDebug>
#include <qmath.h>
#include <QMessageBox>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QPixmap>
#include "myDelegate.h"


#define myRound(a, b) qRound(a*pow(10, b))/pow(10, b)

namespace Ui {
class MainWindow;
}

#define pi 3.14
#define SIO2 "SiO2"
#define LINBO3 "LiNbO3"

typedef enum {
    InputData,
    InputConv,
    OutputConv,
    SizeConv,
    Finish
}State;

typedef enum {
    SiO2,  //кварц
    LiNbO3, // ниобат лития
    LiTaO3, // танталант лития
    LiIO3,  // йодат лития
    Bi4Ge3O12, //германат висмута
    Bi12SiO20 // силикат висмута
}Material;

typedef enum {
    equidistant_not_apodized,
    equidistant_apodized,
    not_equidistant_apodized,
}TypeConverter;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_horizontalSlider_3_valueChanged(int value);

    void on_horizontalSlider_2_valueChanged(int value);

    void on_horizontalSlider_valueChanged(int value);

    void on_pushButton_2_clicked();

    void slotEnableOk();



    void on_spinBox_4_valueChanged(int arg1);

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    State myState;

    TypeConverter type;
    Material myMaterial;
    float V;


    uint CFreq;
    qreal dFreqPer;
    qreal dFreq;
    uint m;
    qreal L1, L2, L3;

    uint inN;
    qreal upFreq;
    qreal downFreq;
    qreal Lamda;
    qreal h;
    qreal d;
    qreal W;

    qreal outN;
    QList<qreal> Hn;
    QList<qreal> Wn;
    QList<qreal> Fn;
    QList<qreal> Yn;

    qreal Lin;
    qreal L4;
    qreal Lout;
    qreal Ld;  //длина звукопровода
    qreal Lw; //ширина звукопровода
    qreal Lh; //толщина звукопровода

    QDialog *helpDialog;


    void calculationfilter();
    qreal func_apodiz(int n);
    void selectMaterial(double per);
    QString strMaterial(Material m);

    bool checkInputConv();
    bool checkOutputConv();
    bool checkSizeConv();

};

#endif // MAINWINDOW_H
