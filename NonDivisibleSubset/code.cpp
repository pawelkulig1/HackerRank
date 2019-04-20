#include <iostream>
#include <vector>

//this is solution that works, it build tree of possible solutions and recursively searches to find max depth
//for example if numbers are 1,2,3,4,5 and k = 5 tree for 1 will be like that:
//      |-------1-------|
//      |       |       |
//      2       3       5-------|
//      |       |       |       |
//      5       5       3       2
//
//max_depth will be 3 (checked only for root being 1)
//Although this solution works, HackerRank doesn't want to accept that because of timeout - it works to slow. (I think that idea was interesting so I wanted to post this code).
//there are few things to improve, for example building root and it's children could be done without looping and using recursion, but it was faster to implement like that.

class TreeNode
{
    int value;
    TreeNode *parent = nullptr;
    std::vector<TreeNode *> children;
public:
    TreeNode(int value): value(value){}
    void setValue(int value){this->value = value;}
    int getValue(){return value;}
    void setParent(TreeNode *parent){this->parent = parent;}
    TreeNode *getParent(){return parent;}
    void addChild(TreeNode *child)
    {
        child->setParent(this);
        children.push_back(child);
    }
    std::vector<TreeNode *> getChildren(){return children;}
    void deleteAllChildren()
    {
        if(children.size() == 0) return;
        
        for(int i=children.size() - 1;i>=0;i--)
        {
            children[i]->deleteAllChildren();
            delete children[i];
            children.erase(children.begin() + i);
        }
    }
};


int maxDepth = 1;

bool addAllChildren(TreeNode *tn, int k, int depth)
{
    if(depth > maxDepth) maxDepth = depth;
    std::vector<TreeNode *> siblings;
    siblings = tn->getParent()->getChildren();

    for(int i=0;i<siblings.size();i++)
    {   
        if(siblings[i] == tn) continue;
        if((tn->getValue() + siblings[i]->getValue()) % k != 0)
        {
            TreeNode *node = new TreeNode(siblings[i]->getValue());
            tn->addChild(node);
            //all.push_back(node);
        }
    }
    for(int i=0;i<tn->getChildren().size();i++)
    {
        addAllChildren(tn->getChildren()[i], k, depth+1);
    }
    return true;    
}

int main()
{
    int k = 7;
    std::vector<int> S = {1,2,3,4,5,6,7,8,9,10,11,141};
    std::vector<TreeNode *> roots;
    for(int i=0;i<S.size();i++)
    {
        TreeNode *node = new TreeNode(S[i]);
        for(int j=i;j<S.size();j++)
        {
            if((S[i] + S[j]) % k != 0)
            {
                if(i == j) continue;
                TreeNode *node2 = new TreeNode(S[j]);
                node->addChild(node2);
                addAllChildren(node2, k, 2);
            }
        }
        roots.push_back(node);
    }
    std::cout<<maxDepth<<std::endl;
    for(int i=0;i<roots.size();i++)
    {
        roots[i]->deleteAllChildren(); 
        delete roots[i];
    }

}


