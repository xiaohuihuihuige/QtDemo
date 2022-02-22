#include "mainwindow.h"
#include "ui_mainwindow.h"

#include"generalfunc.h"
#include<QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this is test;
    this is test3;
#if 0
     cv::Mat src=cv::imread(filename.toStdString().data(),1);
    if(src.empty())
    {
        QMessageBox::warning(this,"waring","empty");
    }
    QImage qsrc=QtOpencv::cvMat2QImage(src);
    GeneralFunc::setPixmapToLbl(ui->lblImage,QPixmap::fromImage(qsrc));
#elif 1
    i_show_image_label_width = ui->lblImage->width();
    i_show_image_label_height = ui->lblImage->height();

    // start x, start y
    i_show_image_start_x = 0;
    i_show_image_start_y = 0;

    // image scale ratio
    f_iamge_ratio_x = 1.0f;
    f_iamge_ratio_y = 1.0f;

    // zoom parameter
    f_zoom_step = 0.5;
    f_zoom_ratio_max = 4;
    f_zoom_ratio_min = 1;
    f_zoom_current_scale = 1.0;

    // image translate
    b_mouse_left_button_clicked = false;
    b_mouse_right_button_clicked = false;

    QString filename="E:\\WorkSpace\\Qt\\ZoomPicture\\001.bmp";//中文路径报错
    QImage qsrc;
    qsrc.load(filename);
    qimage_front_image=new QImage(qsrc);
    // record the image scale ration x,y
    f_iamge_ratio_x = qimage_front_image->width()*1.0 / ui->lblImage->width();
    f_iamge_ratio_y = qimage_front_image->height()*1.0 / ui->lblImage->height();
    QImage qimage_temp = qimage_front_image->copy();

    QImage * qimage_scaled = new QImage;
    *qimage_scaled = qimage_temp.scaled(QSize(ui->lblImage->width(), ui->lblImage->height()), Qt::IgnoreAspectRatio);
    ui->lblImage->setPixmap(QPixmap::fromImage(*qimage_scaled));
    delete qimage_scaled;
    // change status
    b_is_front_image_opened = true;

    // reset parameters about show image
    f_zoom_current_scale = 1;
    // start x, start y
    i_show_image_start_x = 0;
    i_show_image_start_y = 0;
#else
#endif


}

MainWindow::~MainWindow()
{
    delete ui;
}


//mousePressEvent

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    // case1 : front image is opened
    if (b_is_front_image_opened) {
        // select edge point
        if (event->button() == Qt::LeftButton) {

            b_mouse_left_button_clicked = true;
        }else if (event->button() == Qt::RightButton) {
            // translate image
            b_mouse_right_button_clicked = true;
            i_mouse_last_position_x = event->localPos().x();
            i_mouse_last_position_y = event->localPos().y();
        }
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (b_is_front_image_opened) {
        if (b_mouse_right_button_clicked) {
            i_mouse_new_position_x = event->localPos().x();
            i_mouse_new_position_y = event->localPos().y();
            translate_image();
        }
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    //change the flag
    if (event->button() == Qt::LeftButton) {
        b_mouse_left_button_clicked = false;
    }
    else if (event->button() == Qt::RightButton) {
        b_mouse_right_button_clicked = false;
    }
}
// wheel to zoom in and zoom out
void MainWindow::wheelEvent(QWheelEvent* event)
{

    // get the delta
    float f_degree_delta = short(event->delta())*1.0 / 640;

    // case1 : front image opened
    if (b_is_front_image_opened) {

        // zoom in and zoom out
        // update scale ratio
        if (f_zoom_current_scale + f_degree_delta > f_zoom_ratio_max || f_zoom_current_scale + f_degree_delta < f_zoom_ratio_min) {
            return;
        }
        f_zoom_current_scale += f_degree_delta;
        f_iamge_ratio_x = qimage_front_image->width()*1.0 / (f_zoom_current_scale*ui->lblImage->width());
        f_iamge_ratio_y = qimage_front_image->height()*1.0 / (f_zoom_current_scale*ui->lblImage->height());

        // show image
        show_image();
    }
}

void MainWindow::show_image() {

    // test if qimage_front_image is not opened
    if (qimage_front_image == NULL) {
        return;
    }

    // show image
    QImage qimage_temp = qimage_front_image->copy();

    // judge if the start_x or start_y is legal
    if (i_show_image_start_x + ui->lblImage->width() > ui->lblImage->width()*f_zoom_current_scale) {
        i_show_image_start_x = ui->lblImage->width()*f_zoom_current_scale - ui->lblImage->width() - 1;
    }
    if (i_show_image_start_y + ui->lblImage->height() > ui->lblImage->height()*f_zoom_current_scale) {
        i_show_image_start_y = ui->lblImage->height()*f_zoom_current_scale - ui->lblImage->height() - 1;
    }

    QImage * qimage_scaled = new QImage;
    *qimage_scaled = qimage_temp.scaled(QSize(ui->lblImage->width()*f_zoom_current_scale, ui->lblImage->height()*f_zoom_current_scale), Qt::IgnoreAspectRatio).copy(i_show_image_start_x, i_show_image_start_y, ui->lblImage->width(), ui->lblImage->height());
    ui->lblImage->setPixmap(QPixmap::fromImage(*qimage_scaled));
    delete qimage_scaled;

}

void MainWindow::translate_image()
{

    //
    int i_distance = (i_mouse_new_position_x - i_mouse_last_position_x)*(i_mouse_new_position_x - i_mouse_last_position_x) + (i_mouse_new_position_y - i_mouse_last_position_y)*(i_mouse_new_position_y - i_mouse_last_position_y);
    if (i_distance < 50) {
        return;
    }

    // compute the delta
    int i_delta_x = -1 * (i_mouse_new_position_x - i_mouse_last_position_x);
    int i_delta_y = -1 * (i_mouse_new_position_y - i_mouse_last_position_y);


    // start x exceeds the left edge
    if (i_show_image_start_x + i_delta_x < 0) {
        i_show_image_start_x = 0;

    }
    else if (i_show_image_start_x + i_delta_x + ui->lblImage->width() > int(f_zoom_current_scale*ui->lblImage->width() - 1)) {
        //start x exceeds the right edge
        i_show_image_start_x = int(f_zoom_current_scale*ui->lblImage->width() - ui->lblImage->width());
    }
    else {
        i_show_image_start_x += i_delta_x;
    }

    // start y exceeds the top edge
    if (i_show_image_start_y + i_delta_y < 0) {
        i_show_image_start_y = 0;

    }
    else if (i_show_image_start_y + i_delta_y + ui->lblImage->height() > int(f_zoom_current_scale*ui->lblImage->height() - 1)) {
        //start y exceeds the bottom edge
        i_show_image_start_y = int(f_zoom_current_scale*ui->lblImage->height() - ui->lblImage->height());
    }
    else {
        i_show_image_start_y += i_delta_y;
    }

    // update the mouse last position
    i_mouse_last_position_x = i_mouse_new_position_x;
    i_mouse_last_position_y = i_mouse_new_position_y;

    // show image
    show_image();

}
