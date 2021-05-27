#pragma once
#include <afx.h>
class CPerson : public CObject
{
public:
	CPerson();
	~CPerson();

	CString m_strName;
	int m_nAge;
	BOOL m_bGender;
	virtual void Serialize(CArchive& ar);
};

