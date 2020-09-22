#include "Rechner.h"
#include "ui_Rechner.h"
#include <QLineEdit>
#include <QtMath>

#include <QDebug>
Rechner::Rechner(QWidget *parent)
    : QMainWindow(parent), sumTemp(0.0), factorTemp(0.0), waitOperand(true)

    , ui(new Ui::Rechner)
{
    ui->setupUi(this);
    //ui->Calculation->setReadOnly(true);
    //ui->Calculation->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    display = new QLineEdit();
    //display->setText(QString::number("555"));
    ui->display->setText("0");
    //ui->LcdNum->setText("0");
    connect(ui->pbDiv,SIGNAL(released()),this,SLOT(MultDiv()));
    connect(ui->pbMult,SIGNAL(released()),this,SLOT(MultDiv()));
    connect(ui->pbSub,SIGNAL(released()),this,SLOT(SubAdd()));
    connect(ui->pbAdd,SIGNAL(released()),this,SLOT(SubAdd()));

    connect(ui->pb0,SIGNAL(released()),this,SLOT(num_click()));
    connect(ui->pb1,SIGNAL(released()),this,SLOT(num_click()));
    connect(ui->pb2,SIGNAL(released()),this,SLOT(num_click()));
    connect(ui->pb3,SIGNAL(released()),this,SLOT(num_click()));
    connect(ui->pb4,SIGNAL(released()),this,SLOT(num_click()));
    connect(ui->pb5,SIGNAL(released()),this,SLOT(num_click()));
    connect(ui->pb6,SIGNAL(released()),this,SLOT(num_click()));
    connect(ui->pb7,SIGNAL(released()),this,SLOT(num_click()));
    connect(ui->pb8,SIGNAL(released()),this,SLOT(num_click()));
    connect(ui->pb9,SIGNAL(released()),this,SLOT(num_click()));
}

Rechner::~Rechner()
{
    delete ui;
}

void Rechner::num_click(){
    QPushButton *numButton = (QPushButton*) sender();
    QString number = numButton->text(); //speichert die zahl die auf dem Button steht.

    if(ui->display->text() == "0" && number == "0") return;
    if(waitOperand){
        ui->display->clear();
        waitOperand = false;
    }
    ui->display->setText(ui->display->text() + number);

}
/*
void Rechner::on_pb0_clicked()
{
    int digitValue = 0;

    if (ui->display->text() == "0" && digitValue == 0.0)
        return;

    if (waitOperand)
    {
        ui->display->clear();
        waitOperand = false;
    }
    ui->display->setText(ui->display->text() + QString::number(digitValue));
}
*/
/*void Rechner::on_pb1_clicked()
{
    int digitValue = 1;

    if (ui->display->text() == "0" && digitValue == 0.0)
        return;

    if (waitOperand)
    {
        ui->display->clear();
        waitOperand = false;
    }
    ui->display->setText(ui->display->text() + QString::number(digitValue));
}

void Rechner::on_pb2_clicked()
{
    int digitValue = 2;

    if (ui->display->text() == "0" && digitValue == 0.0)
        return;

    if (waitOperand)
    {
        ui->display->clear();
        waitOperand = false;
    }
    ui->display->setText(ui->display->text() + QString::number(digitValue));
}

void Rechner::on_pb3_clicked()
{
    int digitValue = 3;

    if (ui->display->text() == "0" && digitValue == 0.0)
        return;

    if (waitOperand)
    {
        ui->display->clear();
        waitOperand = false;
    }
    ui->display->setText(ui->display->text() + QString::number(digitValue));
}

void Rechner::on_pb4_clicked()
{
    int digitValue = 4;

    if (ui->display->text() == "0" && digitValue == 0.0)
        return;

    if (waitOperand)
    {
        ui->display->clear();
        waitOperand = false;
    }
    ui->display->setText(ui->display->text() + QString::number(digitValue));
}

void Rechner::on_pb5_clicked()
{
    int digitValue = 5;

    if (ui->display->text() == "0" && digitValue == 0.0)
        return;

    if (waitOperand)
    {
        ui->display->clear();
        waitOperand = false;
    }
    ui->display->setText(ui->display->text() + QString::number(digitValue));
}

void Rechner::on_pb6_clicked()
{
    int digitValue = 6;

    if (ui->display->text() == "0" && digitValue == 0.0)
        return;

    if (waitOperand)
    {
        ui->display->clear();
        waitOperand = false;
    }
    ui->display->setText(ui->display->text() + QString::number(digitValue));
}

void Rechner::on_pb7_clicked()
{
    int digitValue = 7;

    if (ui->display->text() == "0" && digitValue == 0.0)
        return;

    if (waitOperand)
    {
        ui->display->clear();
        waitOperand = false;
    }
    ui->display->setText(ui->display->text() + QString::number(digitValue));
}

void Rechner::on_pb8_clicked()
{
    int digitValue = 8;

    if (ui->display->text() == "0" && digitValue == 0.0)
        return;

    if (waitOperand)
    {
        ui->display->clear();
        waitOperand = false;
    }
    ui->display->setText(ui->display->text() + QString::number(digitValue));
}

void Rechner::on_pb9_clicked()
{
    int digitValue = 9;

    if (ui->display->text() == "0" && digitValue == 0.0)
        return;

    if (waitOperand)
    {
        ui->display->clear();
        waitOperand = false;
    }
    ui->display->setText(ui->display->text() + QString::number(digitValue));
}
*/
void Rechner::MultDiv()
{
    QPushButton *clickedButton = (QPushButton*) sender();
    if (!clickedButton){
      return;
    }
    QString clickedOperator = clickedButton->text(); //speichert das symobl "/"
    double operand = ui->display->text().toDouble();

    if (!pendMultOperator.isEmpty())
    {
        if (!calculate(operand, pendMultOperator))
        {
            abortOperation();
            return;
        }
        display->setText(QString::number(factorTemp));
    } else {
        factorTemp = operand;
    }

    pendMultOperator = clickedOperator;
    waitOperand = true;
}

void Rechner::SubAdd()
{
    QPushButton *clickedButton = (QPushButton*) sender();

    if (!clickedButton) return;
    QString clickedOperator = clickedButton->text();
    double operand = ui->display->text().toDouble();

    if (!pendMultOperator.isEmpty())
    {

        if (!calculate(operand, pendMultOperator))
        {
            abortOperation();
            return;
        }
        ui->display->setText(QString::number(factorTemp));
        operand = factorTemp;
        factorTemp = 0.0;
        pendMultOperator.clear();
    }

    if (!pendAddOperator.isEmpty())
    {

        if (!calculate(operand, pendAddOperator))
        {
            abortOperation();
            return;
        }
        ui->display->setText(QString::number(sumTemp));
    } else
    {
        sumTemp = operand;
    }

    pendAddOperator = clickedOperator;
    waitOperand = true;
}

/*
void Rechner::on_pbAdd_clicked()
{
    QPushButton *clickedButton = (QPushButton*) sender();

    if (!clickedButton) return;
    QString clickedOperator = clickedButton->text();
    double operand = ui->display->text().toDouble();

    if (!pendMultOperator.isEmpty())
    {

        if (!calculate(operand, pendMultOperator))
        {
            abortOperation();
            return;
        }
        ui->display->setText(QString::number(factorTemp));
        operand = factorTemp;
        factorTemp = 0.0;
        pendMultOperator.clear();
    }

    if (!pendAddOperator.isEmpty())
    {

        if (!calculate(operand, pendAddOperator))
        {
            abortOperation();
            return;
        }
        ui->display->setText(QString::number(sumTemp));
    } else
    {
        sumTemp = operand;
    }

    pendAddOperator = clickedOperator;
    waitOperand = true;
}
*/
/*
void Rechner::on_pbSub_clicked()
{
    QPushButton *clickedButton = (QPushButton*) sender();

    if (!clickedButton) return;
    QString clickedOperator = clickedButton->text();
    double operand = ui->display->text().toDouble();

    if (!pendMultOperator.isEmpty())
    {

        if (!calculate(operand, pendMultOperator))
        {
            abortOperation();
            return;
        }
        ui->display->setText(QString::number(factorTemp));
        operand = factorTemp;
        factorTemp = 0.0;
        pendMultOperator.clear();
    }

    if (!pendAddOperator.isEmpty())
    {

        if (!calculate(operand, pendAddOperator))
        {
            abortOperation();
            return;
        }
        ui->display->setText(QString::number(sumTemp));
    } else
    {
        sumTemp = operand;
    }

    pendAddOperator = clickedOperator;
    waitOperand = true;
}


void Rechner::on_pbMult_clicked()
{
    QPushButton *clickedButton = (QPushButton*) sender();
    if (!clickedButton){
      return;
    }
    QString clickedOperator = clickedButton->text(); //speichert das symobl "*"
    double operand = ui->display->text().toDouble();

    if (!pendMultOperator.isEmpty())
    {
        if (!calculate(operand, pendMultOperator))
        {
            abortOperation();
            return;
        }
        ui->display->setText(QString::number(factorTemp));
    } else {
        factorTemp = operand;
    }

    pendMultOperator = clickedOperator;
    waitOperand = true;
}

void Rechner::on_pbDiv_clicked()
{
    QPushButton *clickedButton = (QPushButton*) sender();
    if (!clickedButton){
      return;
    }
    QString clickedOperator = clickedButton->text(); //speichert das symobl "/"
    double operand = ui->display->text().toDouble();

    if (!pendMultOperator.isEmpty())
    {
        if (!calculate(operand, pendMultOperator))
        {
            abortOperation();
            return;
        }
        display->setText(QString::number(factorTemp));
    } else {
        factorTemp = operand;
    }

    pendMultOperator = clickedOperator;
    waitOperand = true;
}
*/

void Rechner::on_pbEqual_clicked()
{
    double operand = ui->display->text().toDouble();

    if (!pendMultOperator.isEmpty())
    {
        if (!calculate(operand, pendMultOperator))
        {
            abortOperation();
            return;
        }
        operand = factorTemp;
        factorTemp = 0.0;
        pendMultOperator.clear();
    }
    if (!pendAddOperator.isEmpty())
    {
        if (!calculate(operand, pendAddOperator))
        {
            abortOperation();
            return;
        }
        pendAddOperator.clear();
    } else
    {
        sumTemp = operand;
    }

    ui->display->setText(QString::number(sumTemp));
    sumTemp = 0.0;
    waitOperand = true;
}

void Rechner::on_pbBackSp_clicked()
{
    if (waitOperand)
        return;

    QString text = ui->display->text();
    text.chop(1);
    if (text.isEmpty())
    {
        text = "0";
        waitOperand = true;
    }
    ui->display->setText(text);
}

void Rechner::on_pbInv_clicked()
{
    QString text = ui->display->text();
    double value = text.toDouble();

    if (value > 0.0)
    {
        text.prepend(tr("-"));
    } else if (value < 0.0)
    {
        text.remove(0, 1);
    }
    ui->display->setText(text);
}

void Rechner::on_pbComma_clicked()
{
    if (waitOperand)
        ui->display->setText("0");
    if (!ui->display->text().contains('.'))
        ui->display->setText(ui->display->text() + tr("."));
    waitOperand = false;
}

void Rechner::on_pbReset_clicked()
{
    if (waitOperand)
        return;

    ui->display->setText("0");
    waitOperand = true;
}
void Rechner::clearAll()
{
    sumTemp = 0;
    factorTemp = 0;
    pendAddOperator.clear();
    pendMultOperator.clear();
    ui->display->setText("0");
    waitOperand = true;
}
void Rechner::abortOperation()
{
    clearAll();
    ui->display->setText(tr("####"));
}

bool Rechner::calculate(double rightOperand, const QString &pendOperator)
{
    if (pendOperator == tr("+"))
    {
        sumTemp += rightOperand;
    } else if (pendOperator == tr("-"))
    {
        sumTemp -= rightOperand;
    } else if (pendOperator == tr("\303\227"))
    {
        factorTemp *= rightOperand;
    } else if (pendOperator == tr("\303\267"))
    {
        if (rightOperand == 0.0)
            return false;
        factorTemp /= rightOperand;
    }
    return true;
}

void Rechner::on_pbReset_2_released()
{
   clearAll();
}
