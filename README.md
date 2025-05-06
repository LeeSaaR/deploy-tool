# DeployTool
DeployTool uses windeployqt6 and binarycreator to generate an installer executable. BinaryCreator provides more functionality than Deploy Tool reveals. So definitely check out BinaryCreator, that is not limited to Qt. DeployTool is my quick solution to create an installer with a single package respectively a single component.

## Depedencies

1. windeployqt6
2. binarycreator

Add windeployqt6 path to your system's PATH variable depending on your installation of Qt and your compiler.  
For me it is:  
`C:\Qt\6.8.3\msvc2022_64\bin`

> MINGW should work too.

Install the QtInstallerFramework via Qt's maintenance tool to get binarycreator.exe and add the path to your system's PATH variable. For me it is:  
`C:\Qt\Tools\QtInstallerFramework\4.9\bin`

## Example
The example folder contains:
<pre>
├── example
│   ├── config.json
│   ├── logo.png
│   ├── replace-with-your-exe-file.txt
│   └── win_icon.png
</pre>

Customize:
1. Customize data in config.json to your needs.
2. Replace the file "replace-with-your-exe-file.txt" with your executable .exe file.
3. Replace logo.png and win_icon.png with your own.  

In DeployTool:
1. click source dir and choose example/.   
2. Then select a output dir for your Installer.
3. Click on run.
4. Wait until DeployTool finished.

Done.

## Customize
Feel free to customize and extend DeployTool. 
Look inside the folder res/  
<pre>
└── res
    ├── preset
        ├── config
        │   ├── config.xml
        │   ├── controlscript.js
        │   ├── logo.png
        │   ├── style.qss
        │   └── win_icon.png
        └── packages
            └── com.vendor.template
                ├── data
                │   └── dummy_app_content.txt
                └── meta
                    ├── installscript.js
                    ├── license.txt
                    └── package.xml
</pre>