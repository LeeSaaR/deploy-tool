function Controller()
{
    // console.log("Controller start");
    installer.installationFinished.connect(this, Controller.prototype.onInstallationFinished);
    gui.clickButton(buttons.NextButton);
    // TODO: connect finish button
}

Controller.prototype.onInstallationFinished = function()
{
    // console.log("onInstallationFinished");
    gui.clickButton(buttons.NextButton);
    var widget = gui.currentPageWidget();
    if (widget != null) {
        widget.title = "Installation abgeschlossen.";
    }
}

Controller.prototype.IntroductionPageCallback = function()
{
    // console.log("IntroductionPageCallback");
    installer.setDefaultPageVisible(QInstaller.Introduction, false);
}

Controller.prototype.TargetDirectoryPageCallback = function()
{
    // console.log("TargetDirectoryPageCallback");
    var widget = gui.currentPageWidget();
    if (widget != null) {
        widget.title = "#NAMEANDVERSION# - Installation"; 
        widget.MessageLabel.setText("Installationsordner auswählen.");
    }
}

Controller.prototype.StartMenuDirectoryPageCallback = function()
{
    // console.log("StartMenuDirectoryPageCallback");
    installer.setDefaultPageVisible(QInstaller.StartMenuSelection, false);
    gui.clickButton(buttons.NextButton);
}

Controller.prototype.ComponentSelectionPageCallback = function()
{
    // console.log("ComponentSelectionPageCallback");
    var widget = gui.currentPageWidget();
    widget.selectAll();
    installer.setDefaultPageVisible(QInstaller.ComponentSelection,0);
}

Controller.prototype.LicenseAgreementPageCallback = function()
{
    // console.log("LicenseAgreementPageCallback");
    var widget = gui.currentPageWidget();
    if (widget != null) {
        widget.title = "Lizenz";
        widget.AcceptLicenseLabel.setText("akzeptieren");
    }
}

Controller.prototype.ReadyForInstallationPageCallback = function()
{
    // console.log("ReadyForInstallationPageCallback");
    var widget = gui.currentPageWidget();
    if (widget != null) {
        widget.title = "Installation Bereit";
        widget.MessageLabel.setText("#NAMEANDVERSION# wird #SIZE# Festplatten-Speicher belegen.");
    }
}

Controller.prototype.PerformInstallationPageCallback = function()
{
    // console.log("PerformInstallationPageCallback");
    var widget = gui.currentPageWidget();
    if (widget != null) {
        widget.title = "Installiere...";
        widget.DetailsButton.hide();
    }
}

Controller.prototype.FinishedPageCallback = function()
{
    // console.log("FinishedPageCallback");
    var widget = gui.currentPageWidget();
    if (widget != null) {
        widget.title = "Installation abgeschlossen.";
        widget.MessageLabel.setText("#PRODUCTNAME# ist installiert und bereit zu starten.");
    }
}