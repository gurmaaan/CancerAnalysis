#include "filewidget.h"
#include "ui_filewidget.h"

const QString _CSV_ = "csv";

FileWidget::FileWidget(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::FileWidget)
{
    ui->setupUi(this);

    name_ = "File ";
    path_ = QDir::currentPath();
    type_ = FileType::Dir;
    rowCnt_ = 0;
    colCnt_ = 0;
    progress_= 0;
}

FileWidget::~FileWidget()
{
    delete ui;
}

void FileWidget::setName(const QString &name)
{
    name_ = name;
    nameChanged(name_);
    setTitle(name_);
}

void FileWidget::setPath(const QString &path)
{
    QFileInfo fi(path);
    if(fi.exists())
    {
        path_ = path;
        emit filePathChanged(path_);
        ui->pathLineEdit->setText(path);
        setName(FileService::fileName(path));

        if(FileService::fileExtension(path) == _CSV_)
            setType(FileType::CSV);
    }
    else
    {
        //TODO:: месадж бокс ошибки если юзер выбрал не тот файл и запуск открытия по новой
        //open error msg box
        //reopen file
    }
}

void FileWidget::setFirstColOfFirstRowText(const QString &fileText)
{
    ui->customPlainText->setPlainText(fileText);
}

void FileWidget::setType(const FileType &type)
{
    type_ = type;
    ui->typeCB->addItem(FileService::fileTypeStr(type_));
}

void FileWidget::setRowCnt(int rowCnt)
{
    //вызывается при адой новой обработке объекта, здесь это текущая строка
    rowCnt_ = rowCnt;
    ui->sizeRowSpin->setMaximum(rowCnt_);
    ui->sizeRowSpin->setValue(rowCnt_);
    ui->progressBar->setMaximum(rowCnt_ - 1);

    emit fileRowsCntChanged(rowCnt_);
}

void FileWidget::setColCnt(int colCnt)
{
    colCnt_ = colCnt;
    ui->sizeColSpin->setMaximum(colCnt_);
    ui->sizeColSpin->setValue(colCnt_);

    emit fileColsCntChanged(colCnt_);
}

void FileWidget::setProgress(int currentRow)
{
    progress_ = currentRow;
    ui->progressBar->setValue(progress_);
}

void FileWidget::on_pathBtn_clicked()
{
    ui->actionOpen_File->trigger();
}

void FileWidget::on_actionOpen_File_triggered()
{
    QString fp = FileService::initDialogAndGetOpenedFileName(Msg::header(MessageType::SelectFile), FileType::CSV);
    setPath(fp);

    QString ft = FileService::getTextOfFile(fp);
    setColCnt( StringService::splitAndRemoveFirstColOfFirstRow(ft).count());
    setRowCnt(StringService::splitAndRemoveFirstRow(ft).count());
    emit fileTextChanged(ft);

    setFirstColOfFirstRowText( StringService::multipleLineFromSingle( StringService::getCornerString(ft) ,"   ", 2 ) );
}
