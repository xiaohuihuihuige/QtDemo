#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"qtopencv.h"
#include <QtWidgets/QMainWindow>
#include <QDebug>
#include <QFileDialog>
#include <QString>
#include <QDir>
#include <QMessageBox>
#include <QImage>
#include <vector>
#include <QScrollBar>
#include<QWheelEvent>
#include<QMouseEvent>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    cv::Mat srcImage,showImage,drawImage;

        QImage m_Image;
    // class variable
        int i_show_image_label_width;
        int i_show_image_label_height;

        // image show start x, start y
        int i_show_image_start_x;
        int i_show_image_start_y;

        // image zoom in ratio
        float f_iamge_ratio_x;
        float f_iamge_ratio_y;

        // zoom parameter
        float f_zoom_step;
        float f_zoom_ratio_max;
        float f_zoom_ratio_min;
        float f_zoom_current_scale;


        // QImage front image pointer
        QImage* qimage_front_image;
        bool b_is_front_image_opened;

        // bool variable
        bool is_translate_image;
        int i_mouse_last_position_x;
        int i_mouse_last_position_y;
        int i_mouse_new_position_x;
        int i_mouse_new_position_y;
        bool b_mouse_right_button_clicked;
        bool b_mouse_left_button_clicked;

        //**************************************
        //functions
        //**************************************
        void show_image();
        void translate_image();


    void wheelEvent(QWheelEvent *event) ;
    void mousePressEvent(QMouseEvent *event) ;
    void mouseMoveEvent(QMouseEvent *event) ;
    void mouseReleaseEvent(QMouseEvent *event) ;


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
