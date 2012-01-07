#include "filemanagersettingswidget.h"
#include "ui_filemanagersettingswidget.h"

#include <QtCore/QSettings>
#include <QtCore/QSignalMapper>
#include <coreplugin/core.h>
#include <coreplugin/settings.h>

#include "filemanagersettings.h"
#include "navigationmodel.h"

#include <QDebug>

using namespace CorePlugin;
using namespace FileManagerPlugin;

static int readFlags()
{
    int flags = 0;

    Settings *s = Core::instance()->settings();
    s->beginGroup(QLatin1String("fileManager"));
    if (s->contains(QLatin1String("standardLocations"))) {
        flags = s->value(QLatin1String("standardLocations")).toInt();
    } else {
        flags = NavigationModel::DesktopLocation |
                NavigationModel::DocumentsLocation |
                NavigationModel::HomeLocation |
                NavigationModel::ApplicationsLocation;
    }
    s->endGroup();

    return flags;
}

FileManagerSettingsWidget::FileManagerSettingsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileManagerSettingsWidget),
    m_settings(new QSettings(this)),
    m_fileManagerSettings(FileManagerSettings::globalSettings())
{
    ui->setupUi(this);

    m_settings->beginGroup(QLatin1String("fileManager"));

    setupLeftPanel();
    setupIconSize();
    setupGridSize();
    setupFlow();
}

FileManagerSettingsWidget::~FileManagerSettingsWidget()
{
    delete ui;
}

void FileManagerSettingsWidget::onChecked(bool checked)
{
    int flags = readFlags();

    if (checked)
        flags = flags | sender()->property("flag").toInt();
    else
        flags = flags & ~sender()->property("flag").toInt();

    Settings *s = Core::instance()->settings();
    s->beginGroup(QLatin1String("fileManager"));
    s->setValue(QLatin1String("standardLocations"), flags);
    s->endGroup();
}

void FileManagerSettingsWidget::onIconSizeChanged(int value)
{
    value *= 4;
    QSize size(value, value);
    ui->iconSizeLabel->setText(tr("Icon size: %1x%2").arg(value).arg(value));

    m_settings->setValue(QLatin1String("iconSize"), size);
    m_fileManagerSettings->setIconSize(FileManagerSettings::IconView, size);

    onGridSizeChanged(ui->gridSizeSlider->value());
}

static int calcGridSize(int iconSize, int factor, bool iconMode)
{
    static const int minIconSize = 32;
    static const int minListSize = 2;

    return (iconSize + (iconMode ? minIconSize : minListSize))*(1.0 + factor/100.0) + 0.5;
}

static int calcGridFactor(int iconSize, int gridSize, bool iconMode)
{
    static const int minIconSize = 32;
    static const int minListSize = 2;

    return (100.0*gridSize)/(iconSize + (iconMode ? minIconSize : minListSize)) - 100 + 0.5;
}

void FileManagerSettingsWidget::onGridSizeChanged(int value)
{
    bool iconMode = ui->flowComboBox->currentIndex() == 0;
    int iconSize = ui->iconSizeSlider->value()*4;
    int gridSize = calcGridSize(iconSize, value, iconMode);

    QSize size(gridSize, gridSize);

    m_settings->setValue(QLatin1String("gridSize"), size);
    m_fileManagerSettings->setGridSize(size);
}

void FileManagerSettingsWidget::onFlowChanged(int value)
{
    m_settings->setValue(QLatin1String("flow"), value);
    m_fileManagerSettings->setFlow((FileManagerSettings::Flow)value);

    onGridSizeChanged(ui->gridSizeSlider->value());
}

void FileManagerSettingsWidget::setupLeftPanel()
{
    int flags = readFlags();

    ui->applicationsCheckBox->setChecked(flags & NavigationModel::ApplicationsLocation);
    ui->desktopCheckBox->setChecked(flags & NavigationModel::DesktopLocation);
    ui->documentsCheckBox->setChecked(flags & NavigationModel::DocumentsLocation);
    ui->downloadsCheckBox->setChecked(flags & NavigationModel::DownloadsLocation);
    ui->moviesCheckBox->setChecked(flags & NavigationModel::MoviesLocation);
    ui->musicCheckBox->setChecked(flags & NavigationModel::MusicLocation);
    ui->picturesCheckBox->setChecked(flags & NavigationModel::PicturesLocation);
    ui->homeCheckBox->setChecked(flags & NavigationModel::HomeLocation);

    ui->applicationsCheckBox->setProperty("flag", NavigationModel::ApplicationsLocation);
    ui->desktopCheckBox->setProperty("flag", NavigationModel::DesktopLocation);
    ui->documentsCheckBox->setProperty("flag", NavigationModel::DocumentsLocation);
    ui->downloadsCheckBox->setProperty("flag", NavigationModel::DownloadsLocation);
    ui->moviesCheckBox->setProperty("flag", NavigationModel::MoviesLocation);
    ui->musicCheckBox->setProperty("flag", NavigationModel::MusicLocation);
    ui->picturesCheckBox->setProperty("flag", NavigationModel::PicturesLocation);
    ui->homeCheckBox->setProperty("flag", NavigationModel::HomeLocation);

    connect(ui->applicationsCheckBox, SIGNAL(toggled(bool)), SLOT(onChecked(bool)));
    connect(ui->desktopCheckBox, SIGNAL(toggled(bool)), SLOT(onChecked(bool)));
    connect(ui->documentsCheckBox, SIGNAL(toggled(bool)), SLOT(onChecked(bool)));
    connect(ui->downloadsCheckBox, SIGNAL(toggled(bool)), SLOT(onChecked(bool)));
    connect(ui->moviesCheckBox, SIGNAL(toggled(bool)), SLOT(onChecked(bool)));
    connect(ui->musicCheckBox, SIGNAL(toggled(bool)), SLOT(onChecked(bool)));
    connect(ui->picturesCheckBox, SIGNAL(toggled(bool)), SLOT(onChecked(bool)));
    connect(ui->homeCheckBox, SIGNAL(toggled(bool)), SLOT(onChecked(bool)));
}

void FileManagerSettingsWidget::setupIconSize()
{
    int iconSize = m_fileManagerSettings->iconSize(FileManagerSettings::IconView).height();
    ui->iconSizeSlider->setValue(iconSize/4);
    ui->iconSizeLabel->setText(tr("Icon size: %1x%2").arg(iconSize).arg(iconSize));

    connect(ui->iconSizeSlider, SIGNAL(valueChanged(int)), SLOT(onIconSizeChanged(int)));
}

void FileManagerSettingsWidget::setupGridSize()
{
    int iconSize = m_fileManagerSettings->iconSize(FileManagerSettings::IconView).height();
    int gridSize = m_fileManagerSettings->gridSize().height();
    FileManagerSettings::Flow flow = m_fileManagerSettings->flow();

    int factor = calcGridFactor(iconSize, gridSize, flow == FileManagerSettings::LeftToRight);
    ui->gridSizeSlider->setValue(factor);

    connect(ui->gridSizeSlider, SIGNAL(valueChanged(int)), SLOT(onGridSizeChanged(int)));
}

void FileManagerSettingsWidget::setupFlow()
{
    FileManagerSettings::Flow flow = m_fileManagerSettings->flow();
    ui->flowComboBox->setCurrentIndex(flow);
    connect(ui->flowComboBox, SIGNAL(currentIndexChanged(int)), SLOT(onFlowChanged(int)));
}
