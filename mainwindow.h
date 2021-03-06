#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <math.h>
#include <map>

#include <QtGui>
#include <QtWidgets>
#include <QtCore>
#include <QDebug>
#include <qcustomplot/qcustomplot.h>

#include <Vector.h>

#include <HeaderWidget.h>
#include <FooterWidget.h>

class Experiment;
class Resp;
class historyWidget;
class deformWidget;
class responseWidget;
class hysteresisWidget;

// organization of sxnShape
enum class sxnShape {
    W,
    M,
    S,
    HP,
    C,
    MC,
    L,
    dL,
    WT,
    MT,
    ST,
    HSS,
    RND,
    PIPE
};

// struct for materials
struct steel {
    double fy;
    double Es;
    // kinematic hardening - tension
    double bk;
    double R0k;
    double r1;
    double r2;
    // kinematic hardening - compression
    double bkc;
    double R0kc;
    double r1c;
    double r2c;
    // isotropic hardening - tension
    double bi;
    double rhoi;
    double bl;
    double Ri;
    double lyp;
    // isotropic hardening - compression
    double bic;
    double rhoic;
    double blc;
    double Ric;
    // asymmetric inputs
    double a1;
    double a2;
    double a3;
    double a4;
};

// fatigue structure
struct fat {
    double m;
    double e0;
    double emin;
    double emax;
};

// section struct
struct section {
    double A;
    double Ix;
    double Zx;
    double Sx;
    double rx;
    double Iy;
    double Zy;
    double Sy;
    double ry;
    double I;
    double Z;
    double S;
    double r;
    // sxn geom
    double d;
    double bf;
    double tw;
    double tf;
    // combactness
    double bftf;
    double htw;
};

// connection struct
struct connection { // see Chambers, J. J., & Bartley, T. C. (2009). Erratum: Geometric formulas for gusset plate design ((2007), (258)). Engineering Journal.
    double fy; // gusset material
    double Es;
    double tg; // gusset plate thickness
    double H; // total gusset height
    double W; // total gusset width
    double lb; // gusset length along beam
    double lc; // gusset length along column
    double lbr; // gusset length along brace
    double eb; // depth of column
    double ec; // depth of beam
    double L; // length of gusset
    double rigA; // length of gusset
    double rigI; // length of gusset
};

// create struct for **
struct doublePointer {
    int steps;
    int size;
    QVector<double> **data;
};

// size
struct windowSize {
    int width;
    int height;
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // analysis
    void buildModel();

    // Actions for open and saving files
    void open();
    bool save();
    bool saveAs();
    
    // Options for Help menu
    void about();
    void submitFeedback();
    void version();
    void copyright();

    // custom plots
    //void dPlot(QCustomPlot *plot, int Fig);

private slots:
    // pushButton
    void addExp_clicked();
    void addAISC_clicked();
    void theAISC_sectionClicked(int row);
    void reset();
    void doAnalysis();
    //void stop_clicked();
    void play_clicked();
    void pause_clicked();
    void restart_clicked();

    //connect(play,SIGNAL(clicked()), this, SLOT(play_clicked()));
    //connect(stop,SIGNAL(clicked()), this, SLOT(stop_clicked()));
    //connect(reset,SIGNAL(clicked()), this, SLOT(reset_clicked()));

    // Combo Box
    void inSxn_currentIndexChanged(int row);
    void inOrient_currentIndexChanged(int row);
    void inElType_currentIndexChanged(int row);
    void inElDist_currentIndexChanged(int row);
    void inIM_currentIndexChanged(int row);
    void inShape_currentIndexChanged(int row);
    void inMat_currentIndexChanged(int row);
    void in_conn1_currentIndexChanged(int row);
    void in_conn2_currentIndexChanged(int row);

    // Spin box
    void inNe_valueChanged(int var);
    void inNIP_valueChanged(int var);
    void inNbf_valueChanged(int var);
    void inNtf_valueChanged(int var);
    void inNd_valueChanged(int var);
    void inNtw_valueChanged(int var);

    // double spin box
    void inLwp_valueChanged(double var);
    void inL_valueChanged(double var);
    void inDelta_valueChanged(double var);
    void inEs_valueChanged(double var);
    void infy_valueChanged(double var);
    //
    void inb_valueChanged(double var);
    //
    void ina1_valueChanged(double var);
    void ina2_valueChanged(double var);
    void ina3_valueChanged(double var);
    void ina4_valueChanged(double var);
    //
    void inR0_valueChanged(double var);
    void inR1_valueChanged(double var);
    void inR2_valueChanged(double var);
    //
    void inbk_valueChanged(double var);
    void inR0k_valueChanged(double var);
    void inr1_valueChanged(double var);
    void inr2_valueChanged(double var);
    void inbkc_valueChanged(double var);
    void inR0kc_valueChanged(double var);
    void inr1c_valueChanged(double var);
    void inr2c_valueChanged(double var);
    //
    void inbi_valueChanged(double var);
    void inrhoi_valueChanged(double var);
    void inbl_valueChanged(double var);
    void inRi_valueChanged(double var);
    void inlyp_valueChanged(double var);
    void inbic_valueChanged(double var);
    void inrhoic_valueChanged(double var);
    void inblc_valueChanged(double var);
    void inRic_valueChanged(double var);
    //
    void inm_valueChanged(double var);
    void ine0_valueChanged(double var);
    void inemin_valueChanged(double var);
    void inemax_valueChanged(double var);
    //
    void inl_conn1_valueChanged(double var);
    void inRigA_conn1_valueChanged(double var);
    void inRigI_conn1_valueChanged(double var);
    //
    void inl_conn2_valueChanged(double var);
    void inRigA_conn2_valueChanged(double var);
    void inRigI_conn2_valueChanged(double var);

    // check box
    //void includePDeltaChanged(int);
    void matDefault_checked(int);
    void matAsymm_checked(int);
    void matFat_checked(int);
    void connSymm_checked(int);

    // slider
    void slider_valueChanged(int value);
    //void slider_sliderPressed();
    //void slider_sliderReleased();

private:
    Ui::MainWindow *ui;

    // main layouts
    void createHeaderBox();
    void createFooterBox();
    void createInputPanel();
    void createOutputPanel();
    void createActions();    

    // load information
    void loadAISC();
    void setExp(Experiment *exp);
    void initialize();
    void zeroResponse();

    // plot
    void repaint();

    // methods for loading and saving files given filename
    void setCurrentFile(const QString &fileName);
    bool saveFile(const QString &fileName);
    void loadFile(const QString &fileName);

    // initialize

    // created main layouts
    QHBoxLayout *mainLayout;
    QVBoxLayout *largeLayout;
    //QHBoxLayout *headerLayout;
    //QHBoxLayout *footerLayout;
    QGridLayout *outLay;
    QVBoxLayout *inLay;

    // Button
    QPushButton *addExp;
    QPushButton *addAISC;

    // Combo Box
    QComboBox *inExp;
    QComboBox *inSxn;
    QComboBox *inElType;
    QComboBox *inElDist;
    QComboBox *inIM;
    QComboBox *inShape;
    QComboBox *inOrient;
    QComboBox *inMat;
    QComboBox *in_conn1;
    QComboBox *in_conn2;

    // spin box    
    QSpinBox *inNe;
    QSpinBox *inNIP;
    QSpinBox *inNbf;
    QSpinBox *inNtf;
    QSpinBox *inNd;
    QSpinBox *inNtw;

    // double spin box
    QDoubleSpinBox *inLwp;
    QDoubleSpinBox *inL;
    QDoubleSpinBox *inDelta;
    //
    QDoubleSpinBox *inEs;
    QDoubleSpinBox *infy;
    //
    QDoubleSpinBox *inb;
    //
    QDoubleSpinBox *ina1;
    QDoubleSpinBox *ina2;
    QDoubleSpinBox *ina3;
    QDoubleSpinBox *ina4;
    //
    QDoubleSpinBox *inR0;
    QDoubleSpinBox *inR1;
    QDoubleSpinBox *inR2;
    //
    QDoubleSpinBox *inbk;
    QDoubleSpinBox *inR0k;
    QDoubleSpinBox *inr1;
    QDoubleSpinBox *inr2;
    QDoubleSpinBox *inbkc;
    QDoubleSpinBox *inR0kc;
    QDoubleSpinBox *inr1c;
    QDoubleSpinBox *inr2c;
    //
    QDoubleSpinBox *inbi;
    QDoubleSpinBox *inrhoi;
    QDoubleSpinBox *inbl;
    QDoubleSpinBox *inRi;
    QDoubleSpinBox *inlyp;
    QDoubleSpinBox *inbic;
    QDoubleSpinBox *inrhoic;
    QDoubleSpinBox *inblc;
    QDoubleSpinBox *inRic;
    //
    QDoubleSpinBox *inm;
    QDoubleSpinBox *ine0;
    QDoubleSpinBox *inemin;
    QDoubleSpinBox *inemax;
    // connection-1
    //QDoubleSpinBox *infy_conn1;
    //QDoubleSpinBox *inEs_conn1;
    //QDoubleSpinBox *inb_conn1;
    //QDoubleSpinBox *intg_conn1;
    QDoubleSpinBox *inl_conn1;
    //QDoubleSpinBox *inlw_conn1;
    QDoubleSpinBox *inRigA_conn1;
    QDoubleSpinBox *inRigI_conn1;
    // connection-2
    //QDoubleSpinBox *infy_conn2;
    //QDoubleSpinBox *inEs_conn2;
    //QDoubleSpinBox *inb_conn2;
    //QDoubleSpinBox *intg_conn2;
    QDoubleSpinBox *inl_conn2;
    //QDoubleSpinBox *inlw_conn2;
    QDoubleSpinBox *inRigA_conn2;
    QDoubleSpinBox *inRigI_conn2;

    // check box
    QCheckBox *matDefault;
    QCheckBox *matAsymm;
    QCheckBox *matFat;
    QCheckBox *connSymm;

    // group box
    QGroupBox *bBox;
    QGroupBox *steel01Box;
    QGroupBox *steel02Box;
    QGroupBox *kinBox;
    QGroupBox *isoBox;
    QGroupBox *cKinBox;
    QGroupBox *cIsoBox;
    QGroupBox *fatBox;

    // frame
    QFrame *steel4Frame;

    // labels
    QLabel *deltaL;
    QLabel *Alabel;
    QLabel *Ilabel;
    QLabel *Zlabel;
    QLabel *Slabel;
    QLabel *rlabel;
    QLabel *tlabel;
    QLabel *dlabel;
    QLabel *bflabel;
    QLabel *twlabel;
    QLabel *tflabel;

    // QList
    QList<QStandardItem *> sxnProp; // huh?? want to grab row of QStandardItemModel
    // AISC lists
    QStandardItemModel *AISCshapes;
    QStringList propList;
    QStringList sxnList;

    // QStrings
    QString sxn;
    QString orient;
    QString elType;
    QString elDist;
    QString IM;
    QString shape;
    QString mat;

    // enums
    sxnShape sxnType;

    // QSlider
    QSlider *slider;

    // window size
    windowSize wSize;

    // ints
    int ne; // # of elements
    int nn; // # of nodes
    int NIP; // # of integration points
    int nbf; // # of fibers across flange width
    int ntf; // # of fibers across flange thickness
    int nd; // # of fibers across depth
    int ntw; // # of fibers across web depth
    int stepCurr;
    int type_conn1;
    int type_conn2;

    // doubles
    // constants
    double pi;
    // geom
    double Lwp;
    double L;
    double delta;
    double angle;
    // mat
    steel theSteel;
    fat theFat;
    // sxn prop
    section theSxn;
    // connection
    connection conn1;
    connection conn2;

    // bools
    bool inclDefault;
    bool inclAsymm;
    bool inclFat;
    bool inclConnSymm;
    //bool movSlider;
    bool pause;
    bool stop;

    // coordinates
    QVector<double> xc;
    QVector<double> yc;

    // experiment
    int numSteps;
    QVector<double> *expD;
    QVector<double> *expP;
    QVector<double> *time;
    QString experimentType;
    double dt;

    // response
    Resp *Ux;
    Resp *Uy;
    Resp *q1;
    Resp *q2;
    Resp *q3;

    // output widgets
    deformWidget *dPlot;
    historyWidget *tPlot;
    responseWidget *pPlot;
    responseWidget *mPlot;
    responseWidget *kPlot;
    hysteresisWidget *hPlot;

    // Name of current file
    QString currentFile;
    double braceHeight;
    double braceWidth;
};

#endif // MAINWINDOW_H
