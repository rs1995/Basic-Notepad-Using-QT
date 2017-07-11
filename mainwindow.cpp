#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>
#include<QFile>
#include<QTextStream>
#include<QFileDialog>
#include<QFontDialog>
#include<QFont>
#include<QColor>
#include<QColorDialog>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    file_path="";
    ui->textEdit->setText("");

}

void MainWindow::on_actionOpen_triggered()
{
    QString filter=" All Files (*.*);; Text Files (*.txt);; XML Files (*.xml);; Doc Files (*.docx)";
    QString file_name= QFileDialog::getOpenFileName(this,"Open File","D://",filter);
    QFile file(file_name);
    file_path=file_name;
    if(!file.open(QFile::ReadOnly|QFile::Text)){
        QMessageBox::warning(this,"Warning","File Not Open");
        return;
    }
    QTextStream in(&file);
    QString text= in.readAll();
    ui->textEdit->setText(text);
    file.close();

}

void MainWindow::on_actionSave_triggered()
{


    QFile file(file_path);
    if(!file.open(QFile::WriteOnly|QFile::Text)){
        QMessageBox::warning(this,"Warning","File Not Saved");
        return;
    }
    QTextStream out(&file);
    QString text= ui->textEdit->toPlainText();
    out<< text;
    file.flush();
    file.close();

}

void MainWindow::on_actionSave_as_triggered()
{
    QString filter=" All Files (*.*);; Text Files (*.txt);; XML Files (*.xml);; Doc Files (*.docx)";
    QString file_name= QFileDialog::getSaveFileName(this,"Save File","D://",filter);
    QFile file(file_name);
    if(!file.open(QFile::WriteOnly|QFile::Text)){
        QMessageBox::warning(this,"Warning","File Not Saved");
        return;
    }
    QTextStream out(&file);
    QString text= ui->textEdit->toPlainText();
    out<< text;
    file.flush();
    file.close();

}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionAbout_Notepad_1_0_triggered()
{
    QMessageBox::information(this,"About Notepad 1.0","This program is free software; you can redistribute it and/or "
                                                      "modify it under the terms of the GNU General Public License as "
                                                      "published by the Free Software Foundation; either version 2 of "
                                                      "the License, or (at your option) any later version.\n"
                                                      "Author : Rohit Sharma \n"
                                                      "Date   : 6/15/2017\n"
                                                      "(C) Notepad 1.0 (R)");

}

void MainWindow::on_actionFont_triggered()
{
    bool ok;
    QFont font= QFontDialog::getFont(&ok,this);
    if(true){
        ui->textEdit->setFont(font);
    }
    else return;
}

void MainWindow::on_actionText_Color_triggered()
{
    QColor color= QColorDialog::getColor(Qt::white,this,"Choose color");
    if(color.isValid()){
        ui->textEdit->setTextColor(color);
    }
    else return;
}

void MainWindow::on_actionText_Background_triggered()
{
    QColor color= QColorDialog::getColor(Qt::white,this,"Choose color");
    if(color.isValid()){
        ui->textEdit->setTextBackgroundColor(color);
    }
    else return;
}

void MainWindow::on_actionPalette_Color_triggered()
{
    QColor color= QColorDialog::getColor(Qt::white,this,"Choose color");
    if(color.isValid()){
        ui->textEdit->setPalette(QPalette(color));
    }
    else return;
}
