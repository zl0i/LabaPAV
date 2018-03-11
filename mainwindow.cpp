#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/pavIcon/icon.png"));
    QRegExp exp("[1-9]{1,3}[.]{0,1}[0-9]{0,2}");
    ui->lineEdit->setValidator(new QRegExpValidator(exp, this));
    ui->lineEdit_2->setValidator(new QRegExpValidator(exp, this));
    ui->lineEdit_3->setValidator(new QRegExpValidator(exp, this));
    ui->lineEdit_4->setValidator(new QRegExpValidator(exp, this));
    ui->lineEdit_5->setValidator(new QRegExpValidator(exp, this));
    ui->lineEdit_6->setValidator(new QRegExpValidator(exp, this));
    ui->lineEdit_7->setValidator(new QRegExpValidator(exp, this));
    ui->lineEdit_8->setValidator(new QRegExpValidator(exp, this));
    ui->lineEdit_9->setValidator(new QRegExpValidator(exp, this));
    ui->lineEdit_10->setValidator(new QRegExpValidator(exp, this));
    LineNoEditDelegate *dlg = new LineNoEditDelegate(this);
    ui->tableWidget->setItemDelegateForColumn(0, dlg);
    LineEditDoubleDelegate *dlg_2 = new LineEditDoubleDelegate(this);
    ui->tableWidget->setItemDelegateForColumn(1, dlg_2);
    ui->tableWidget->setItemDelegateForColumn(2, dlg_2);
    ui->tableWidget->setItemDelegateForColumn(3, dlg_2);
    ui->tableWidget->setItemDelegateForColumn(4, dlg_2);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
     ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    setWindowTitle("Лабораторная работа №1 Расчет фильтра на ПАВ");
    ui->statusBar->showMessage("Разработал студент группы РП-142 Попов Д. А.");
    QPixmap pix(":/pavIcon/pav.png");
    ui->label_28->setScaledContents(true);
    ui->label_40->setScaledContents(true);
    ui->label_28->setPixmap(pix);

    ui->lineEdit->setText("160");
    ui->doubleSpinBox->setValue(50);
    ui->spinBox_2->setValue(4);

    L1 = 8.0/1000.0;
    L2 = 5.0/1000.0;
    L3 = 5.0/1000.0;
    ui->stackedWidget->setCurrentIndex(0);
    ui->stackedWidget_2->setCurrentIndex(0);
    ui->pushButton_2->setEnabled(false);
    myState = InputData;
    connect(ui->lineEdit_2, SIGNAL(textEdited(QString)), this, SLOT(slotEnableOk()));
    connect(ui->lineEdit_3, SIGNAL(textEdited(QString)), this, SLOT(slotEnableOk()));
    connect(ui->lineEdit_4, SIGNAL(textEdited(QString)), this, SLOT(slotEnableOk()));
    connect(ui->lineEdit_5, SIGNAL(textEdited(QString)), this, SLOT(slotEnableOk()));
    connect(ui->lineEdit_6, SIGNAL(textEdited(QString)), this, SLOT(slotEnableOk()));
    connect(ui->lineEdit_7, SIGNAL(textEdited(QString)), this, SLOT(slotEnableOk()));
    connect(ui->lineEdit_8, SIGNAL(textEdited(QString)), this, SLOT(slotEnableOk()));
    connect(ui->lineEdit_9, SIGNAL(textEdited(QString)), this, SLOT(slotEnableOk()));
    connect(ui->lineEdit_10, SIGNAL(textEdited(QString)), this, SLOT(slotEnableOk()));
    connect(this, SIGNAL(destroyed(QObject*)), this, SLOT(close()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked() //далее
{

    if(myState == InputData) {
        if(ui->lineEdit->text() == 0) {
            QMessageBox::critical(this, "Ошибка", "Введите центральную частоту");
            return;
        }
        calculationfilter();
        ui->stackedWidget_2->setCurrentIndex(1);
        QPixmap pix(":/pavIcon/InputConv.png");
        ui->label_40->setGeometry(0, 0, pix.width()>650 ? 650:pix.width() , pix.height()>390 ? 390:pix.height());
        ui->label_40->setPixmap(pix);
        ui->pushButton_2->setEnabled(true);
        ui->stackedWidget->setCurrentIndex(1);
        myState = InputConv;
        //slotEnableOk();
        return;
    }
    if(myState == InputConv) {
        //if(!checkInputConv()) return;
        //helpDialog->close();
        QPixmap pix(":/pavIcon/OutputConv.png");
        ui->label_40->setGeometry(0, 0, pix.width()>650 ? 650:pix.width() , pix.height()>390 ? 390:pix.height());
        ui->label_40->setPixmap(pix);
        ui->stackedWidget->setCurrentIndex(2);
        myState = OutputConv;
        return;
    }
    if(myState == OutputConv) {
        //if(!checkOutputConv()) return;
        //helpDialog->close();
        QPixmap pix(":/pavIcon/SizeConv.png");
        ui->label_40->setGeometry(0, 0, pix.width()>650 ? 650:pix.width() , pix.height()>390 ? 390:pix.height());
        ui->label_40->setPixmap(pix);
        ui->stackedWidget->setCurrentIndex(3);
        myState = SizeConv;
        //slotEnableOk();
        return;
    }
    if(myState == SizeConv) {
        //if(!checkSizeConv()) return;
        //helpDialog->close();
        ui->label_40->clear();
        ui->stackedWidget->setCurrentIndex(4);
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
        ui->pushButton->setText("Закрыть");
        connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(close()));
        ui->stackedWidget_2->setCurrentIndex(1);
        myState = Finish;
        return;
    }
}



qreal MainWindow::func_apodiz(int n) {
    qreal x = (pi*n)/(outN+1);
    switch (ui->spinBox_3->value()) {
        case 1:
            return 1+0.8*cos(x);
        case 2:
            return pow(sin(x)/x, 1);
        case 3:
            return pow(sin(x)/x, 2);;
        case 4:
            return pow(sin(x)/x, 3);;
        case 5:
            return pow(cos(x/2), 1);
        case 6:
            return pow(cos(x/2), 2);
        case 7:
            return pow(cos(x/2), 3);
        case 8:
            return 0.5*(1 + cos(x));
    }
    return 0;
}


void MainWindow::selectMaterial(double per) {
    if(per == 5.3) {
        myMaterial = SiO2;
        V = 3159;
    }
    if(per == 4.6) {
        myMaterial = SiO2;
        V = 3158;
    }
    if(per == 5.6) {
        myMaterial = SiO2;
        V = 3158;
    }
    if(per == 50) {
        myMaterial = LiNbO3;
        V = 4000;
    }
    type = equidistant_apodized;
}



QString MainWindow::strMaterial(Material m) {
    switch (m) {
        case SiO2:
            return "SiO2";
        case LiNbO3:
             return "LiNbO3";
        case LiTaO3:
            return "LiTaO3";
        case LiIO3:
            return "LiIO3";
        case Bi4Ge3O12:
            return "Bi4Ge3O12";
        case Bi12SiO20:
            return "Bi12SiO20";
        default:
            return "nan";
    }
}


void MainWindow::calculationfilter() {
    CFreq = ui->lineEdit->text().toInt()*1000000;
    dFreqPer = ui->doubleSpinBox->value();
    dFreq = CFreq * dFreqPer/100;
    m = ui->spinBox_2->value();
    selectMaterial(dFreqPer);
    inN = CFreq/dFreq;
    upFreq = CFreq + dFreq/2;
    downFreq = CFreq - dFreq/2;
    Lamda = V/CFreq;
    h = myRound(Lamda/2.0, 8);
    d = myRound(Lamda/4.0, 8);
    W = myRound(20 * Lamda, 5);
    Lin = myRound(h*(2*inN-1)+d, 8);
   if(type == equidistant_apodized || not_equidistant_apodized) {
        outN = (m+1)*(CFreq/dFreq);
        qreal tz = L1/V;
        for(uint n  = 1; n <= outN; n++) {
            qreal temp = V * ((upFreq*tz)/(2*dFreq))*(1-qSqrt(1-((4*n*dFreq)/(qPow(upFreq, 2)*tz))));
            Hn.insert(n, myRound(temp, 8));
        }
        int N2 = outN;
        for(int n = -N2, i = 0; n <= N2; n++, i++) {
            if(n == 0) {
                Wn.insert(i, 0);
                Fn.insert(i, 0);
                Yn.insert(i, 0);
            }
            else {
                Wn.insert(i, myRound(func_apodiz(n), 5));
                qreal temp = (pi*n)/(N2+1);
                Fn.insert(i, myRound(Wn[i]*sin(temp)/temp, 5));
                Yn.insert(i, myRound((W/2)*(1-pow(-1, n)*Fn.at(i)), 5));
           }
        }
        Lout = 0;
        for(int i = 1; i < outN; i++) {
            Lout +=2 * Hn.at(i);
        }
        Lout += d;
        Lout = myRound(Lout, 5);
    }
    Ld = myRound(Lin + Lout + L1 + L2, 5);
    L4 = 2.0*d;
    Lw = myRound(W + 2*(L3+L4), 5);
    Lh = 0.0015;
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    ui->label_9->setText("L1 = " + QString::number(value) + " мм");
    L1 = value/1000.0;
}

void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    ui->label_10->setText("L2 = " + QString::number(value) + " мм");
    L2 = value/1000.0;
}

void MainWindow::on_horizontalSlider_3_valueChanged(int value)
{
    ui->label_11->setText("L3 = " + QString::number(value) + " мм");
    L3 = value/1000.0;
}


void MainWindow::on_pushButton_2_clicked()
{
    if(myState == InputConv) {
        ui->pushButton->setEnabled(true);
        ui->pushButton_2->setEnabled(false);
        ui->stackedWidget->setCurrentIndex(0);
        ui->stackedWidget_2->setCurrentIndex(0);
        myState = InputData;
        return;
    }
    if(myState == OutputConv) {
        ui->pushButton->setEnabled(true);
        ui->stackedWidget->setCurrentIndex(1);
        QPixmap pix(":/pavIcon/InputConv.png");
        ui->label_40->setGeometry(0, 0, pix.width()>650 ? 650:pix.width() , pix.height()>390 ? 390:pix.height());
        ui->label_40->setPixmap(pix);
        myState = InputConv;
        return;
    }
    if(myState == SizeConv) {
        ui->pushButton->setEnabled(true);
        QPixmap pix(":/pavIcon/OutputConv.png");
        ui->label_40->setGeometry(0, 0, pix.width()>650 ? 650:pix.width() , pix.height()>390 ? 390:pix.height());
        ui->label_40->setPixmap(pix);
        ui->stackedWidget->setCurrentIndex(2);
        myState = OutputConv;
        return;
    }
}



void MainWindow::slotEnableOk()
{
    if(myState == InputConv) {
        if(ui->lineEdit_2->text() != 0 &&  ui->lineEdit_3->text() != 0 &&
           ui->lineEdit_4->text() != 0 && ui->lineEdit_5->text() != 0 && ui->lineEdit_6->text() != 0) {
            ui->pushButton->setEnabled(true);
        }
        else {
            ui->pushButton->setEnabled(false);
        }
    }
    if(myState == SizeConv) {
        if(ui->lineEdit_7->text() != 0 &&  ui->lineEdit_8->text() != 0 &&
           ui->lineEdit_9->text() != 0 && ui->lineEdit_10->text() != 0) {
            ui->pushButton->setEnabled(true);
        }
        else {
            ui->pushButton->setEnabled(false);
        }
    }
}


void MainWindow::on_spinBox_4_valueChanged(int arg1)
{
    ui->tableWidget->setRowCount(2*arg1+1);
    arg1 = -arg1;
    for(int i = 0; i < ui->tableWidget->rowCount(); i++, arg1++) {
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(arg1)));
    }
}

bool MainWindow::checkInputConv() {
    bool error;
    if(ui->comboBox->currentText() != strMaterial(myMaterial)) {
        ui->label_13->setStyleSheet("color: rgb(255, 0, 0)");
        error = true;
    }
    else {
        ui->label_13->setStyleSheet("color: rgb(0, 0, 0)");
    }
    if(ui->spinBox->value() != inN) {
        ui->label_14->setStyleSheet("color: rgb(255, 0, 0)");
        error = true;
    }
    else {
        ui->label_14->setStyleSheet("color: rgb(0, 0, 0)");
    }
    if(ui->lineEdit_2->text().toDouble() != upFreq/1000000) {
        ui->label_16->setStyleSheet("color: rgb(255, 0, 0)");
        error = true;
    }
    else {
        ui->label_16->setStyleSheet("color: rgb(0, 0, 0)");
    }
    if(ui->lineEdit_3->text().toDouble() != downFreq/1000000) {
        ui->label_17->setStyleSheet("color: rgb(255, 0, 0)");
       error = true;
    }
    else {
        ui->label_17->setStyleSheet("color: rgb(0, 0, 0)");
    }
    if(ui->lineEdit_4->text() != QString::number(h*pow(10, 6))) {
        ui->label_20->setStyleSheet("color: rgb(255, 0, 0)");
       error = true;
    }
    else {
        ui->label_20->setStyleSheet("color: rgb(0, 0, 0)");
    }
    if(ui->lineEdit_5->text() != QString::number(d*pow(10, 6))) {
        ui->label_22->setStyleSheet("color: rgb(255, 0, 0)");
        error = true;
    }
    else {
        ui->label_22->setStyleSheet("color: rgb(0, 0, 0)");
    }
    if( ui->lineEdit_6->text() != QString::number(W*1000)) {
        ui->label_24->setStyleSheet("color: rgb(255, 0, 0)");
        error = true;
    }
    else {
        ui->label_24->setStyleSheet("color: rgb(0, 0, 0)");
    }
    return !error;
}

bool MainWindow::checkOutputConv() {
    bool error = false;
    if(ui->spinBox_4->value() != outN) {
        ui->label_30->setStyleSheet("color: rgb(255, 0, 0)");
        error = true;
        return !error;
    }
    else {
         ui->label_30->setStyleSheet("color: rgb(0, 0, 0)");
    }
    QTableWidgetItem *item;
    for(int i = 0; i < ui->tableWidget->rowCount(); i++) {
        //------------------------------------------------------------------
        item = ui->tableWidget->item(i, 2);
        if(item != 0) {
            if(item->text() != QString::number(Wn.at(i)*pow(10, 3))) {
                item->setTextColor(Qt::red);
                ui->tableWidget->setItem(i, 2, item);
                error = true;
            }
            else {
                item->setTextColor(Qt::black);
                ui->tableWidget->setItem(i, 2, item);
            }
        }
        else {
            error = true;
        }
        //-------------------------------------------------------------------
        item = ui->tableWidget->item(i, 3);
        if(item != 0) {
            if(item->text() != QString::number(Fn.at(i)*pow(10, 3))) {
                item->setTextColor(Qt::red);
                ui->tableWidget->setItem(i, 3, item);
                error = true;
            }
            else {
                item->setTextColor(Qt::black);
                ui->tableWidget->setItem(i, 3, item);
            }
        }
        else {
            error = true;
        }
        //-------------------------------------------------------------------
        item = ui->tableWidget->item(i, 4);
        if(item != 0) {
            if(item->text() != QString::number(Yn.at(i)*pow(10, 3))) {
                item->setTextColor(Qt::red);
                ui->tableWidget->setItem(i, 4, item);
                error = true;
            }
            else {
                item->setTextColor(Qt::black);
                ui->tableWidget->setItem(i, 4, item);
            }
        }
        else {
            error = true;
        }
        //-------------------------------------------------------------------
        if(i > outN) {
            item = ui->tableWidget->item(i, 1);
            if(item != 0) {
                if(item->text() != QString::number(Hn.at(i-outN-1)*pow(10, 6))) {
                    item->setTextColor(Qt::red);
                    ui->tableWidget->setItem(i, 1, item);
                    error = true;
                }
                else {
                    item->setTextColor(Qt::black);
                    ui->tableWidget->setItem(i, 1, item);
                }
            }
            else {
                error = true;
            }
        }
    }
    return !error;
}

bool MainWindow::checkSizeConv() {
    bool error = false;
    if(ui->lineEdit_7->text() != QString::number(Lin*pow(10, 6))) {
        ui->label_27->setStyleSheet("color: rgb(255, 0, 0)");
        error = true;
    }
    else {
        ui->label_27->setStyleSheet("color: rgb(0, 0, 0)");
    }
    if(ui->lineEdit_8->text() != QString::number(Lout*pow(10, 3))) {
        ui->label_32->setStyleSheet("color: rgb(255, 0, 0)");
        error = true;
    }
    else {
        ui->label_32->setStyleSheet("color: rgb(0, 0, 0)");
    }
    if(ui->lineEdit_9->text() != QString::number(Ld*pow(10, 3))) {
        ui->label_34->setStyleSheet("color: rgb(255, 0, 0)");
        error = true;
    }
    else {
        ui->label_34->setStyleSheet("color: rgb(0, 0, 0)");
    }
    if(ui->lineEdit_10->text() != QString::number(Lw*pow(10, 3))) {
        ui->label_36->setStyleSheet("color: rgb(255, 0, 0)");
        error = true;
    }
    else {
        ui->label_36->setStyleSheet("color: rgb(0, 0, 0)");
    }
    return !error;
}

void MainWindow::on_pushButton_3_clicked()
{

    if(myState == InputConv) {
        helpDialog = new QDialog(this);
        helpDialog->setWindowTitle("Help");
        QLabel *lbl = new QLabel(helpDialog);
        QString str = "Тип входного преобразователся - эквидисантый неаподизированный, Материа - " +strMaterial(myMaterial) +
                " \n N = " + QString::number(inN) + ""
                " Верхняя частота = " +  QString::number(upFreq/pow(10, 6)) + " МГц Нижняя частота = " +  QString::number(downFreq/pow(10, 6)) + " МГц \n"
                " h = "+  QString::number(h*pow(10, 6)) + " мкм d = " +  QString::number(d*pow(10, 6)) + " мкм  W = " + QString::number(W*pow(10, 6)) + " мкм";
        lbl->setText(str);
        QVBoxLayout *layout = new QVBoxLayout(helpDialog);

        layout->addWidget(lbl);
        helpDialog->setLayout(layout);
        helpDialog->show();
        return;
    }
    if(myState == OutputConv) {
        helpDialog = new QDialog(this);
        helpDialog->setWindowTitle("Help");
        QTableWidget *helpTable = new QTableWidget(helpDialog);
        helpTable->setColumnCount(5);
        helpTable->setHorizontalHeaderItem(0, new QTableWidgetItem("n"));
        helpTable->setHorizontalHeaderItem(1, new QTableWidgetItem("h(n), мкм"));
        helpTable->setHorizontalHeaderItem(1, new QTableWidgetItem("w(n), мм"));
        helpTable->setHorizontalHeaderItem(2, new QTableWidgetItem("F(n), мм"));
        helpTable->setHorizontalHeaderItem(3, new QTableWidgetItem("Y(n), мм"));
        for(int n = -(int)outN, i = 0; n <= outN; n++, i++) {
            helpTable->insertRow(i);
            helpTable->setItem(i, 0, new QTableWidgetItem(QString::number(n)));
            helpTable->setItem(i, 2, new QTableWidgetItem(QString::number(Wn.at(i)*pow(10, 3))));
            helpTable->setItem(i, 3, new QTableWidgetItem(QString::number(Fn.at(i)*pow(10, 3))));
            helpTable->setItem(i, 4, new QTableWidgetItem(QString::number(Yn.at(i)*pow(10, 3))));
            if(n > 0) {
                helpTable->setItem(i, 1, new QTableWidgetItem(QString::number(Hn.at(i-outN-1)*pow(10, 6))));
            }
        }
        QVBoxLayout *layout = new QVBoxLayout(helpDialog);
        layout->addWidget(helpTable);
        helpDialog->setLayout(layout);
        helpDialog->show();
        return;
    }
    if(myState == SizeConv) {
        helpDialog = new QDialog(this);
        helpDialog->setWindowTitle("Help");
        QLabel *lbl = new QLabel(helpDialog);
        QString str = "Lin = " + QString::number(Lin*pow(10, 6)) + " мкм Lout = " + QString::number(Lout*pow(10, 3)) + " мм \n"
                "Длина звукопровода = " + QString::number(Ld*pow(10, 3)) + " мм\nШирина звукопровода = " + QString::number(Lw*pow(10, 3)) + " мм";
        lbl->setText(str);
        QVBoxLayout *layout = new QVBoxLayout(helpDialog);
        layout->addWidget(lbl);

        helpDialog->setLayout(layout);
        helpDialog->show();
        return;
    }
}
