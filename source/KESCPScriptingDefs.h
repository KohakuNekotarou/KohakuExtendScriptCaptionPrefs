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


#ifndef __KESCPScriptingDefs_h__
#define __KESCPScriptingDefs_h__

#define kCPrefs_CLSID { 0x8d448fe0, 0x8194, 0x11d3, { 0xa6, 0x53, 0x0, 0xe0, 0x98, 0x71, 0xa, 0x6f } }
DECLARE_GUID(CPrefs_CLSID, kCPrefs_CLSID);

// Note: 4-char IDs below must be unique.
// See ScriptingDefs.h for further information.

enum KESCPScriptClasses
{
	c_KESCPCaptionPreferences = 'KCPe',
	c_KESCPCaptionLine = 'KCLi',
	c_KESCPCaptionLines = 'KCLs',
};

// Method IDs
enum KESCPScriptEvents
{
	e_KESCPGetInfoProviderDescriptionString = 'KGPS',
	e_KESCPGetNumInfoProviders = 'KGNP',
};

// Property IDs
enum KESCPScriptProperties
{
	p_KESCPCaptionPreferences = 'KCPs',
	p_KESCPFrameOffset = 'KFOf',
	p_KESCPCaptionParagraphStyleID = 'KPSU',
	p_KESCPCaptionLayerName = 'KCLN',
	p_KESCPGroupCaptionWithImage = 'KGCI',
	p_KESCPCaptionAlignment = 'KCAl',
	p_KESCPInfoProviderIndex = 'KIPI',
};

#endif // __KESCPScriptingDefs_h__