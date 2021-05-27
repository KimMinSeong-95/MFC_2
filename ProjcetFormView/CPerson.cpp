#include "pch.h"
#include "CPerson.h"

CPerson::CPerson()
{
	m_strName = _T("");
	m_nAge = 0;
	m_bGender = TRUE;
}

CPerson::~CPerson()
{

}

void CPerson::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
		ar << m_strName;
		ar << m_nAge;
		ar << m_bGender;
	}
	else
	{	// loading code
		ar >> m_strName;
		ar >> m_nAge;
		ar >> m_bGender;
	}
}
