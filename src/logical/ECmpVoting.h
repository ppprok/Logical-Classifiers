#pragma once

#include "Interfaces.h"
#include "ECmp.h"

struct ECmpSetInfo;

typedef std::vector<ECmpSetInfo> ECmpSetInfos;

// ����������� �� ������� ��.��. � �����������
class ECmpVoting : public IBinaryClassifier, public IECVoting
{
public:

    ECmpSetInfos ecmpSets;
    
    ObjectPtrList precedents;

    ECmpVoting(ECmpSetInfos ecset, ObjectPtrList precedents);

    // �������� ����������� �� ������� ��.��.
    virtual Estimate Apply( Object const& o ) const;

    virtual void GetECSet( ECSet& ecset );
};

typedef std::vector<ECmpSet> ECmpSets;

// ����������� �� ������� ��.��. � �����������
class ECmpVoting0 : public IBinaryClassifier, public IECVoting
{
public:

    ECmpSets ecmpSets;

    ObjectPtrList precedents;

    ECmpVoting0(ECmpSets ecsets, ObjectPtrList precedents);

    // �������� ����������� �� ������� ��.��.
    virtual Estimate Apply( Object const& o ) const;

    Estimate Apply(ECmpSet const& ecmpSet, Object const& p, Object const& o) const;

    virtual void GetECSet( ECSet& ecset );
};


// ���������� � ������ ��.��. � �����������, � �������� �� ���� ������������ ���������
struct ECmpSetInfo
{
    // ����� ��.��. � �����������
    ECmpSet ecmpSet;

    // ����� ��������, � �������� �� ���� ����������� ���������
    ObjectPtrList excludedPrecedents;

    ECmpSetInfo(){};

    ECmpSetInfo(ECmpSet e, ObjectPtrList p)
    {
        ecmpSet = std::move(e);
        excludedPrecedents = std::move(p);
    };

    UTILITY_MOVE_DEFAULT_MEMBERS(ECmpSetInfo, (ecmpSet)(excludedPrecedents));

    // �������� ������ � �����������
    Estimate Apply(Object const& precedent, Object const& o) const;

    // �������� ������ � ������������
    Estimate Apply(ObjectPtrList const& precedents, Object const& o) const;
};





