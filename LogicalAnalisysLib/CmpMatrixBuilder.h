#pragma once

#include <map>

#include "ECmp.h"
#include "bit_matrix.h"
#include <assert.h>
#include "containers.h"


typedef std::map<Object*, int> ObjectPositionMap;

// ���������� � ���������� ������� ���������
struct CmpMatrixSubmatrix
{
    UTILITY_MOVE_DEFAULT_MEMBERS(CmpMatrixSubmatrix, (Rows)(Positive)(Negative)(OptionalPositive)(OptionalNegative));    
    
    CmpMatrixSubmatrix(){};

    // ������ ����������
    bit_chunks Rows;
    
    // ������������� �������, ������������ � ����������
    ObjectPtrList Positive;
    
    // ������������� �������, ������������ � ����������
    ObjectPtrList Negative;
    
    // ������������� �������, ��� ������� �������� ������� ����������
    ObjectPtrList OptionalPositive;
    
    // ������������� �������, ��� ������� �������� ������� ����������
    ObjectPtrList OptionalNegative;

    // ����� ����� ������ ��� ���� ��������
    int GetRowNum(int pos, int neg)
    {
        assert(inside(Positive, pos));
        assert(inside(Negative, neg));
        return pos * Negative.size() + neg;
    }

    // ����� ������������� ������ �� ������ ������
    int GetPosNum(int row)
    {
        assert(inside(Rows, row));
        return row / Negative.size();
    }

    // ����� ������������� ������ �� ������ ������
    int GetNegNum(int row)
    {
        assert(inside(Rows, row));
        return row % Negative.size();
    }
};

/// ���������� ������� ��������� � � ���������
class CmpMatrixBuilder
{
    
    // ����������� ������� ���������
    bit_matrix _cmpMatrix;

    // ������� ������������� ��������
    ObjectPositionMap _positivePositions;
    
    // ������� ������������� ��������
    ObjectPositionMap _negativePositions;

    // ����� ����������������� ��������
    int _reservedColumns;

    // ��������� ����� �� ��.��. � ���������
    ECmpSet _localBasis;
    
    // ��������� ������� ������� �������� � �������
    int MakeObjectPositionMap(ObjectPtrList const& objects, ObjectPositionMap& posMap);

    // ��������� ������� ������� �������� ������������ ��������
    int MakeOptionalObjectPositionMap( ObjectPtrList const& optional, ObjectPtrList const& objects, ObjectPositionMap& posMap, ObjectPtrList& registered);

    // ���������� ��������� ������� �� �������
    int GetObjectPosition(ObjectPositionMap const& posMap, ObjectPtr const& o);

    int GetOptionalObjectPosition(ObjectPtr const& o, 
        ObjectPtrList const& optional,
        ObjectPositionMap& registeredPositions, 
        ObjectPtrList& registered);
    
    // ���������� ��������� ������� �� �������
    int GetObjectsPositions(
        ObjectPositionMap const& posMap, 
        ObjectPtrList const& objects,
        ObjectPtrList& present,
        Positions& positions);


public:

    CmpMatrixBuilder():
        _reservedColumns(0)
    {
    }

    ECmpSet const& GetLocalBasis() const
    {
        return _localBasis;
    }

    bit_matrix const& GetCmpMatrix() const
    {
        return _cmpMatrix;
    }

    ObjectPositionMap const& GetPositiveObjectPositions() const
    {
        return _positivePositions;
    }

    ObjectPositionMap const& GetNegativeObjectPositions() const
    {
        return _negativePositions;
    }

    // �������� ������ ������� ��� ���� ��������
    bit_chunk GetRow(ObjectPtr const& pos, ObjectPtr const& neg);


    // ��������� ���������� �� �����, ����������� � ����� �������� �� ��������� �������
    // ������������� � ������������� ��������.
    // ��� ������� ��������������� (optional) ������� �� ����� ����������������� ��������
    // ���������� ���� �������, � ������� ����� ������� � ��� �������, ������� �������������
    // ��������������� �������.
    CmpMatrixSubmatrix GetSubmatrix(
        ObjectPtrList const& positive, 
        ObjectPtrList const& negative,
        ObjectPtrList const& optionalPositive,
        ObjectPtrList const& optionalNegative);


    // ��������� ������� ��������� �������� �� ���� �������:
    // ������������� �������� � ������������� ��������
    // ��� ��������� ������������ ��������� ����� � ���������������
    // ��������� ����� �������� 
    void Build(
        ObjectPtrList const& positive, 
        ObjectPtrList const& negative,
        ECmpSet localBasis,
        int reserveColumns = 0);
    
    // �������� ��.��. � ���������� ��������
    ECmpSet GetECmpSubset(Positions const& positions);

    // �������� ������ ����������� ��������
    void GetExcludedOptionalObjects(
        CmpMatrixSubmatrix const& submatrix, 
        Positions const& cover, 
        ObjectPtrList& excludedPositive, 
        ObjectPtrList& excludedNegative);
};