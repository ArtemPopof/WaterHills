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
private slots:
    void on_verticalSlider_sliderMoved(int position);
};

#endif // EDITOWINDOW_H
