#pragma once



class CListUDG
{
private: // 内部类
    // 邻接表中表对应的链表的顶点
    class ENode
    {
    public:
        int ivex;           // 该边所指向的顶点的位置
        ENode* nextEdge;    // 指向下一条弧的指针
    };

    // 邻接表中表的顶点
    class VNode
    {
    public:
        CPoint data;          // 顶点信息
        ENode* firstEdge;   // 指向第一条依附该顶点的弧
    };

private: // 私有成员
    int mVexNum;             // 图的顶点的数目
    int mEdgNum;             // 图的边的数目
    VNode mVexs[19 * 19];
    bool visited[19 * 19];
    bool isHave[19 * 19];
public:
    CListUDG() {}
    CListUDG(int inVexNum, CPoint inVexs[]);
    CListUDG(int inVexNum);
    ~CListUDG(){}
    void ResetNode(int bakcPoint);//重设某个结点
    void InitList(int inVexNum);//初始化
    void ResetList();//重置无向图
    void LinkNode(int inVexNum1, int inVexNum2);//连接相关结点
    void TreeNum(int mapPoint, int& n); //计算某节点生成树结点数量
    void SetHave(int havePoint);
private:
    void InitVisited();//初始化访问
    void DFS(int mapPoint, int& n);//深度优先搜索
};

