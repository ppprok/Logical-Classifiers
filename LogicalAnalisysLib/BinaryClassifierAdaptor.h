#pragma once
#include "Interfaces.h"


// �������� ������������ ����� ������� �������������
class BinaryClassifierAdaptor
    :public IBinaryClassifier, public IECVoting
{
    IClassifierPtr _classifier;

public:
    
    BinaryClassifierAdaptor(IClassifierPtr classifier);
    
    virtual Estimate Apply( Object const& o ) const;

    virtual void GetECSet( ECSet& ecset );
};