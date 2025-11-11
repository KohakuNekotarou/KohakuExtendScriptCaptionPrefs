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
DECLARE_PMID(kClassIDSpace, kKESCPPrefsScriptProviderBoss, kKESCPPrefix + 0)

// InterfaceIDs:
//DECLARE_PMID(kInterfaceIDSpace, IID_IKESCPINTERFACE, kKESCPPrefix + 0)

// ImplementationIDs:
DECLARE_PMID(kImplementationIDSpace, kKESCPPrefsScriptProviderImpl, kKESCPPrefix + 0 )
//DECLARE_PMID(kImplementationIDSpace, kKESCPImpl, kKESCPPrefix + 1)
//DECLARE_PMID(kImplementationIDSpace, kKESCPImpl, kKESCPPrefix + 2)
//DECLARE_PMID(kImplementationIDSpace, kKESCPImpl, kKESCPPrefix + 3)
//DECLARE_PMID(kImplementationIDSpace, kKESCPImpl, kKESCPPrefix + 4)
//DECLARE_PMID(kImplementationIDSpace, kKESCPImpl, kKESCPPrefix + 5)
//DECLARE_PMID(kImplementationIDSpace, kKESCPImpl, kKESCPPrefix + 6)
//DECLARE_PMID(kImplementationIDSpace, kKESCPImpl, kKESCPPrefix + 7)
//DECLARE_PMID(kImplementationIDSpace, kKESCPImpl, kKESCPPrefix + 8)
//DECLARE_PMID(kImplementationIDSpace, kKESCPImpl, kKESCPPrefix + 9)
//DECLARE_PMID(kImplementationIDSpace, kKESCPImpl, kKESCPPrefix + 10)
//DECLARE_PMID(kImplementationIDSpace, kKESCPImpl, kKESCPPrefix + 11)
//DECLARE_PMID(kImplementationIDSpace, kKESCPImpl, kKESCPPrefix + 12)
//DECLARE_PMID(kImplementationIDSpace, kKESCPImpl, kKESCPPrefix + 13)
//DECLARE_PMID(kImplementationIDSpace, kKESCPImpl, kKESCPPrefix + 14)
//DECLARE_PMID(kImplementationIDSpace, kKESCPImpl, kKESCPPrefix + 15)
//DECLARE_PMID(kImplementationIDSpace, kKESCPImpl, kKESCPPrefix + 16)
//DECLARE_PMID(kImplementationIDSpace, kKESCPImpl, kKESCPPrefix + 17)
//DECLARE_PMID(kImplementationIDSpace, kKESCPImpl, kKESCPPrefix + 18)
//DECLARE_PMID(kImplementationIDSpace, kKESCPImpl, kKESCPPrefix + 19)
//DECLARE_PMID(kImplementationIDSpace, kKESCPImpl, kKESCPPrefix + 20)
//DECLARE_PMID(kImplementationIDSpace, kKESCPImpl, kKESCPPrefix + 21)
//DECLARE_PMID(kImplementationIDSpace, kKESCPImpl, kKESCPPrefix + 22)
//DECLARE_PMID(kImplementationIDSpace, kKESCPImpl, kKESCPPrefix + 23)
//DECLARE_PMID(kImplementationIDSpace, kKESCPImpl, kKESCPPrefix + 24)
//DECLARE_PMID(kImplementationIDSpace, kKESCPImpl, kKESCPPrefix + 25)

// ActionIDs:
DECLARE_PMID(kActionIDSpace, kKESCPAboutActionID, kKESCPPrefix + 0)

// WidgetIDs:
//DECLARE_PMID(kWidgetIDSpace, kKESCPWidgetID, kKESCPPrefix + 2)

//Script Element IDs
//DECLARE_PMID(kScriptInfoIDSpace, kKESCPMethodScriptElement, kKESCPPrefix + 0)
DECLARE_PMID(kScriptInfoIDSpace, kKESCPCaptionPreferenceObjectScriptElement, kKESCPPrefix + 0)
DECLARE_PMID(kScriptInfoIDSpace, kKESCPCaptionPreferenceObjectPropertyScriptElement, kKESCPPrefix + 1)
DECLARE_PMID(kScriptInfoIDSpace, kKESCPFrameOffsetPropertyScriptElement, kKESCPPrefix + 2)

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
