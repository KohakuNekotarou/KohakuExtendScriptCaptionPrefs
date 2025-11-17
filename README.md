# InDesign Plug-In

**I'll add various things to ExtendScript.**
<br>**Let's learn the InDesign SDK together.**

We cannot be held responsible for any issues arising from your use of this service.<br>
Please use it at your own risk.<br>

On Mac, you cannot use downloaded plug-ins directly.<br>
https://helpx.adobe.com/jp/indesign/kb/indesign-and-macos-catalina.html<br>
Refer to the above and use Terminal to<br>
sudo xattr -r -d com.apple.quarantine /Applications/Adobe\ Indesign\ 2025/Plug-ins/KohakuExtendScriptCaptionPrefs.InDesignPlugin<br>
Please execute.

## extendScript for JavaScript
```
// Edit caption preferences

// Caption lines object
CaptionLines = app.kescpCaptionPreferences.kescpCaptionLines;
CaptionLines.count();

// Add
// KescpCaptionLinesObject does not have an ID; it can only be accessed by index.
// Added objects are appended to the end.
infoProviderDescriptionString = app.kescpCaptionPreferences.kescpGetInfoProviderDescriptionString(0);
app.kescpCaptionPreferences.kescpCaptionLines.add("Kohaku", infoProviderDescriptionString, "Nekotarou");

// Remove
app.kescpCaptionPreferences.kescpCaptionLines[0].remove();

// Before string
beforeString = app.kescpCaptionPreferences.kescpCaptionLines[0].kescpBeforeString;
app.kescpCaptionPreferences.kescpCaptionLines[0].kescpBeforeString = "Kohaku";

// Link info provider name
linkInfoProviderName = app.kescpCaptionPreferences.kescpCaptionLines[0].kescpLinkInfoProviderName;
infoProviderDescriptionString = app.kescpCaptionPreferences.kescpGetInfoProviderDescriptionString(0);
app.kescpCaptionPreferences.kescpCaptionLines[0].kescpLinkInfoProviderName = infoProviderDescriptionString;

// After string
AfterString = app.kescpCaptionPreferences.kescpCaptionLines[0].kescpAfterString;
app.kescpCaptionPreferences.kescpCaptionLines[0].kescpAfterString = "Nekotarou";
```
