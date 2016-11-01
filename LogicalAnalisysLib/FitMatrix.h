#pragma once
#include "Object.h"
#include "bit_matrix.h"
#include "Comparers.h"
#include "bit_vector.h"



typedef bit_matrix_<std::vector<weighted_bit_chunk<Weight> > > 
    weighted_bit_matrix;


// ����������� �������
class FitMatrix
{
    // ������, �������������� ��������� ��������
    IComparerPtr _comparer;

    // ��������� ������ ��� ���������� ���������� ��������� ��������
    bit_vector _cmpRow;

    // ������� ��������� ��� ���������
    weighted_bit_matrix _fitMatrix;

    // ����� ��������
    int _n;

    // ����� ����� �����, ������� ����� ������� ��������
    Weights _columnWeights;

public:

    FitMatrix();

    void SetComparer(IComparerPtr comparer);

    // ����� ����� ����� �������� �����
    Weight GetCoveredRowsWeight(bit_chunk cover) const;

    // ����� ����� ����� ����� ��������
    Weight GetCommonColumnsWeight(bit_chunk const& c1, bit_chunk const& c2) const;

    // ����� ����� ����� ������������ ��������
    Weight GetDiffColumnsWeight(bit_chunk const& c1, bit_chunk const& c2) const;

    // �������� ������ � ����������� �������
    weighted_bit_matrix& GetFitMatrix();

    // �������� ������ � ����������� �������
    weighted_bit_matrix const& GetFitMatrix() const;

    // �������� ������, �� �������� ����������� ��������
    void AddFittingObject(Object const& precedent, Object const& o, Weight w);

    // �������� �������, �� ������� ����������� ��������
    void AddFittingObjects(Object const& precedent, ObjectsRange const& objects, Weight w);

    // �������� ������, �� �������� ����������� �������� �� ������ �����������
    void AddFittingObject(ObjectsRange const& precedents, Object const& o, Weight w);

    // �������� �������, �� ������� ����������� �������� �� ������ �����������
    void AddFittingObjects(ObjectsRange const& precedents, ObjectsRange const& objects, Weight w);

    // ������� ������, ������������ ��������� ������
    void RemoveSupRows(bit_chunk row);
    
    // ������� ������, ������������ ���� �� ���� �� ��������� �����
    template<typename Rows>
    void RemoveSupRows(Rows const& rows)
    {
        for (auto const& row:rows)
        {
            if (_fitMatrix.height() == 0)
                break;
            RemoveSupRows(row);
        }
    }

    // ������� ������, �������� ��������� �������
    void RemoveCoveredRows(bit_chunk cover);

    // ������� ������ � �������� ������
    void RemoveZeroWeightRows();

    // ����� ������� ������, ������� �� ����� restCount �����
    void MergeSimilarRows(int restCount);

private:
    
    // �������� ���� �������� ����� ��������� ���� ������
    void UpdateColumnWeights(bit_chunk row, Weight deltaW);

};
