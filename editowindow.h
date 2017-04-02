#ifndef EDITOWINDOW_H
#define EDITOWINDOW_H

#include <QMainWindow>

namespace Ui {
class EditoWindow;
}

class EditoWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit EditoWindow(QWidget *parent = 0);
    ~EditoWindow();

private:
    Ui::EditoWindow *ui;

    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *event);
};

#endif // EDITOWINDOW_H
