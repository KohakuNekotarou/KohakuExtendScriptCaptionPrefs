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
#include "IApplication.h"
#include "IDataBase.h"
#include "IPMUnknown.h"
#include "IStringData.h"

// General includes:
#include "CProxyScript.h"

// Project includes:
#include "KESCPScriptingDefs.h"
#include "KESCPID.h"

class KESCPCaptionLinesScript : public CProxyScript
{
public:
	KESCPCaptionLinesScript(IPMUnknown* boss);

	virtual ~KESCPCaptionLinesScript(void);

	// Returns the database related to this object.
	// Since the SnippetRunner isn't persistent, we just return the application database.
	virtual IDataBase* GetDataBase(const RequestContext& requestContext) const;

private:
	IDataBase* fDB;
};

// Make the implementation available to the application.
CREATE_PMINTERFACE(KESCPCaptionLinesScript, kKESCPCaptionLinesScriptImpl)

// Constructor
KESCPCaptionLinesScript::KESCPCaptionLinesScript(IPMUnknown* boss) : CProxyScript(boss)	
{
	// NOTE: this ScriptID must match that used in the call to IScriptUtils::CreateProxyScriptObject
	fObjectType = c_KESCPCaptionLine;
	fDB = nil;
}

// Destructor
KESCPCaptionLinesScript::~KESCPCaptionLinesScript(void){}

// GetDataBase
// A safe way to determine the appropriate database for this object. Most implementations
// can simply inherit and use the default implementation { return ::GetDataBase( this ) ; }
// but some script bosses are non-persistent, and should therefore override this method.
IDataBase* KESCPCaptionLinesScript::GetDataBase(const RequestContext& requestContext) const
{
	if (fDB == nil)
	{
		InterfacePtr<IApplication> iApplication(::GetExecutionContextSession()->QueryApplication());
		if (iApplication != nil)
		{
			const_cast<KESCPCaptionLinesScript*>(this)->fDB = ::GetDataBase(iApplication);
		}
	}
	return fDB;
}