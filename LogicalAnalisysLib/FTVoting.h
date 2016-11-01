#pragma once
#include "Interfaces.h"

typedef std::vector<Features> FeatureTests;

// �������� ����������� �� ������
class FTVoting
    :public IBinaryClassifier, public IECVoting
{
public:

    // ����������� �����
    FeatureTests tests;

    // ���������� ������
    ObjectPtrList precedents;
    
    FTVoting(FeatureTests tests, ObjectPtrList precedents);

    virtual Estimate Apply(Object const& object) const;

    virtual void GetECSet( ECSet& ecset );

private:

    Estimate Apply(Object const& object, Object const& precedent,
        Features const& featureTest) const;

    
};

