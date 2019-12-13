#include "painterwindow.h"
#include "ui_painterwindow.h"

PainterWindow::PainterWindow(QString backgroundFileName, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PainterWindow){
    ui->setupUi(this);
    resize(800, 600);
    setWindowTitle("Painter");

    fileName = nullptr;

    setAction();

    if(backgroundFileName != ""){
        QImage image(backgroundFileName);
        qDebug() << image.size();
        resize(image.size());
    }

    paint2DWidget = new Paint2DWidget(backgroundFileName);
    paint2DWidget->setMode(NONE);
    ui->Canvas->addWidget(paint2DWidget);

    this->show();
}

void PainterWindow::setAction(){
    //文件操作
    fileMenu = ui->menuBar->addMenu("File");
    //新建窗口
    newWindowAction = new QAction("New");
    newWindowAction->setShortcut(QKeySequence::New);
    connect(newWindowAction, SIGNAL(triggered(bool)), this, SLOT(newWindow()));
    //保存文件
    saveFileAction = new QAction("Save");
    saveFileAction->setShortcut(QKeySequence::Save);
    connect(saveFileAction, SIGNAL(triggered(bool)), this, SLOT(saveFile()));
    //复制
    copyAction = new QAction("Copy");
    copyAction->setShortcut(QKeySequence::Copy);
    connect(copyAction, SIGNAL(triggered(bool)), this, SLOT(graphicsCopy_triggered()));
    //粘贴
    pasteAction = new QAction("Paste");
    pasteAction->setShortcut(QKeySequence::Paste);
    connect(pasteAction, SIGNAL(triggered(bool)), this, SLOT(graphicsPaste_triggered()));
    fileMenu->addAction(newWindowAction);
    fileMenu->addAction(saveFileAction);
    fileMenu->addAction(copyAction);
    fileMenu->addAction(pasteAction);


    //图元操作
    transformMenu = ui->menuBar->addMenu("Transform");
    //平移
    translationAction = new QAction("Translation");
    connect(translationAction, SIGNAL(triggered(bool)), this, SLOT(on_actionTranslation_triggered()));
    //旋转
    rotateAction = new QAction("Rotation");
    connect(rotateAction, SIGNAL(triggered(bool)), this, SLOT(on_actionRotation_triggered()));
    //缩放
    scaleAction = new QAction("Scale");
    connect(scaleAction, SIGNAL(triggered(bool)), this, SLOT(on_actionScale_triggered()));
    //缩放
    cropAction = new QAction("Crop");
    connect(cropAction, SIGNAL(triggered(bool)), this, SLOT(on_actionCrop_triggered()));
    transformMenu->addAction(translationAction);
    transformMenu->addAction(rotateAction);
    transformMenu->addAction(scaleAction);
    transformMenu->addAction(cropAction);

    //直线算法选择
    DDAAction = new QAction("DDA");
    connect(DDAAction, SIGNAL(triggered(bool)), this, SLOT(on_actionDDA_triggered()));
    BresenhamAction = new QAction("BresenHam");
    connect(BresenhamAction, SIGNAL(triggered(bool)), this, SLOT(on_actionBresenHam_triggered()));
    ui->LineToolButton->addAction(DDAAction);
    ui->LineToolButton->addAction(BresenhamAction);

    //裁剪算法选择
    CSAction = new QAction("CS");
    connect(CSAction, SIGNAL(triggered(bool)), this, SLOT(on_actionCS_triggered()));
    LBAction = new QAction("LB");
    connect(LBAction, SIGNAL(triggered(bool)), this, SLOT(on_actionLB_triggered()));
    ui->CropToolButton->addAction(CSAction);
    ui->CropToolButton->addAction(LBAction);

    //曲线算法选择
    BezierAction = new QAction("Bezier");
    connect(BezierAction, SIGNAL(triggered(bool)), this, SLOT(on_actionBezier_triggered()));
    BsplineAction = new QAction("Bspline");
    connect(BsplineAction, SIGNAL(triggered(bool)), this, SLOT(on_actionBspline_triggered()));
    ui->CurveToolButton->addAction(BezierAction);
    ui->CurveToolButton->addAction(BsplineAction);
}

PainterWindow::~PainterWindow(){
    delete ui;
}

/**
 * @brief PainterWindow::newOneFile
 * 新建一个窗口
 */
void PainterWindow::newWindow(){
    PainterWindow* newWindow = new PainterWindow;
    newWindow->show();
}

bool PainterWindow::saveFile(){
    if(fileName == nullptr){
        fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "newPic", tr("Image (*.jpg)"));
    }
    if(fileName == "")  return false;
    fileName = fileName.toUtf8();
    paint2DWidget->saveTo(fileName);
    return true;
}

void PainterWindow::closeEvent(QCloseEvent* event){
    if (paint2DWidget->getIsModified()){
        int temp = QMessageBox::information(this, "File Not Saved", "文件未保存，是否保存？", QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (temp == QMessageBox::Yes){              //保存
            if(saveFile()){
                event->accept();
            }else{
                event->ignore();
            }
        }
        else if(temp == QMessageBox::No){           //不保存
            event->accept();
        }else{                                      //取消关闭
            event->ignore();
        }
    }
    else{
        event->accept();
    }
}

/**
 * @brief PainterWindow::resizeEvent
 * @param event
 * 检测窗口改变，调整大小
 */
void PainterWindow::resizeEvent(QResizeEvent*){
    ui->HSpinBox->setValue(this->height());
    ui->WSpinBox->setValue(this->width());
}

void PainterWindow::on_actionDDA_triggered(){
    ui->LineToolButton->setText("DDA");
    paint2DWidget->setLineAlgorithm(DDA);
}

void PainterWindow::on_actionBresenHam_triggered(){
    ui->LineToolButton->setText("BresenHam");
    paint2DWidget->setLineAlgorithm(BRESENHAM);
}

void PainterWindow::on_actionCS_triggered(){
    ui->CropToolButton->setText("CS");
    paint2DWidget->setCropAlgorithm(CS);
}

void PainterWindow::on_actionLB_triggered(){
    ui->CropToolButton->setText("LB");
    paint2DWidget->setCropAlgorithm(LB);
}

void PainterWindow::on_actionBezier_triggered(){
    ui->CurveToolButton->setText("Bezier");
    paint2DWidget->setCurveAlgorithm(BEZIER);
}

void PainterWindow::on_actionBspline_triggered(){
    ui->CurveToolButton->setText("Bspline");
    paint2DWidget->setCurveAlgorithm(BSPLINE);
}

void PainterWindow::on_LineSegmentButton_clicked(){
    paint2DWidget->setMode(LINESEGMENT);
    ui->ModeLabel->setText("LineSegment");
}

void PainterWindow::on_RandomLineButton_clicked(){
    paint2DWidget->setMode(RANDOMLINE);
    ui->ModeLabel->setText("RandomLine");
}

void PainterWindow::on_PolygonButton_clicked(){
    paint2DWidget->setMode(POLYGON);
    ui->ModeLabel->setText("Polygon");
}

void PainterWindow::on_CircleButton_clicked(){
    paint2DWidget->setMode(CIRCLE);
    ui->ModeLabel->setText("Circle");
}

void PainterWindow::on_EllipseButton_clicked(){
    paint2DWidget->setMode(ELLIPSE);
    ui->ModeLabel->setText("Ellipse");
}

void PainterWindow::on_CurveButton_clicked(){
    paint2DWidget->setMode(CURVE);
    ui->ModeLabel->setText("Curve");
}

void PainterWindow::on_ColorButton_clicked(){
    paint2DWidget->setColor(QColorDialog::getColor());
}

void PainterWindow::on_EraserButton_clicked(){
    paint2DWidget->setMode(ERASER);
    ui->ModeLabel->setText("Eraser");
}

void PainterWindow::on_WithDrawButton_clicked(){
//    ui->ModeLabel->setText("WithDraw");
    paint2DWidget->withDraw();
}

void PainterWindow::on_ReDoButton_clicked(){
    paint2DWidget->reDraw();
}

void PainterWindow::on_WidthSpinBox_valueChanged(int arg1){
    paint2DWidget->setWidth(arg1);
}

void PainterWindow::on_WSpinBox_valueChanged(int arg1){
    resize(arg1, this->height());
}

void PainterWindow::on_HSpinBox_valueChanged(int arg1){
    resize(this->width(), arg1);
}

void PainterWindow::on_KSpinBox_valueChanged(int arg1){
    paint2DWidget->setK(arg1);
}

void PainterWindow::on_actionTranslation_triggered(){
    ui->ModeLabel->setText("Translation");
    paint2DWidget->setMode(TRANSLATION);
}

void PainterWindow::on_actionRotation_triggered(){
    ui->ModeLabel->setText("Rotation");
    paint2DWidget->setMode(ROTATION);
}

void PainterWindow::on_actionScale_triggered(){
    ui->ModeLabel->setText("Scale");
    paint2DWidget->setMode(SCALE);
}

void PainterWindow::on_actionCrop_triggered(){
    ui->ModeLabel->setText("Crop");
    paint2DWidget->setMode(CROP);
}

void PainterWindow::on_SelectButton_clicked(){
    ui->ModeLabel->setText("Select");
    paint2DWidget->setMode(SELECT);
}

void PainterWindow::graphicsCopy_triggered(){
    ui->ModeLabel->setText("Copy");
    paint2DWidget->graphicsCopy();
}

void PainterWindow::graphicsPaste_triggered(){
    ui->ModeLabel->setText("Paste");
    paint2DWidget->graphicsPaste();
    ui->ModeLabel->setText("Translation");
}

void PainterWindow::on_SelectBlockButton_clicked(){
    ui->ModeLabel->setText("Select Block");
    paint2DWidget->setMode(SELECTBOLCK);
}

void PainterWindow::on_ResetButton_clicked(){
    ui->ModeLabel->setText("None");
    ui->WidthSpinBox->setValue(1);
    ui->LineToolButton->setText("BresenHam");
    ui->CropToolButton->setText("CS");
    ui->CurveToolButton->setText("Bezier");
    ui->KSpinBox->setValue(3);
    paint2DWidget->reset();
}
