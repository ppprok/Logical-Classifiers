#pragma once

#include "Object.h"
#include "Comparers.h"
#include "FitMatrix.h"

// ���������� ������� ���������
class CmpMatrix    
{
    // ������� ���������
    bit_matrix _cmpMatrix;

    // ��������� ������ ��� ���������� ���������� ��������� ��������
    bit_vector _cmpRow;

    // ����� ��������
    int _n;

    // ������������ ��������
    IComparerPtr _comparer;
        
public:

    void SetComparer(IComparerPtr comparer);
    
    CmpMatrix();

    // ������� ������� ���������
    bit_matrix& GetCmpMatrix();    
    
    // �������� ������������ �������
    void AddComparableObjects(Object const& po, Object const& no);
        
    // �������� ������������ �������
    void AddComparableObjects(Object const& po, ObjectsRange const& negative);

    // �������� ���� ������������ ��������
    void AddComparableObjects(ObjectsRange const& positive, 
        ObjectsRange const& negative);

    // ����� ������� ������
    void MergeSimilarRows(int restCount, FitMatrix const& fitMatrix);

    // �������� ����� ������
    void AddRow(bit_chunk const& row);
};

