#ifndef FRMMAIN_H
#define FRMMAIN_H

#include <QMainWindow>
#include <QMessageBox>
#include <QString>

/* Forward declerations */
namespace Ui
{
    class FrmMain;
}

/**
 * @brief FrmMain class
 */
class FrmMain : public QMainWindow
{
    /* Q_OBJECT macro allows usage of slots */
    Q_OBJECT

public:

    /* Constructor (optional parent Widget parameter) */
    explicit FrmMain(QWidget *parent = 0);

    /* Deconstructor frees memory usage */
    ~FrmMain();

private slots:

    /* Open File menu item click event */
    void on_actnOpenFile_triggered();

    /* Exit menu item click event */
    void on_actnExit_triggered();

    /* Background Colour menu item click event */
    void on_actnBackgroundColour_triggered();

    /* Foreground Colour menu item click event */
    void on_actnForegroundColour_triggered();

    /* About menu item click event */
    void on_actnAbout_triggered();

    /* X Position spin box value changed event */
    void on_dsbPositionX_valueChanged(double value);

    /* Y Position spin box value changed event */
    void on_dsbPositionY_valueChanged(double value);

    /* X Rotation spin box value changed event */
    void on_dsbRotationX_valueChanged(double value);

    /* Y Rotation spin box value changed event */
    void on_dsbRotationY_valueChanged(double value);

    /* Z Rotation spin box value changed event */
    void on_dsbRotationZ_valueChanged(double value);

    /* Zoom spin box value changed event */
    void on_dsbZoom_valueChanged(double value);

    /* Point Cloud radio dialog button toggle event */
    void on_rdbPointCloud_toggled(bool state);

    /* Wireframe radio dialog button toggle event */
    void on_rdbWireframe_toggled(bool state);

    /* Sets the ModelViewer's point size to 1 */
    void on_actPointSize1_triggered();

    /* Sets the ModelViewer's point size to 2 */
    void on_actPointSize5_triggered();

    /* Sets the ModelViewer's point size to 3 */
    void on_actPointSize2_triggered();

    /* Sets the ModelViewer's point size to 4 */
    void on_actPointSize3_triggered();

    /* Sets the ModelViewer's point size to 5 */
    void on_actPointSize4_triggered();

private:

    /* Window title */
    const QString cWindowTitle = "The Little Teapot";

    /* Pointer to UI controls */
    Ui::FrmMain* ui;

    /* Opens a QMessageBox of the desired specification */
    void showMessageBox(const QString& message, const QString& caption, const QMessageBox::Icon& icon);

    /* Sets all of the point size menu item's checked values to false */
    void disableActionChecks();

    /* Initializes the application and loads the default teapot model */
    void initialize();

};

#endif // FRMMAIN_H
