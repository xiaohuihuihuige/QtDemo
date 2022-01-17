#ifndef GENERALFUNC_H
#define GENERALFUNC_H

#include<QVector>
#include <string>
#include <vector>
#include<QTableWidget>
#include<QHeaderView>
#include<QLabel>
#include<QMap>

class GeneralFunc
{
public:
    GeneralFunc();
    static void writeCsv(QString csvPath, QVector<QVector<QString>> writeData, char rowSplit);
    static int readCSV(std::string FilePath, char RowSeparator, char ColSeparator,QVector<QString> *header, QVector<QVector<QString>> *readData);//读取CSV文件信息，返回String二维数组
    static void setTableWidgetHeader(QTableWidget * tbl,QVector<QString> header);
    static void setTableWidgetData(QTableWidget * tbl,QVector<QVector<QString>> tabData);
    static void setPixmapToLbl(QLabel * lbl,QPixmap image);
    static QString getFilePath(QWidget *parent);
    static bool saveImage(QWidget *parent,QImage image);
    static QImage getImageFromFile(QWidget *parent);
    static bool isDirExist(QString fullPath);
    static bool isFileExist(QString filePath);
    static QStringList GetAllFileFolder(QString dirPath);
    static QStringList getFileList(const QString &path, QStringList fileType);
};

#endif // GENERALFUNC_H
