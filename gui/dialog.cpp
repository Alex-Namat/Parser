#include "dialog.h"
#include <QFont>
#include "parser.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    draw();

    connect(pushButton,SIGNAL(clicked(bool)),this,SLOT(clicked_pushButton()));
}

Dialog::~Dialog()
{
}

void Dialog::clicked_pushButton()
{
    std::string str(codeEditor->toPlainText().toStdString());
    Parser<std::string::iterator> parser(str.begin(),str.end());

   clearSelection();
    try {
        parser.parse();
        auto table = parser.getTable();
        QString tmp;
        for (const auto& i : table) {
            tmp += QString::fromStdString(i.first->lexeme);
            tmp += " = ";
            tmp += QString::number(i.second);
            tmp += "\n";
        }
        textEdit->setText(tmp);
    }
    catch (const ParseError& exception) {
        QString str;
        str += QString::number(exception.pos.line);
        str += ":";
        str += QString::number(exception.pos.pos);
        str += ": '";
        str += QString::fromStdString(exception.tok);
        str += "' ";
        str += QString::fromStdString(exception.msg);
        textEdit->setText(str);
        errorSelection(exception.pos.absPos);
    }
    catch (const std::exception& exception) {
        textEdit->setText(QString::fromLocal8Bit(exception.what()));
    }
}

void Dialog::draw()
{
    vSpacer = new QSpacerItem(20,40, QSizePolicy::Fixed, QSizePolicy::Expanding);
    vbLayout = new QVBoxLayout;
    vbLayout->addSpacerItem(vSpacer);
    QFont font("Times New Roman",14);
    pushButton = new QPushButton("Run");
    pushButton->setMinimumSize(40,40);
    pushButton->setMaximumSize(40,40);
    pushButton->setFont(font);
    vbLayout->addWidget(pushButton);

    splitter = new QSplitter(Qt::Vertical);
    codeEditor = new CodeEditor;
    font.setFamily("Lucida Console");
    font.setPointSize(10);
    codeEditor->setFont(font);
    splitter->addWidget(codeEditor);
    textEdit = new QTextEdit;
    font.setFamily("Consolas");
    font.setPointSize(10);
    textEdit->setFont(font);
    textEdit->setReadOnly(true);
    splitter->addWidget(textEdit);

    hbLayout = new QHBoxLayout;
    hbLayout->addWidget(splitter);
    hbLayout->addLayout(vbLayout);

    setLayout(hbLayout);
}

void Dialog::errorSelection(const int& pos)
{
    QTextCursor cur = codeEditor->textCursor();
    QTextCursor tmp = cur;
    QTextCharFormat fmt;
    fmt.setBackground(Qt::red);
    tmp.setPosition(pos, QTextCursor::MoveAnchor);
    tmp.movePosition(QTextCursor::PreviousWord,QTextCursor::KeepAnchor);
    tmp.setCharFormat(fmt);
    tmp.select(QTextCursor::LineUnderCursor);
    codeEditor->setTextCursor(tmp);
    codeEditor->setTextCursor(cur);
}

void Dialog::clearSelection()
{
    QTextCursor cur = codeEditor->textCursor();
    QTextCharFormat fmt;
    fmt.setBackground(Qt::white);
    cur.setPosition(0, QTextCursor::MoveAnchor);
    cur.movePosition(QTextCursor::End,QTextCursor::KeepAnchor);
    cur.setCharFormat(fmt);
    cur.select(QTextCursor::LineUnderCursor);
    codeEditor->setTextCursor(cur);
}
