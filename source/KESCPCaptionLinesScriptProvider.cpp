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
#include "IIntData.h"
#include "ILinkCaptionPrefs.h"
#include "IScript.h"
#include "IScriptRequestData.h"

// General includes
#include "CAlert.h" // CAlert::InformationAlert()
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

	virtual ErrorCode AccessProperty(ScriptID scriptID_property, IScriptRequestData* iScriptRequestData, IScript* iScript);

protected:
	// Returns the number of objects (managed by this provider) of a specific type. 
	// @see RepresentScriptProvider::GetNumObjects
	virtual int32 GetNumObjects( const IScriptRequestData* data, IScript* parent );

	// Returns the Nth object (managed by this provider) of a specific type. 
	// @see RepresentScriptProvider::AppendNthObject
	virtual ErrorCode AppendNthObject
		( const IScriptRequestData* iScriptRequestData, IScript* iScript_parent, int32 int32_n, ScriptList& scriptList_object );



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

// AccessProperty
ErrorCode KESCPCaptionLinesScriptProvider::AccessProperty
	(ScriptID scriptID_property, IScriptRequestData* iScriptRequestData, IScript* iScript)
{
	ErrorCode result = kFailure;
	do
	{
		switch (scriptID_property.Get())
		{
		case e_Create: // add
			//return Utils<IPageItemScriptUtils>()->DoCreatePageItem(data, script, &this->CreateCandleChart);

			break;
		default:
			// NOTE:
			// The following properties are handled in the super class RepresentScriptProvider (See CScriptProvider.cpp):
			// p_Index (kIndexPropertyScriptElement)
			// p_Parent (kParentPropertyScriptElement)
			// p_Properties (kPropertiesPropertyScriptElement)
			result = RepresentScriptProvider::AccessProperty(scriptID_property, iScriptRequestData, iScript);
			break;
		}
	} while (false);

	return result;
}

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
ErrorCode KESCPCaptionLinesScriptProvider::AppendNthObject
(const IScriptRequestData* iScriptRequestData, IScript* iScript_parent, int32 int32_n, ScriptList& scriptList_object)
{
	ErrorCode result = kFailure;

	do
	{
		// check input parameters
		if (iScriptRequestData == nil || iScript_parent == nil) break;

		// that we are getting the object ID we are expecting
		ScriptID ScriptID_objectType = iScriptRequestData->GetDesiredType();
		if (ScriptID_objectType != this->fScriptClassID) break;

		// create a proxy script object
		InterfacePtr<IScript> iScript_proxyScriptObject(Utils<IScriptUtils>()->CreateProxyScriptObject(
			iScriptRequestData->GetRequestContext(),
			this->fProviderClassID,
			this->fScriptClassID,
			iScript_parent
		));
		if (iScript_proxyScriptObject == nil) break;

		// query for data interfaces
		InterfacePtr<IIntData> iIntData(iScript_proxyScriptObject, ::UseDefaultIID());
		if (iIntData == nil) break;

		// set the index
		iIntData->Set(int32_n);

		// add the object to the list
		// ASLSupport.lib is required
		scriptList_object.push_back(iScript_proxyScriptObject);

		result = kSuccess;

	} while (false);

	return result;
}