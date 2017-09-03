#pragma once
#include "Object.h"
#include "ECmp.h"

struct IComparer
{
    virtual int GetSize() const  = 0;

    virtual void Compare(Object const& o1, Object const& o2, 
        bit_chunk& output) const = 0;

    virtual ~IComparer(){};
};


// ��������� ���������
struct FeatureComparer
    :IComparer
{
    Features features;

    int GetSize() const;

    void Compare(Object const& o1, Object const& o2, 
        bit_chunk& output) const;

    void Get(bit_chunk cover, Features& selected);
};

// ��������� ���������
struct ECmpSetComparer
    :IComparer
{
    ECmpSet ecmpSet;

    int GetSize() const;

    void Compare(Object const& o1, Object const& o2, 
        bit_chunk& output) const;

    void Get(bit_chunk cover, ECmpSet& ecmpSet);
};

// ��������� ������������ �����������
struct OptionalObjects
    :IComparer
{
    ObjectPtrList optionalPrecedents;

    int GetSize() const;

    void Compare(Object const& o1, Object const& o2, 
        bit_chunk& output) const;

    void Get(bit_chunk cover, ObjectPtrList& selected);
};

typedef std::shared_ptr<IComparer> IComparerPtr;

typedef std::vector<IComparerPtr> Comparers;


struct ComparersComposer
    :IComparer
{
    Comparers comparers;

    virtual int GetSize() const;

    virtual void Compare( Object const& o1, Object const& o2, bit_chunk& output) const;

    // �������� ����� ��������, ����������� � ���������� � ��������� �������
    bit_chunk GetPart(bit_chunk const& cover, int index) const;
};
