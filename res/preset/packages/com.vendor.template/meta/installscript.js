function Component()
{
}

Component.prototype.isDefault = function()
{
    return true;
}

Component.prototype.createOperations = function()
{
    component.createOperations(); // call base

    if (systemInfo.productType === "windows") {
        console.log( "createOperations ");
        component.addOperation("CreateShortcut", "@TargetDir@/#FILEEXE#", "@StartMenuDir@/#PRODUCTNAME#.lnk");
    }
}
