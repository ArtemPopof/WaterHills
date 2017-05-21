#include "editowindow.h"
#include "ui_editowindow.h"

EditoWindow::EditoWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EditoWindow)
{
    ui->setupUi(this);
}

EditoWindow::~EditoWindow()
{
    delete ui;
}

void EditoWindow::keyPressEvent(QKeyEvent *event)
{
    ui->openGLWidget->m_currentCamera->handleKeyboard(event);
}
