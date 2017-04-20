#include "frmabout.h"
#include "ui_frmabout.h"

/**
 * @brief Constructor (optional parent Widget parameter)
 * @param parent parent Widget
 */
FrmAbout::FrmAbout(QWidget *parent) : QMainWindow(parent), ui(new Ui::FrmAbout)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
}

/**
 * @brief Deconstructor frees memory usage
 */
FrmAbout::~FrmAbout()
{
    delete ui;
}

/**
 * @brief Close button click event
 */
void FrmAbout::on_btnClose_clicked()
{
    close();
}
