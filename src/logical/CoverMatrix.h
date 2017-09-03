#pragma once
#include "FitMatrix.h"

// ������� ��� ���������� ���������� �������� ������� ���������
class CoverMatrix    
{
    // ����� ��������
    int _n;

    // ��������� ��������
    weighted_bit_matrix _covers;
        
    typedef std::pair<Weight, int> WeightOrder;

    typedef std::vector<WeightOrder> WeightOrders;

    // ��������� ������ ��� ���������� �� �����
    WeightOrders _weightOrders;

public:

    CoverMatrix();

    // ���������� ����� ��������
    void SetWidth(int n);

    // �������� ������ � ��������� ���������
    weighted_bit_matrix& GetCovers();
    
    // �������� ������ � ��������� ���������
    weighted_bit_matrix const& GetCovers() const;

    // �������� �������� � �����
    void AddCover(bit_chunk cover, Weight w);

    // �������� count �������� � ����������� ������
    void RestMost(int count);
    
};

