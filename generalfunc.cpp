#include "generalfunc.h"
#include <qfile.h>
#include <qtextstream.h>
#include <fstream>
#include <sstream>
#include <io.h>
#include<QFileDialog>
#include<QString>
#include<QObject>
#include<QTreeWidget>
#include<QMap>
#include<QDomDocument>
#include<QDir>
#include<QFileInfo>



GeneralFunc::GeneralFunc()
{

}

void GeneralFunc::writeCsv(QString csvPath, QVector<QVector<QString>> writeData, char rowSplit)
{
    QFile outFile(csvPath);
    QStringList lines;
    for (int i=0;i<writeData.size();i++)
    {
        QString lineData=QString("");
        for (int j=0;j<writeData[i].size();j++)
        {
            lineData+=writeData[i][j]+rowSplit;
        }
        lineData.chop(1);
        lineData+=QString("\n");
        lines<<lineData;
    }
    /*如果以ReadWrite方式打开，不会把所有数据清除，如果文件原来的长度为100字节，写操作写入了30字节，那么还剩余70字节，并且这70字节和文件打开之前保持一直*/
    if (outFile.open(QIODevice::WriteOnly))
    {
        for (int i = 0; i < lines.size(); i++)
        {
            outFile.write(lines[i].toStdString().c_str());/*写入每一行数据到文件*/
        }
        outFile.close();
    }
}


int GeneralFunc::readCSV(std::string FilePath, char RowSeparator, char ColSeparator, QVector<QString> *header,QVector<QVector<QString>> *readData)
{
    std::ifstream inFile(FilePath, std::ios::in);
    std::string lineStr;
    QVector<QVector<QString>> strArray;
    //按照自定字符分割
    while (getline(inFile, lineStr, RowSeparator))
    {
        // 存成二维表结构
        std::stringstream ss(lineStr);
        std::string str;
        QVector<QString>  lineArray;
        // 按照指定字符分隔
        while (getline(ss, str, ColSeparator))
        {
            lineArray.push_back(QString::fromStdString(str));
        }
        strArray.push_back(lineArray);
    }
    if(strArray.size()>0)
    {
        *header=strArray[0];
        strArray.erase(strArray.begin());
        (*readData) = strArray;
    }
    return 0;
}
void GeneralFunc::setTableWidgetHeader(QTableWidget * tbl,QVector<QString> header)
{
    int num=tbl->columnCount();
    for (int i=0;i<num;i++)
    {
        tbl->removeColumn(0);
    }
    QStringList tabHeader;
    for (int i=0;i<header.size();i++)
    {
        tabHeader<<header[i];
        int col = tbl->columnCount();
        tbl->insertColumn(col);
    }
    tbl->horizontalHeader()->setStretchLastSection(true);//自适应列宽，末尾列自动填满控件区域
    //ui->tblwgtType->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//等分控件宽度
    tbl->setEditTriggers(QAbstractItemView::EditKeyPressed);
    tbl->setHorizontalHeaderLabels(tabHeader);

}

void GeneralFunc::setTableWidgetData(QTableWidget * tbl,QVector<QVector<QString>> tabData)
{
    int num=tbl->rowCount();
    for (int i=0;i<num;i++)
    {
        tbl->removeRow(0);
    }
    for (int i=0;i<tabData.size();i++)
    {
        int row = tbl->rowCount();
        tbl->insertRow(row);
        for (int j=0;j<tabData[i].size();j++)
        {
            QTableWidgetItem *item=new QTableWidgetItem(tabData[i][j]);
            tbl->setItem(i,j,item);
        }
    }
}




void GeneralFunc::setPixmapToLbl(QLabel *lbl, QPixmap image)
{
    QPixmap image1=image.scaled(lbl->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);//重新调整图像大小以适应窗口
    lbl->setPixmap(image1);
}

QString GeneralFunc::getFilePath(QWidget *parent)
{
    QString fileName =QFileDialog::getOpenFileName(parent,
                                                   QObject::tr("open file"),
                                                   "./",
                                                   QString::fromLocal8Bit("Image files(*.bmp *.jpg *.png );;文本文件(*.txt *.csv);;All files (*.*)"));//打开打开文件对话框
    if(fileName.isEmpty())
    {
        return QString("");
    }
    else
    {
        return fileName;
    }
}

bool GeneralFunc::saveImage(QWidget *parent,QImage image)
{
    if(!image.isNull())
    {
        QString fileName = QFileDialog::getSaveFileName(parent,
                                                        QObject::tr("Save Image"),
                                                        "",
                                                        QObject::tr("bmpImage(*.bmp);;jpgImage(*.jpg);;pngImage(*.png)"));//打开保存文件对话框
        if (fileName.isNull())
        {
            return false;
        }
        else
        {
            QImage saveImage;
            saveImage=image;//获取加载图片
            //将图片重新命名并保存至刚刚创建的文件夹里
            saveImage.save(fileName);//QImage保存方法
            return  true;
        }
    }
    else
    {
        return  false;
    }
}

QImage GeneralFunc::getImageFromFile(QWidget *parent)
{
    QString filePath=getFilePath(parent);
    if(filePath=="")
    {
        return  QImage();
    }
    QImage image;
    image.load(filePath);
    return image;
}


bool GeneralFunc::isDirExist(QString fullPath)
{
    QDir dir(fullPath);
    if(dir.exists())//判断文件夹是否存在
    {
        return true;
    }
    else
    {
        bool ok=dir.mkpath(fullPath);//没有则创建一个
        return ok;
    }
}
bool GeneralFunc::isFileExist(QString filePath)
{
    QFile file(filePath);
    if(file.exists())//判断文件是否存在
    {
        return true;
    }
    else
    {
        bool ok=file.open(QIODevice::WriteOnly);//没有则创建一个
        file.close();
        return ok;
    }
}

QStringList GeneralFunc::GetAllFileFolder(QString dirPath)
{
    QStringList folders;
    QDir dir(dirPath);
    dir.setFilter(QDir::Dirs);
    foreach(QFileInfo fullDir, dir.entryInfoList())
    {
        if(fullDir.fileName() == "." || fullDir.fileName() == "..") continue;
        folders<<fullDir.absoluteFilePath();
    }
    return folders;
}

QStringList GeneralFunc::getFileList(const QString &path,QStringList fileType)//"*.jpg" << "*.png"
{
    QDir dir(path);
    QStringList nameFilters;
    nameFilters = fileType;
    QStringList files = dir.entryList(nameFilters, QDir::Files|QDir::Readable, QDir::Name);
    return files;
}










