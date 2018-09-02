#include "fileservice.h"

const QString _DATA_PATH_ = "ParamsViewer/data";

FileService::FileService(QObject *parent) : QObject(parent)
{

}

QString FileService::initDialogAndGetOpenedFileName(QString title, FileType fType)
{
    QString fileName = QFileDialog::getOpenFileName(nullptr, title, requiredPath(QDir::current(), _DATA_PATH_), FileService::fileTypeStr(fType) );
    return fileName;
}

QString FileService::requiredPath(QDir currentDir, const QString &redirect, QString defaultLocation)
{

#ifdef Q_OS_MAC
    currentDir.cdUp();
    currentDir.cdUp();
    currentDir.cdUp();
#endif

    currentDir.cdUp();
    currentDir.cd(redirect);
    QString path = (currentDir.exists()) ?  currentDir.absolutePath() : defaultLocation;

    if(currentDir.exists())
    {
        return path;
    } else
    {
       qDebug() << Msg::dir() << currentDir.absolutePath() << Msg::plus() <<  redirect << Msg::missing();
       return "";
    }
}

QString FileService::getTextOfFile(QString path)
{
    QFile file(path);
    QString textOfFile;
    if ( !file.open(QFile::ReadOnly | QFile::Text ) )
    {
        qDebug() << QString(Msg::body(ErrorType::FileNotExist));
        textOfFile = "";
    } else
    {
         QTextStream in(&file);
         in.setCodec(QTextCodec::codecForName(ENCODING));
         textOfFile = in.readAll();
    }
    Msg::body(MessageType::SuccessfullyReaded);
    file.close();
    return textOfFile;
}

QString FileService::fileTypeStr(FileType fType)
{
    QString fileTypeStr = tr("*");
    switch (fType) {
    case FileType::Image:
        fileTypeStr = tr("Image PNG(*.png);;Image JPG(*.jpg);;Image BMP(*.bmp);;");
        break;
    case FileType::CSV:
        fileTypeStr = tr("Comma Separatred table *.CSV");
        break;
    case FileType::Excel:
        fileTypeStr = tr("Excel spreadsheet(*.xls*)");
        break;
    case FileType::Dir:
        fileTypeStr = tr("Folder");
        break;
    }
    return fileTypeStr;
}

QString FileService::fileExtension(QString path)
{
    QString fileExtension = path.split(".").last();
    return fileExtension;
}

QString FileService::fileName(QString path)
{
    QString fileName;
    if(path.contains("\\"))
        fileName = path.split("\\").last();
    else
    {
        QFileInfo fi(path);
        fileName = fi.fileName();
    }

    return fileName;
}


Msg::Msg() {}

QString Msg::getActionString(UsersAction act)
{
    QString actionStr = " ";
    switch (act)
    {
        case UsersAction::Save:
            actionStr = "save";
            break;
        case UsersAction::Open:
            actionStr = "open";
            break;
        case UsersAction::Close:
            actionStr = "close";
            break;
        case UsersAction::Cancel:
            actionStr = "Cancel";
            break;
        case UsersAction::Continue:
            actionStr = "continue";
            break;
    }
    return actionStr;
}

QString Msg::header(MessageType type)
{
    QString messageHeaderStr = " ";
    switch (type)
    {
        case MessageType::Status:
            messageHeaderStr = "Status of ";
            break;
        case MessageType::Completed:
            messageHeaderStr = "The operation completed";
            break;
        case MessageType::Warrning:
            messageHeaderStr = "Warning";
            break;
        case MessageType::Error:
            messageHeaderStr = "Error";
            break;
        case MessageType::SelectFile:
            messageHeaderStr = "Please select the file";
            break;
        case MessageType::SelectCol:
            messageHeaderStr = "Select the column";
            break;
        default:
            messageHeaderStr = " ";
            break;
    }
    return messageHeaderStr;
}

QString Msg::body(MessageType type)
{
    QString mesgBody = "";
    switch (type)
    {
    case MessageType::Completed:
        mesgBody = "The block completed in ";
        break;
    case MessageType::Warrning:
        mesgBody = "Warning! ";
        break;
    case MessageType::Error:
        mesgBody = "Error";
        break;
    case MessageType::SelectFile:
        mesgBody = "Please chose the file with ";
        break;
    case MessageType::SelectCol:
        mesgBody = "Select the column...";
        break;
    case MessageType::SuccessfullyReaded:
        mesgBody = file() + "successfully readed. ";
    default:
        mesgBody = " ";
        break;
    }
    return mesgBody;
}

QString Msg::body(ErrorType type)
{
    QString errMsg = " ";
    switch (type)
    {
        case ErrorType::EmptyCell:
            errMsg = "The document contains empty cells.";
            break;
        case ErrorType::FileNotExist:
            errMsg = "File doesn't exist";
            break;
        case ErrorType::DirNotExist:
            errMsg = "Directory doesn't exist";
            break;
        default:
            errMsg = " ";
            break;
    }
    return errMsg;
}

QString Msg::wouldYouLike(UsersAction uAct)
{
    return "Would you like to " + getActionString(uAct) + ask();
}

