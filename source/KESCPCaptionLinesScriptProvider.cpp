//========================================================================================
//  
//  $File$
//  
//  Owner: Adobe Developer Technologies
//  
//  $Author$
//  
//  $DateTime$
//  
//  $Revision$
//  
//  $Change$
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// Interface includes:
#include "IActiveContext.h"
#include "ILinkCaptionPrefs.h"
#include "IScript.h"
#include "IScriptRequestData.h"

// General includes:
#include "CAlert.h"
#include "PreferenceUtils.h" // for QueryPreferences
#include "CScriptProvider.h"
#include "Utils.h"

// Project includes:
#include "KESCPScriptingDefs.h"
#include "KESCPID.h"

class KESCPCaptionLinesScriptProvider : public RepresentScriptProvider
{
public:
	KESCPCaptionLinesScriptProvider(IPMUnknown *boss);

	virtual ~KESCPCaptionLinesScriptProvider();

	//virtual ErrorCode HandleMethod(ScriptID methodID, IScriptRequestData* data, IScript* script);

	//virtual ErrorCode AccessProperty(ScriptID propID, IScriptRequestData* data, IScript* script);

protected:
	// Get the number of child objects in a collection on the given parent.
	virtual int32 GetNumObjects(const IScriptRequestData* data, IScript* parent);

	// Append the nth child object from a collection on the given parent.
	virtual ErrorCode AppendNthObject
	(const IScriptRequestData* iScriptRequestData, IScript* iScript_parent, int32 int32_n, ScriptList& scriptList_objectList);
};

// Makes the implementation available to the application.
CREATE_PMINTERFACE(KESCPCaptionLinesScriptProvider, kKESCPCaptionLinesScriptProviderImpl)

KESCPCaptionLinesScriptProvider::KESCPCaptionLinesScriptProvider(IPMUnknown *boss) : RepresentScriptProvider(boss){}
KESCPCaptionLinesScriptProvider::~KESCPCaptionLinesScriptProvider(){}

int32 KESCPCaptionLinesScriptProvider::GetNumObjects(const IScriptRequestData* data, IScript* parent )
{
	int32 int32_NumObjects = 0;

	do
	{
		// ---------------------------------------------------------------------------------------
		// Query ILinkCaptionPrefs
		IActiveContext* iActiveContext = GetExecutionContextSession()->GetActiveContext();
		if (iActiveContext == nil) break;

		InterfacePtr<ILinkCaptionPrefs> iLinkCaptionPrefs(
			(ILinkCaptionPrefs*)::QueryPreferences(IID_ILINKCAPTIONPREFS, iActiveContext)
		);
		if (iLinkCaptionPrefs == nil) break;

		// ---------------------------------------------------------------------------------------
		// Get num caption lines
		int32_NumObjects = iLinkCaptionPrefs->GetNumCaptionLines();

	} while (false); // only do once

	return int32_NumObjects;
}

ErrorCode KESCPCaptionLinesScriptProvider::AppendNthObject
(const IScriptRequestData* iScriptRequestData, IScript* iScript_parent, int32 int32_n, ScriptList& scriptList_objectList)	//0-based index
{
	ErrorCode status = kFailure;

	do
	{
		// ---------------------------------------------------------------------------------------
		// Query ILinkCaptionPrefs
		IActiveContext* iActiveContext = GetExecutionContextSession()->GetActiveContext();
		if (iActiveContext == nil) break;

		InterfacePtr<ILinkCaptionPrefs> iLinkCaptionPrefs(
			(ILinkCaptionPrefs*)::QueryPreferences(IID_ILINKCAPTIONPREFS, iActiveContext)
		);
		if (iLinkCaptionPrefs == nil) break;

		// ---------------------------------------------------------------------------------------
		// Get num caption lines

	} while (false); // only do once

	return status;
}