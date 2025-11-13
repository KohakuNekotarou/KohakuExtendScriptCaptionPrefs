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

// Interface includes
#include "ILinkCaptionPrefs.h"
#include "IScript.h"
#include "IScriptRequestData.h"

// General includes
#include "CScriptProvider.h" // for RepresentScriptProvider
#include "PreferenceUtils.h" // for QueryPreferences
#include "ScriptData.h" // also has typedef for ScriptListData

// Project includes
#include "KESCPScriptingDefs.h"
#include "KESCPID.h"

class KESCPCaptionLinesScriptProvider : public RepresentScriptProvider
{
public:
	KESCPCaptionLinesScriptProvider(IPMUnknown* boss);

	virtual ~KESCPCaptionLinesScriptProvider(void);

protected:
	// Returns the number of objects (managed by this provider) of a specific type. 
	// @see RepresentScriptProvider::GetNumObjects
	virtual int32 GetNumObjects( const IScriptRequestData* data, IScript* parent );

	// Returns the Nth object (managed by this provider) of a specific type. 
	// @see RepresentScriptProvider::AppendNthObject
	virtual ErrorCode AppendNthObject( const IScriptRequestData* data, IScript* parent, int32 n, ScriptList& objectList );



	/** The ScriptID of the object represented by this 
	 * 	RepresentScriptProvider implementation.
	 */
	ScriptID fScriptClassID;

	/** The ClassID of the boss class that has the IScript implementation 
	 * 	for the script object identified by fScriptClassID.
	 */
	ClassID  fProviderClassID;
};

// Make the implementation available to the application.
CREATE_PMINTERFACE(KESCPCaptionLinesScriptProvider, kKESCPCaptionLinesScriptProviderImpl)

// Constructor
KESCPCaptionLinesScriptProvider::KESCPCaptionLinesScriptProvider(IPMUnknown* boss) :
	RepresentScriptProvider(boss), 
	fScriptClassID(c_KESCPCaptionLine),
	fProviderClassID(kKESCPCaptionLinesScriptObjectBoss)
{
}

// Destructor
KESCPCaptionLinesScriptProvider::~KESCPCaptionLinesScriptProvider(void)	{}

// GetNumObjects
int32 KESCPCaptionLinesScriptProvider::GetNumObjects( const IScriptRequestData* data, IScript* parent )
{
	int32 numObjects = 0;
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
		numObjects = iLinkCaptionPrefs->GetNumCaptionLines();

	} while (false);
	return numObjects;
}

// AppendNthObject
ErrorCode KESCPCaptionLinesScriptProvider::AppendNthObject( const IScriptRequestData* data, IScript* parent, int32 n, ScriptList& objectList )
{
	ErrorCode result = kFailure;
	do
	{

	} while (false);
	return result;
}