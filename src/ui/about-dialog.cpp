#include <QtWidgets>

#include "seadrive-gui.h"
#include "utils/utils.h"

#include "about-dialog.h"

#ifdef HAVE_SPARKLE_SUPPORT
#include "auto-update-service.h"
#endif

namespace {

} // namespace

AboutDialog::AboutDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);
    setWindowTitle(tr("About %1").arg(getBrand()));
    setWindowIcon(QIcon(":/images/seafile.png"));
    setWindowFlags((windowFlags() & ~Qt::WindowContextHelpButtonHint) |
                   Qt::WindowStaysOnTopHint);

    version_text_ = tr("<h4>AlphaDrive %2</h4>")
	               .arg(STRINGIZE(SEADRIVE_GUI_VERSION));

    mVersionText->setText(version_text_);

    connect(mOKBtn, SIGNAL(clicked()), this, SLOT(close()));

    mCheckUpdateBtn->setVisible(false);
#ifdef HAVE_SPARKLE_SUPPORT
    if (AutoUpdateService::instance()->shouldSupportAutoUpdate()) {
        mCheckUpdateBtn->setVisible(true);
        connect(mCheckUpdateBtn, SIGNAL(clicked()), this, SLOT(checkUpdate()));
    }
#endif
}

#ifdef HAVE_SPARKLE_SUPPORT
void AboutDialog::checkUpdate()
{
    AutoUpdateService::instance()->checkUpdate();
    close();
}
#endif
