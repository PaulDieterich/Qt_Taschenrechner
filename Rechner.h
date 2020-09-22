#ifndef RECHNER_H
#define RECHNER_H

#include <QMainWindow>
#include <QWidget>
#include <QLineEdit>
#include <QDebug>
//#include <QLCDNumber>
//#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class Rechner; }
QT_END_NAMESPACE
//class QLineEdit;

class Rechner : public QMainWindow
{
    Q_OBJECT


public:
    Rechner(QWidget *parent = nullptr);
    ~Rechner();


private slots:
    void num_click();
   // void on_pb0_clicked();
   // void on_pb1_clicked();
   // void on_pb2_clicked();
   // void on_pb3_clicked();
    //void on_pb4_clicked();
    //void on_pb5_clicked();
   // void on_pb6_clicked();
   // void on_pb7_clicked();
   // void on_pb8_clicked();
   // void on_pb9_clicked();


    void MultDiv();
    void SubAdd();
    //void on_pbAdd_clicked();
    //void on_pbSub_clicked();
    //void on_pbMult_clicked();
    //void on_pbDiv_clicked();

    void on_pbInv_clicked();
    void on_pbComma_clicked();

    void on_pbBackSp_clicked();
    void on_pbEqual_clicked();
    void on_pbReset_clicked();

    void on_pbReset_2_released();

private:
    void abortOperation();                                                  // x/0
    void clearAll();
    //double sumInMemory;
    double sumTemp;                                                         // store accumulated value
    double factorTemp;                                                      // store temp mult / div value

    QString pendAddOperator;                                                // store last additive clicked operator "+" or "-"
    QString pendMultOperator;                                               // store last multiplicative clicked operator "*" or "/"

    bool waitOperand;                                                       // true when ready to start typing an operand.
    bool calculate(double rightOperand, const QString &pendOperator);       // +, -, x, /

    QLineEdit *display;

    Ui::Rechner *ui;
};
#endif // RECHNER_H
