//Фильтры типа файлов
#define TFS ";;"
//по названию (Отсеивание конкретно этих типов среди остальных )
#define N_F_PNG QString("PNG Images (*.png)")
#define N_F_BMP QString("Bitmap Image (*.bmp)")
#define N_F_JPG QString("JPG Images (*.jpg)")
#define N_F_TIF QString("TIF Images (*.tif)")
#define N_F_ALL (N_F_BMP + TFS + N_F_JPG + TFS + N_F_PNG + TFS + N_F_TIF)

//По типу группы формата для интернета ()
#define MIME_BMP QString("image/bmp")
#define MIME_PNG QString("image/png")
#define MIME_JPG QString("image/jpg")
#define MIME_TIF QString("img/tif")
#define MIME_ALL (MIME_BMP + TFS + MIME_JPG + TFS + MIME_PNG + TFS + MIME_TIF)

//Фильтры суффикса
#define S_F_BMP QString("bmp" )
#define S_F_PNG QString("png" )
#define S_F_JPG QString("jpg" )
#define S_F_TIF QString("tif" )
#define S_F_ALL (S_F_BMP + TFS + S_F_JPG + TFS + S_F_PNG + TFS + S_F_TIF)

//Стиль кнопки колорпикера
#define CLR_PCKR_STYLE "border: 1px solid black; background-color: "

//Диалоговые окна:
    // Сообщения
#define OPEN_FAILED "Не могу загрузить изображение %1: %2"
#define OPEN_SUCCESS "Открыто изображение \"%1\", %2x%3, Depth: %4"
#define SAVE_FAILED "Не могу сохранить изображение %1: %2"
#define SAVED_SUCCESS "Сохранено изображение \"%1\" "