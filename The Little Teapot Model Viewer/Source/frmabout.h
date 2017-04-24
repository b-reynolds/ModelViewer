#ifndef FRMABOUT_H
#define FRMABOUT_H

#include <QMainWindow>

/* Forward declerations */
namespace Ui
{
    class FrmAbout;
}

/**
 * @brief FrmAbout class
 */
class FrmAbout : public QMainWindow
{
    /* Q_OBJECT macro allows usage of slots */
    Q_OBJECT

public:

    /* Constructor (optional parent Widget parameter) */
    explicit FrmAbout(QWidget *parent = 0);

    /* Deconstructor frees memory usage */
    ~FrmAbout();

private slots:

    /* Close button click event */
    void on_btnClose_clicked();

private:

    /* Pointer to UI controls */
    Ui::FrmAbout *ui;

};

#endif // FRMABOUT_H
