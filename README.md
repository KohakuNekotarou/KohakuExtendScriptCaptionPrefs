# InDesign Plug-In

**I'll add various things to ExtendScript.**
<br>**Let's learn the InDesign SDK together.**

We cannot be held responsible for any issues arising from your use of this service.<br>
Please use it at your own risk.<br>

On Mac, you cannot use downloaded plug-ins directly.<br>
https://helpx.adobe.com/jp/indesign/kb/indesign-and-macos-catalina.html<br>
Refer to the above and use Terminal to<br>
sudo xattr -r -d com.apple.quarantine /Applications/Adobe\ Indesign\ 2025/Plug-ins/KohakuExtendScriptStyleShortcut.InDesignPlugin<br>
Please execute.

## extendScript for JavaScript
```
// Style Shortcut Settings
app.activeDocument.objectStyles.lastItem().shortcut = ""; // delete
app.activeDocument.objectStyles.lastItem().shortcut = "Shift+0";
app.activeDocument.cellStyles.lastItem().shortcut = "Shift+1";
app.activeDocument.tableStyles.lastItem().shortcut = "Shift+2";
app.activeDocument.paragraphStyles.lastItem().shortcut = "Shift+3";
app.activeDocument.characterStyles.lastItem().shortcut = "Shift+4";
alert(app.activeDocument.characterStyles.lastItem().shortcut);
```
