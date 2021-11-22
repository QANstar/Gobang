#pragma once



class CListUDG
{
private: // �ڲ���
    // �ڽӱ��б��Ӧ������Ķ���
    class ENode
    {
    public:
        int ivex;           // �ñ���ָ��Ķ����λ��
        ENode* nextEdge;    // ָ����һ������ָ��
    };

    // �ڽӱ��б�Ķ���
    class VNode
    {
    public:
        CPoint data;          // ������Ϣ
        ENode* firstEdge;   // ָ���һ�������ö���Ļ�
    };

private: // ˽�г�Ա
    int mVexNum;             // ͼ�Ķ������Ŀ
    int mEdgNum;             // ͼ�ıߵ���Ŀ
    VNode mVexs[19 * 19];
    bool visited[19 * 19];
    bool isHave[19 * 19];
public:
    CListUDG() {}
    CListUDG(int inVexNum, CPoint inVexs[]);
    CListUDG(int inVexNum);
    ~CListUDG(){}
    void ResetNode(int bakcPoint);//����ĳ�����
    void InitList(int inVexNum);//��ʼ��
    void ResetList();//��������ͼ
    void LinkNode(int inVexNum1, int inVexNum2);//������ؽ��
    void TreeNum(int mapPoint, int& n); //����ĳ�ڵ��������������
    void SetHave(int havePoint);
private:
    void InitVisited();//��ʼ������
    void DFS(int mapPoint, int& n);//�����������
};

