//========================================================================================
//  
//  $File: $
//  
//  Owner: 
//  
//  $Author: $
//  
//  $DateTime: $
//  
//  $Revision: $
//  
//  $Change: $
//  
//  Copyright 1997-2012 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================


#ifndef __KESCPID_h__
#define __KESCPID_h__

#include "SDKDef.h"

// Company:
#define kKESCPCompanyKey	kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kKESCPCompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kKESCPPluginName	"KohakuExtendScriptCaptionPrefs"			// Name of this plug-in.
#define kKESCPPrefixNumber	0xe204468 		// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kKESCPVersion		kSDKDefPluginVersionString						// Version of this plug-in (for the About Box).
#define kKESCPAuthor		""					// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kKESCPPrefixNumber above to modify the prefix.)
#define kKESCPPrefix		RezLong(kKESCPPrefixNumber)				// The unique numeric prefix for all object model IDs for this plug-in.
#define kKESCPStringPrefix	SDK_DEF_STRINGIZE(kKESCPPrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

// Missing plug-in: (see ExtraPluginInfo resource)
#define kKESCPMissingPluginURLValue		kSDKDefPartnersStandardValue_enUS // URL displayed in Missing Plug-in dialog
#define kKESCPMissingPluginAlertValue	kSDKDefMissingPluginAlertValue // Message displayed in Missing Plug-in dialog - provide a string that instructs user how to solve their missing plug-in problem

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kKESCPPluginID, kKESCPPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kKESCPCaptionPreferencesScriptProviderBoss, kKESCPPrefix + 0)
DECLARE_PMID(kClassIDSpace, kKESCPCaptionLinesScriptProviderBoss, kKESCPPrefix + 1)
DECLARE_PMID(kClassIDSpace, kKESCPCaptionLinesScriptObjectBoss, kKESCPPrefix + 2)

// InterfaceIDs:
//DECLARE_PMID(kInterfaceIDSpace, IID_IKESCPINTERFACE, kKESCPPrefix + 0)

// ImplementationIDs:
DECLARE_PMID(kImplementationIDSpace, kKESCPCaptionPreferencesScriptProviderImpl, kKESCPPrefix + 0)
DECLARE_PMID(kImplementationIDSpace, kKESCPCaptionLinesScriptImpl, kKESCPPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kKESCPCaptionLinesScriptProviderImpl, kKESCPPrefix + 2)

// ActionIDs:
DECLARE_PMID(kActionIDSpace, kKESCPAboutActionID, kKESCPPrefix + 0)

// WidgetIDs:
//DECLARE_PMID(kWidgetIDSpace, kKESCPWidgetID, kKESCPPrefix + 2)

//Script Element IDs
DECLARE_PMID(kScriptInfoIDSpace, kKESCPCaptionPreferencesObjectScriptElement, kKESCPPrefix + 0)
DECLARE_PMID(kScriptInfoIDSpace, kKESCPCaptionPreferencesObjectPropertyScriptElement, kKESCPPrefix + 1)
DECLARE_PMID(kScriptInfoIDSpace, kKESCPFrameOffsetPropertyScriptElement, kKESCPPrefix + 2)
DECLARE_PMID(kScriptInfoIDSpace, kKESCPCaptionParagraphStyleUIDPropertyScriptElement, kKESCPPrefix + 3)
DECLARE_PMID(kScriptInfoIDSpace, kKESCPCaptionLayerNamePropertyScriptElement, kKESCPPrefix + 4)
DECLARE_PMID(kScriptInfoIDSpace, kKESCPGroupCaptionWithImagePropertyScriptElement, kKESCPPrefix + 5)
DECLARE_PMID(kScriptInfoIDSpace, kKESCPCaptionAlignmentPropertyScriptElement, kKESCPPrefix + 6)
DECLARE_PMID(kScriptInfoIDSpace, kKESCPCaptionLinesObjectScriptElement, kKESCPPrefix + 7)
DECLARE_PMID(kScriptInfoIDSpace, kKESCPGetInfoProviderDescriptionStringMethodScriptElement, kKESCPPrefix + 8)
DECLARE_PMID(kScriptInfoIDSpace, kKESCPGetNumInfoProvidersMethodScriptElement, kKESCPPrefix + 9)

// GUIDs
#define kKESCPCaptionLine_CLSID { 0xfe7b2072, 0x0183, 0x4be8, { 0x85, 0x09, 0x9d, 0xd7, 0x05, 0x51, 0x52, 0x77 } }
#define kKESCPCaptionLines_CLSID { 0x496a7def, 0x5f0a, 0x44f1, { 0xb7, 0xd6, 0xc9, 0x66, 0xb8, 0x91, 0x9a, 0x07 } }

// "About Plug-ins" sub-menu:
#define kKESCPAboutMenuKey			kKESCPStringPrefix "kKESCPAboutMenuKey"
#define kKESCPAboutMenuPath		kSDKDefStandardAboutMenuPath kKESCPCompanyKey

// "Plug-ins" sub-menu:
#define kKESCPPluginsMenuKey 		kKESCPStringPrefix "kKESCPPluginsMenuKey"
#define kKESCPPluginsMenuPath		kSDKDefPlugInsStandardMenuPath kKESCPCompanyKey kSDKDefDelimitMenuPath kKESCPPluginsMenuKey

// Menu item keys:

// Other StringKeys:
#define kKESCPAboutBoxStringKey	kKESCPStringPrefix "kKESCPAboutBoxStringKey"
#define kKESCPTargetMenuPath kKESCPPluginsMenuPath

// Menu item positions:


// Initial data format version numbers
#define kKESCPFirstMajorFormatNumber  RezLong(1)
#define kKESCPFirstMinorFormatNumber  RezLong(0)

// Data format version numbers for the PluginVersion resource 
#define kKESCPCurrentMajorFormatNumber kKESCPFirstMajorFormatNumber
#define kKESCPCurrentMinorFormatNumber kKESCPFirstMinorFormatNumber

#endif // __KESCPID_h__
