#include "fileservice.h"

//Folder name where located data for basic (test) usage
//Redirect function will be _ProjectName/data_path

const QString data_path = "/test";
const QString mime_separator = ";;";

FileService::FileService(QObject *parent) : QObject(parent)
{

}

QString FileService::initOpenFileDialog(QString title, FileType fType)
{
    QString fileName = " ";
    if(fType != FileType::Image)
        fileName = QFileDialog::getOpenFileName(nullptr, title, requiredPath(QDir::current(), projectDataPath()), fileTypeStr(fType) );
    else
    {
        QFileDialog d;
        fileName = initOpenImgFileDialog(d);
    }
    return fileName;
}

QString FileService::requiredPath(QDir currentDir, const QString &redirect, QString defaultLocation)
{

#ifdef Q_OS_MAC
    currentDir.cdUp();
    currentDir.cdUp();


#endif
    currentDir.cdUp();
    currentDir.cdUp();
    currentDir.cdUp();
    qDebug() << currentDir.path();
    currentDir.cd(redirect);
    qDebug() << currentDir.path();
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

QString FileService::projectDataPath()
{
    QString path = QString("_") + QApplication::applicationName() + QString(data_path);
    return path;
}


QString FileService::initOpenImgFileDialog(QFileDialog &dialog, QFileDialog::AcceptMode acceptMode)
{
    static bool firstDialog = true;

    if (firstDialog)
    {
        firstDialog = false;
        const QStringList myPicturesPath = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
        dialog.setDirectory( !myPicturesPath.isEmpty() ? requiredPath(QApplication::applicationFilePath(), projectDataPath(), myPicturesPath.last()) : myPicturesPath.last() ); //WARNING Change required
    }

    //Создали лист бит => получаем список поддерживаемыхх форматов системй!! в зависимости от открытия или сохранения картинки
    const QByteArrayList supportedTypes = acceptMode == QFileDialog::AcceptOpen
        ? QImageReader::supportedMimeTypes() : QImageWriter::supportedMimeTypes();


    //Из полученного массива извлекаем строки названия формата по которому будут фильтроваться файлы в диалоге (поддерживаемые типы картинок)
    QStringList typeFilter;
    for(auto &mimeTypeName : supportedTypes)
        typeFilter.append(mimeTypeName);
    typeFilter.sort();

    dialog.setMimeTypeFilters(typeFilter); //Установить фильтр на файлы - отображать только изображения любого типа (как в списке так и видно)
    dialog.selectMimeTypeFilter(FileService::imgTypeStr(ImgType::SUPPORTED)); //Среди полученных выбрать группу опр формата

    if (acceptMode == QFileDialog::AcceptSave)
        dialog.setDefaultSuffix( FileService::imgTypeStr(ImgType::SUPPORTED) ); //При сохранении сам добавляет выбранный суффикс (.формат) к файлы

    return dialog.getOpenFileName();
}

QString FileService::concotinateMime(QVector<QString> parts, const QString separator)
{
    QString sum = "";
    for (auto iter = parts.begin(); iter < parts.end(); ++iter) {
        sum += (iter + separator);
    }
    sum += parts.last();
    return sum;
}

QString FileService::typeByExt(QString extenssion)
{
    QString type = "";
    if (extenssion == "bmp")
        type = "bmp Windows Bitmap";
    if (extenssion == "jpg")
        type = "jpeg Joint Photographic Experts Group";
    if (extenssion == "png")
        type = "png Portable Network Graphics";
    if (extenssion == "pbm")
        type = "x-portable-bitmap Portable Bitmap";
    if (extenssion == "pgm")
        type = "x-portable-graymap Portable Graymap";
    if (extenssion == "ppm")
        type = "x-portable-pixmap Portable Pixmap";
    if (extenssion == "xbm")
        type = "x-xbitmap X11 Bitmap";
    if (extenssion == "xpm")
        type = "x-xpixmap X11 Pixmap";
    if (extenssion == "tif")
        type = "tifа Tagged Image File Format";
    return type;
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
        fileTypeStr = tr("Image PNG(*.png);;Image JPG(*.jpg);;Image BMP(*.bmp);;Tagged Image TIF(*.tif);;");
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

QString FileService::imgTypeStr(ImgType imgType)
{
    QString imgFileExtenssion = "";
    switch (imgType)
    {
        case ImgType::PNG:
        {
            imgFileExtenssion = "png";
            break;
        }
        case ImgType::JPG:
        {
            imgFileExtenssion = "jpg";
            break;
        }
        case ImgType::TIF:
        {
            imgFileExtenssion = "tif";
            break;
        }
        case ImgType::BMP:
        {
            imgFileExtenssion = "bmp";
            break;
        }
        case ImgType::SUPPORTED:
        {
            QVector<QString> exts(4);
            exts << "png" << "jpg" << "tif" << "bmp";
            imgFileExtenssion = concotinateMime(exts);
            break;
        }
        default:
        {
            QVector<QString> formatsList;
            const QByteArrayList supportedTypes = QImageReader::supportedMimeTypes();
            for(auto type : supportedTypes)
                formatsList.append(type);
            imgFileExtenssion = concotinateMime(formatsList);
        }
    }
    return  imgFileExtenssion;
}

QString FileService::fileExtension(QString path)
{
    QString fileExtension = "";
    if(path.count(".") >= 1)
        fileExtension = path.split(".").last();
    else
        fileExtension = ".*";
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
        break;
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
    case ErrorType::CouldntRead:
        errMsg = "Couldn't read the image";
        break;
//        default:
//            errMsg = " ";
//            break;
    }
    return errMsg;
}

QString Msg::wouldYouLike(UsersAction uAct)
{
    return "Would you like to " + getActionString(uAct) + ask();
}

