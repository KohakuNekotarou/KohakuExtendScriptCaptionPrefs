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
// Edit caption preferences.

// Caption preferences object.
captionPrefs = app.kescpCaptionPreferences;

// Get num info providers.
NumInfoProviders = app.kescpCaptionPreferences.kescpGetNumInfoProviders();

// Get info provider description string.
infoProviderDescriptionString = app.kescpCaptionPreferences.kescpGetInfoProviderDescriptionString(0);

// Caption alignment.
captionAlignment = app.kescpCaptionPreferences.kescpCaptionAlignment;
app.kescpCaptionPreferences.kescpCaptionAlignment = "Below";
app.kescpCaptionPreferences.kescpCaptionAlignment = "Above";
app.kescpCaptionPreferences.kescpCaptionAlignment = "Left";
app.kescpCaptionPreferences.kescpCaptionAlignment = "Right";

// Frame offset.
app.kescpCaptionPreferences.kescpFrameOffset = 5;

// Caption paragraph style ID.
captionParagraphStyleID = app.kescpCaptionPreferences.kescpCaptionParagraphStyleID;
app.kescpCaptionPreferences.kescpCaptionParagraphStyleID = app.activeDocument.paragraphStyles[0].id;

// Caption layer name.
captionLayerName = app.kescpCaptionPreferences.kescpCaptionLayerName;
app.kescpCaptionPreferences.kescpCaptionLayerName = captionLayerName;

// Group caption with image.
groupCaptionWithImage = app.kescpCaptionPreferences.kescpGroupCaptionWithImage;
app.kescpCaptionPreferences.kescpGroupCaptionWithImage = true;

// Caption lines object.
CaptionLines = app.kescpCaptionPreferences.kescpCaptionLines;
CaptionLines.count();

// Add.
// KescpCaptionLinesObject does not have an ID; it can only be accessed by index.
// Added objects are appended to the end.
infoProviderDescriptionString = app.kescpCaptionPreferences.kescpGetInfoProviderDescriptionString(0);
app.kescpCaptionPreferences.kescpCaptionLines.add("Kohaku", infoProviderDescriptionString, "Nekotarou");

// Remove.
app.kescpCaptionPreferences.kescpCaptionLines[0].remove();

// Before string.
beforeString = app.kescpCaptionPreferences.kescpCaptionLines[0].kescpBeforeString;
app.kescpCaptionPreferences.kescpCaptionLines[0].kescpBeforeString = "Kohaku";

// Link info provider name.
linkInfoProviderName = app.kescpCaptionPreferences.kescpCaptionLines[0].kescpLinkInfoProviderName;
infoProviderDescriptionString = app.kescpCaptionPreferences.kescpGetInfoProviderDescriptionString(0);
app.kescpCaptionPreferences.kescpCaptionLines[0].kescpLinkInfoProviderName = infoProviderDescriptionString;

// After string.
AfterString = app.kescpCaptionPreferences.kescpCaptionLines[0].kescpAfterString;
app.kescpCaptionPreferences.kescpCaptionLines[0].kescpAfterString = "Nekotarou";
```
