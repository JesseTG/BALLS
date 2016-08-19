// Emacs mode hint: -*- mode: JavaScript -*-
// See http://stackoverflow.com/q/25105269/1089957 for why this script exists

function Controller() {
    installer.autoRejectMessageBoxes();
    installer.installationFinished.connect(function() {
        gui.clickButton(buttons.NextButton);
    })
}

Controller.prototype.WelcomePageCallback = function() {
    gui.clickButton(buttons.NextButton);
}

Controller.prototype.CredentialsPageCallback = function() {
    gui.clickButton(buttons.NextButton);
}

Controller.prototype.IntroductionPageCallback = function() {
    gui.clickButton(buttons.NextButton);
}

Controller.prototype.TargetDirectoryPageCallback = function()
{
    gui.currentPageWidget().TargetDirectoryLineEdit.setText(installer.value("HomeDir") + "/Qt");
    gui.clickButton(buttons.NextButton);
}

Controller.prototype.ComponentSelectionPageCallback = function() {
    var widget = gui.currentPageWidget();
    widget.deselectAll();
    widget.selectComponent("qt.56.win64_msvc2015_64.qtbase");
    widget.selectComponent("qt.56.win64_msvc2015_64.qtwinextras");
    widget.selectComponent("qt.56.win64_msvc2015_64.qtimageformats");
    widget.selectComponent("qt.56.win64_msvc2015_64.qttools");
    widget.selectComponent("qt.56.win64_msvc2015_64.icu_541_release.win_64");
    widget.selectComponent("qt.56.win64_msvc2015_64.d3d_compiler_47.x64");
    widget.selectComponent("qt.56.win64_msvc2015.opengl32sw.x64");
    widget.selectComponent("qt.56.win64_msvc2015_64.qttranslations");
    widget.selectComponent("qt.56.qtquickcontrols.win64_msvc2015_64");
    widget.selectComponent("qt.56.qtquickcontrols2.win64_msvc2015_64");
    widget.selectComponent("qt.56.win64_mingw492.essentials");
    widget.selectComponent("qt.56.win64_mingw492.addons");
    widget.selectComponent("qt.56.win64_mingw492.icu_541.mingw_64");
    widget.selectComponent("qt.56.win64_mingw492.runtime");

    widget.selectComponent("qt.57.win64_msvc2015_64.qtbase");
    widget.selectComponent("qt.57.win64_msvc2015_64.qtwinextras");
    widget.selectComponent("qt.57.win64_msvc2015_64.qtimageformats");
    widget.selectComponent("qt.57.win64_msvc2015_64.qttools");
    widget.selectComponent("qt.57.win64_msvc2015_64.qtquickcontrols");
    widget.selectComponent("qt.57.win64_msvc2015_64.qtquickcontrols2");
    widget.selectComponent("qt.57.win64_msvc2015_64.d3d_compiler_47.x64");
    widget.selectComponent("qt.57.win64_msvc2015.opengl32sw.x64");
    
    gui.clickButton(buttons.NextButton);
}

Controller.prototype.LicenseAgreementPageCallback = function() {
    gui.currentPageWidget().AcceptLicenseRadioButton.setChecked(true);
    gui.clickButton(buttons.NextButton);
}

Controller.prototype.StartMenuDirectoryPageCallback = function() {
    gui.clickButton(buttons.NextButton);
}

Controller.prototype.ReadyForInstallationPageCallback = function()
{
    gui.clickButton(buttons.NextButton);
}

Controller.prototype.FinishedPageCallback = function() {
var checkBoxForm = gui.currentPageWidget().LaunchQtCreatorCheckBoxForm
if (checkBoxForm && checkBoxForm.launchQtCreatorCheckBox) {
    checkBoxForm.launchQtCreatorCheckBox.checked = false;
}
    gui.clickButton(buttons.FinishButton);
}
