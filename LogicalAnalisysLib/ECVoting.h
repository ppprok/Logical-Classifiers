#pragma once

#include "Interfaces.h"
#include "Object.h"


// ����������� �� ��.��.
class ECVoting
    :public IBinaryClassifier, public IECVoting
{
    // ��.��. � ������
    ECSet _ecset;

public:

    ECVoting(ECSet ecset)
        :_ecset(std::move(ecset))
    {
    }
    
    // ��������� ��������� ��� ��.��., �������� ����� �� ��������� ������� �
    // �������������� ������
    virtual Estimate Apply( Object const& o ) const;

    ECSet const& GetECSet() const
    {
        return _ecset;
    }

    virtual void GetECSet( ECSet& ecset );
};