#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QPushButton>
#include <QTextEdit>
#include <QSplitter>
#include <string>
#include "codeeditor.h"

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void clicked_pushButton();

private:
    void draw();
    void errorSelection(const int& pos);
    void clearSelection();
    QSpacerItem* vSpacer;
    QVBoxLayout* vbLayout;
    QHBoxLayout* hbLayout;
    QPushButton* pushButton;
    QTextEdit* textEdit;
    QSplitter* splitter;
    CodeEditor* codeEditor;
};

#endif // DIALOG_H
