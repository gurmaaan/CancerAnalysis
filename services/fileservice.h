#ifndef FILESERVICE_H
#define FILESERVICE_H

#ifndef ENCODING
    #define ENCODING "Windows-1251"
#endif

#include <QObject>
#include <QFileDialog>
#include <QStandardPaths>
#include <QDir>
#include <QDebug>
#include <QTextStream>
#include <QTextCodec>
#include <QFileInfo>
#include <QApplication>
#include <QImageReader>
#include <QImageWriter>
#include <QFileDialog>
#include <QByteArray>

extern const QString data_path;
extern const QString mime_separator;

enum class FileType
{
    Image,
    CSV,
    Excel,
    Dir
};

enum class ImgType
{
    PNG,
    JPG,
    TIF,
    BMP,
    SUPPORTED,
    ALL
};

class FileService : public QObject
{
    Q_OBJECT
public:
    explicit FileService(QObject *parent = nullptr);
    static QString initOpenFileDialog(QString title, FileType fType);
    static QString getTextOfFile(QString path);
    static QString projectDataPath();
    static QString fileTypeStr(FileType fType);
    static QString imgTypeStr(ImgType imgType);
    static QString fileExtension(QString path);
    static QString fileName(QString path);
    static QString concotinateMime(QVector<QString> parts, const QString separator = mime_separator);
    static QString typeByExt(QString extenssion);
    static QString requiredPath(QDir currentDir, const QString &redirect, QString defaultLocation = QString(QStandardPaths::PicturesLocation));
    static QString initOpenImgFileDialog(QFileDialog &dialog, QFileDialog::AcceptMode acceptMode = QFileDialog::AcceptOpen);
};

enum class UsersAction
{
    Save,
    Open,
    Close,
    Cancel,
    Continue
};

enum class MessageType
{
    Status,
    Completed,
    Warrning,
    Error,
    SelectFile,
    SelectCol,
    SuccessfullyReaded
};

enum class ErrorType
{
    EmptyCell,
    FileNotExist,
    DirNotExist,
    CouldntRead
};

class Msg
{
public:
    Msg();
    static QString header(MessageType type);
    static QString body(MessageType type);
    static QString body(ErrorType type);
    static QString wouldYouLike(UsersAction uAct);
    inline static QString endline() { return "\n"; }
    inline static QString ask() { return " ? \n"; }
    inline static QString plus() { return " + "; }
    inline static QString is() { return " : "; }
    inline static QString dir() { return "Directory "; }
    inline static QString file() { return "File "; }
    inline static QString missing() { return " doesn't exist."; }

private:
    static QString getActionString(UsersAction act);
};

#endif // FILESERVICE_H
