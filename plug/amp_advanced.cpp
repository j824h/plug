#include "amp_advanced.h"
#include "ui_amp_advanced.h"

Amp_Advanced::Amp_Advanced(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Amp_Advanced)
{
    ui->setupUi(this);

    ui->dial_5->setDisabled(true);
    ui->spinBox_5->setDisabled(true);
    ui->dial_4->setDisabled(true);
    ui->spinBox_4->setDisabled(true);

    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), parent, SLOT(set_cabinet(int)));
    connect(ui->comboBox_2, SIGNAL(currentIndexChanged(int)), parent, SLOT(set_noise_gate(int)));
    connect(ui->comboBox_2, SIGNAL(currentIndexChanged(int)), this, SLOT(activate_custom_ng(int)));
    connect(ui->dial, SIGNAL(valueChanged(int)), parent, SLOT(set_master_vol(int)));
    connect(ui->dial_2, SIGNAL(valueChanged(int)), parent, SLOT(set_gain2(int)));
    connect(ui->dial_3, SIGNAL(valueChanged(int)), parent, SLOT(set_presence(int)));
    connect(ui->dial_4, SIGNAL(valueChanged(int)), parent, SLOT(set_depth(int)));
    connect(ui->dial_5, SIGNAL(valueChanged(int)), parent, SLOT(set_threshold(int)));
    connect(ui->dial_6, SIGNAL(valueChanged(int)), parent, SLOT(set_bias(int)));
    connect(ui->dial_7, SIGNAL(valueChanged(int)), parent, SLOT(set_sag(int)));
}

Amp_Advanced::~Amp_Advanced()
{
    delete ui;
}

void Amp_Advanced::change_cabinet(int value)
{
    ui->comboBox->setCurrentIndex(value);
}

void Amp_Advanced::change_noise_gate(int value)
{
    ui->comboBox_2->setCurrentIndex(value);
}

void Amp_Advanced::activate_custom_ng(int value)
{
    if(value == 5)
    {
        ui->dial_5->setDisabled(false);
        ui->spinBox_5->setDisabled(false);
        ui->dial_4->setDisabled(false);
        ui->spinBox_4->setDisabled(false);
    }
    else
    {
        ui->dial_5->setDisabled(true);
        ui->spinBox_5->setDisabled(true);
        ui->dial_4->setDisabled(true);
        ui->spinBox_4->setDisabled(true);
    }
}
